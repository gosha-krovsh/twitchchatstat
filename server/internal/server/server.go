package server

import (
	"context"
	"encoding/json"
	"fmt"
	"net/http"
	"os"
	"os/signal"
	"regexp"
	"server/gosha.krovsh/twitchstatserver/internal/twitch"
	"strconv"
	"syscall"
	"time"
)

var clientAPI twitch.APIClient

func update(w http.ResponseWriter, r *http.Request) {
	clientId := r.URL.Query().Get("client_id")
	token := r.URL.Query().Get("token")

	var currentUpdate twitch.UpdateResponse
	if user, ok := clientAPI.GetClient(clientId, token); ok {
		currentUpdate = user.CurrentUpdate
	} else {
		err := clientAPI.AddClient(clientId, token)
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			return
		}
		user, _ = clientAPI.GetClient(clientId, token)

		currentUpdate = user.CurrentUpdate
	}

	bytes, marshalError := json.Marshal(currentUpdate)
	if marshalError != nil {
		return
	}

	_, writeErr := w.Write(bytes)
	if writeErr != nil {
		return
	}
}

func hello(w http.ResponseWriter, r *http.Request) {
	clientId := r.URL.Query().Get("client_id")
	token := r.URL.Query().Get("token")

	if user, ok := clientAPI.GetClient(clientId, token); ok {
		user.TwitchClient.Say(user.UserName, "hello")
	} else {
		/* This is impossible if everything works correctly */
		w.WriteHeader(http.StatusInternalServerError)
		return
	}

	w.WriteHeader(200)
}

func router(w http.ResponseWriter, r *http.Request) {
	var updateRegex = regexp.MustCompile(`/update*`)
	var helloRegex = regexp.MustCompile(`/hello*`)

	if updateRegex.MatchString(r.RequestURI) {
		getOnly(http.HandlerFunc(update)).ServeHTTP(w, r)
	} else if helloRegex.MatchString(r.RequestURI) {
		getOnly(http.HandlerFunc(hello)).ServeHTTP(w, r)
	} else {
		w.WriteHeader(404)
	}
}

func Serve(port int) error {
	clientAPI = *twitch.NewAPIClient()

	srv := &http.Server{
		Addr:    ":" + strconv.Itoa(port),
		Handler: http.HandlerFunc(router),
	}
	serveChan := make(chan error, 1)
	go func() {
		serveChan <- srv.ListenAndServe()
	}()

	stop := make(chan os.Signal, 1)
	signal.Notify(stop, syscall.SIGINT, syscall.SIGTERM)
	select {
	case <-stop:
		fmt.Println("shutting down gracefully")
		ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
		defer cancel()
		return srv.Shutdown(ctx)

	case err := <-serveChan:
		return err
	}
}

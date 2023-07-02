package internal

import (
	"net/http"
	"strconv"
)

func update(w http.ResponseWriter, r *http.Request) {

}

func write(w http.ResponseWriter, r *http.Request) {

}

func router(w http.ResponseWriter, r *http.Request) {
	switch r.RequestURI {
	case "/update":
		getOnly(http.HandlerFunc(update))
	case "/write":
		postOnly(http.HandlerFunc(write))
	default:
		w.WriteHeader(404)
	}
}

func Serve(port int) {
	/* Http server on localhost:port */
	err := http.ListenAndServe(":"+strconv.Itoa(port), http.HandlerFunc(router))
	if err != nil {
		panic(err)
	}
}

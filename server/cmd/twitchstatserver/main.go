package main

import (
	"flag"
	"fmt"
	"os"
	"server/gosha.krovsh/twitchstatserver/internal/server"
)

var port *int = flag.Int("port", 8080, "<port> port for the server")

func main() {
	flag.Parse()
	err := server.Serve(*port)
	if err != nil {
		_, _ = fmt.Fprint(os.Stderr, fmt.Errorf("server has failed: %v", err))
		return
	}
}

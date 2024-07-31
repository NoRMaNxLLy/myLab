package main

import (
	"fmt"
	"io"
	"log"
	"os"
)

func cat(r io.Reader) error {
	buf := make([]byte, 4096)

	for {
		n, err := r.Read(buf)
		fmt.Printf("%s", buf[:n])

		if err == io.EOF {
			return err
		}

		if err != nil {
			log.Fatal(err)
			return err
		}
	}
}

func main() {
	if len(os.Args[1:]) == 0 {
		cat(os.Stdin)
		os.Exit(0)
	}

	for _, f := range os.Args[1:] {
		fd, err := os.Open(f)

		if err != nil {
			panic(err)
		}

		cat(fd)
		fd.Close()
	}
}

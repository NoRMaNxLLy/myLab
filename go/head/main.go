package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
)

var numLines = 10

// Head prints out the first numLines of an io.Reader
func Head(r io.Reader) {
	scanner := bufio.NewScanner(r)

	for i := 0; scanner.Scan() && i <= numLines; i++ {
		fmt.Printf("%s\n", scanner.Text())
	}
}

func main() {
	flag.IntVar(&numLines, "n", 10, "print first N lines")
	flag.Parse()
	fnames := flag.Args()
	if len(fnames) == 0 {
		Head(os.Stdin)
		os.Exit(0)
	}

	for i := range fnames {
		f, err := os.Open(fnames[i])
		if err != nil {
			fmt.Fprintf(os.Stderr, "%v\n", err)
			os.Exit(1)
		}

		if len(fnames) > 1 {
			fmt.Printf("==> %s <==\n", f.Name())
		}
		Head(f)
		f.Close()
	}
}

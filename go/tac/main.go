// tac concatenate and print file in reverse
package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
)

func Tac(r io.Reader) {
	scanner := bufio.NewScanner(r)
	//var rev []string
	rev := make([]string, 0, 256)

	for scanner.Scan() {
		rev = append(rev, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	for i := len(rev) - 1; i >= 0; i-- {
		fmt.Printf("%s\n", rev[i])
	}
}

func main() {
	if len(os.Args[1:]) < 1 {
		Tac(os.Stdin)
		os.Exit(1)
	}

	files := os.Args[1:]
	for _, v := range files {
		if v == "-" {
			Tac(os.Stdin)
			continue
		}

		f, err := os.Open(v)
		if err != nil {
			log.Fatal(err)
		}

		Tac(f)
		f.Close()
	}
}

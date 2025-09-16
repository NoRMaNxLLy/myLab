package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

type WordCounter int

func (wc *WordCounter) Write(p []byte) (int, error) {
	words := strings.Split(string(p), " ")
	*wc += WordCounter(len(words))
	return len(words), nil
}

func main() {
	var wc WordCounter
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		_, _ = wc.Write([]byte(scanner.Text()))
	}
	if err := scanner.Err(); err != nil {
		log.Fatalf("scanner error: %v\n", err)
	}
	fmt.Printf("wc: %d\n", wc)
}

package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"path"
	"regexp"
	"strings"
)

var emoji = make(map[string]string)
var EmojiRE = regexp.MustCompile(":[a-zA-Z-_]+:")

// TODO: this is not right
var EmojiFile = path.Join(os.ExpandEnv("$HOME"), ".local", "share", "emojies.txt")

// ReadEmojies reads the emojie file into the emojies Map
func ReadEmojies(f io.Reader) {
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		l := strings.TrimSpace(scanner.Text())
		if l == "" || strings.HasPrefix(l, "#") {
			continue
		}
		f := strings.Split(l, "\t")
		e := f[0]
		for _, v := range f[1:] {
			emoji[v] = e
		}
	}
}

func main() {
	f, err := os.Open(EmojiFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
	ReadEmojies(f)
	f.Close()

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		l := scanner.Text()
		res := EmojiRE.ReplaceAllStringFunc(l, func(s string) string {
			if e, ok := emoji[s]; ok {
				return e
			}
			return s
		})
		fmt.Println(res)
	}

	if err := scanner.Err(); err != nil {
		fmt.Fprintf(os.Stderr, "%s\n", err)
	}
}

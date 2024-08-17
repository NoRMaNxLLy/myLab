package main

import (
	"fmt"
	"os"
	"path"
	"strings"
)

// get the PATH variable
// split at :
// check if PATHVal/args exists
// TODO: add -a

func Executable(file string) bool {
	f, err := os.Stat(file)
	if err != nil {
		return false
	}
	return f.Mode()&0111 != 0
}

func main() {
	paths := strings.Split(os.Getenv("PATH"), ":")
Outer:
	for _, a := range os.Args[1:] {
		for _, p := range paths {
			fp := path.Join(p, a)
			if ok := Executable(fp); ok {
				fmt.Println(fp)
				continue Outer
			}
		}
		fmt.Fprintf(os.Stderr, "no %s in (%s)\n", a, os.Getenv("PATH"))
	}
}

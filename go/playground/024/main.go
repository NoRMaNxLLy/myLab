package main

import (
	"fmt"
	"strings"
	"time"
)

func main() {
	str := "hello\tworld\t" + time.Now().Format(time.RFC3339)
	fmt.Println(str)
	fmt.Printf("%#v\n", strings.Split(str, "\t"))
}

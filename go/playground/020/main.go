package main

import "fmt"

func foo(ch <-chan int) {
	for {
		fmt.Println("hi?", <-ch)
	}
}

func main() {
	ch := make(chan int)

	go foo(ch)
	ch <- 15
	ch <- 30
}

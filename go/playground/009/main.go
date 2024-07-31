package main

import (
	"fmt"
)

type Person struct {
	name string
	age  int
}

func main() {
	p := &Person{"mohammed", 22}

	fmt.Printf("%v || %#[1]v || %[1]T || %[1]p\n", p)
}

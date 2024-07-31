package main

// read an int in
// while in > 1
//	s = append(s, in % 10)
//  in /= 10
// for i = len(s) - 1; i >= 0; i--
//	print s[i]

import (
	"fmt"
)

func main() {
	var in int
	s := []int{}

	fmt.Print("in: ")
	fmt.Scanf("%d", &in)

	for in >= 1 {
		s = append(s, in%10)
		in /= 10
	}

	for i := len(s) - 1; i >= 0; i-- {
		fmt.Printf("%d", s[i])
		if i == 0 {
			break
		}
		fmt.Printf(", ")
	}
	fmt.Println()
}

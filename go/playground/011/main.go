package main

import "fmt"

func main() {
	s1 := []int{1, 2, 3}
	s2 := s1
	s2 = append(s2, 4)
	fmt.Println(s1, len(s1), cap(s1))
	fmt.Println(s2, len(s2), cap(s2))
}

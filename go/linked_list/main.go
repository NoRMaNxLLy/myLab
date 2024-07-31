package main

import "fmt"

type node struct {
	Val  any
	Next *node
	Prev *node
}

func (n *node) String() {
	if n == nil {
		fmt.Println("<nil>")
		return
	}
	for n != nil {
		fmt.Printf("%#v --> ", n.Val)
		n = n.Next
	}

	fmt.Println("nil")
}

func (n *node) PushFront(val any) *node {
	if n == nil {
		n = &node{Val: val}
		return n
	}

	n.Prev = &node{Val: val, Next: n, Prev: nil}

	return n.Prev
}

func (n *node) PushBack(val any) *node {
	if n == nil {
		n = &node{Val: val}
		return n
	}

	t := n
	for t.Next != nil {
		t = t.Next
	}

	t.Next = &node{Val: val, Prev: t}
	return n
}

func main() {
	var head *node

	head = head.PushFront(15)
	head = head.PushFront(30)
	head = head.PushBack(500)
	head = head.PushBack(100)
	head = head.PushFront(1)
	head = head.PushFront("hello world!!")
	head = head.PushFront(
		struct {
			name string
			id   int
		}{
			"mohammed",
			51,
		},
	)

	head.String()
}

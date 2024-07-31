package main

import (
	"fmt"
)

type IntTree struct {
	val         int
	left, right *IntTree
}

func (it *IntTree) Insert(val int) *IntTree {
	if it == nil {
		return &IntTree{val: val}
	}

	if val < it.val {
		it.left = it.left.Insert(val)
	} else if val > it.val {
		it.right = it.right.Insert(val)
	}

	return it
}

func (it *IntTree) Contains(val int) bool {
	switch {
	case it == nil:
		return false
	case val < it.val:
		return it.left.Contains(val)
	case val > it.val:
		return it.right.Contains(val)
	default:
		return true
	}
}

func (it *IntTree) String() string {
	if it == nil {
		return ""
	}

	return fmt.Sprintf("%s %d %s", it.left.String(), it.val, it.right.String())
}

func main() {
	var it *IntTree
	it = it.Insert(50)
	it = it.Insert(12)
	it = it.Insert(21)
	it = it.Insert(5)
	it = it.Insert(3)
	it = it.Insert(10)
	it = it.Insert(2)
	fmt.Println(it.String())
}

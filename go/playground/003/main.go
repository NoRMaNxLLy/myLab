package main

import (
	"errors"
	"os"
)

func div(numerator, denominator int) (int, int, error) {
	if denominator == 0 {
		return 0, 0, errors.New("cannot divide by Zero")
	}
	return numerator / denominator, numerator % denominator, nil
}

func main() {
	res, rem, err := div(5, 2)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(res, rem)
	fmt.Printf("%T\n", div)
}

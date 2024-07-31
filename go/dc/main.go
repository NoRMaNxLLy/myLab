package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func Calculate(e string) (int, error) {
	tokens := strings.Fields(e)
	s := make([]int, 0, 32)

	for _, v := range tokens {
		l := len(s) - 1
		if match, _ := regexp.MatchString("^[0-9]+", v); match {
			n, _ := strconv.Atoi(v)
			s = append(s, n)
		} else if v == "+" {
			s[l-1] = s[l-1] + s[l]
			s = s[:l]
		} else if v == "-" {
			s[l-1] = s[l-1] - s[l]
			s = s[:l]
		} else if v == "*" {
			s[l-1] = s[l-1] * s[l]
			s = s[:l]
		} else if v == "/" {
			s[l-1] = s[l-1] / s[l]
			s = s[:l]
		} else {
			return 0, fmt.Errorf("%s is invalid", v)
		}
	}

	if len(s) != 1 {
		return 0, errors.New("invalid expression")
	}
	return s[0], nil
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		res, err := Calculate(scanner.Text())
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			continue
		}

		fmt.Println(res)
	}
}

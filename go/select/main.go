package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	choices := make([]string, 1, 128)
	for i := 1; scanner.Scan(); i++ {
		choices = append(choices, scanner.Text())
	}
	if err := scanner.Err(); err != nil {
		log.Println(err)
		os.Exit(1)
	}

	for i := 1; i < len(choices); i++ {
		fmt.Printf("%d) %s\n", i, choices[i])
	}

	os.Stdin, _ = os.Open("/dev/tty")
	fmt.Print("#? ")
	var choice int
	fmt.Scanf("%d", &choice)

	if 1 <= choice && choice <= len(choices) {
		fmt.Fprintf(os.Stdout, "%s\n", choices[choice])
	}
}

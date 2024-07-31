package main

func div(numerator, denominator int) int {
	if denominator == 0 {
		return 0
	}
	return numerator / denominator
}

func main() {
	var result = div(3, 2)
	fmt.Println(result)
}

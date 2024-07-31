package main

func main() {
	var i any

	i = 5000
	fmt.Printf("%T\n", i)

	i = "hello world"
	fmt.Printf("%T\n", i)
	fmt.Printf("%s\n", "just a test")
}

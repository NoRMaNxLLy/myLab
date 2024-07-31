package main

func countLetters(r io.Reader) (map[rune]int, error) {
	buf := make([]byte, 2048)
	out := map[rune]int{}
	for {
		n, err := r.Read(buf)
		for _, b := range string(buf[:n]) {
			if unicode.IsLetter(b) {
				out[b]++
			}
		}

		if err == io.EOF {
			return out, nil
		}
		if err != nil {
			return nil, err
		}
	}
}

func main() {
	strReader := strings.NewReader("hello world!.")

	countMap, _ := countLetters(strReader)

	for k, v := range countMap {
		fmt.Printf("%q %d\n", k, v)
	}
}

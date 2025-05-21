package main

import (
	"fmt"
	"os"
	"testing"
)

func TestEmojiRE(t *testing.T) {
	txt := "hello :grinning:, :vomiting: :upside-down: :-_-:"
	//res := EmojiRE.FindAllString(txt, -1)
	res := EmojiRE.ReplaceAllStringFunc(txt, func(s string) string {
		if e, ok := emoji[s]; ok {
			return e
		}
		return s
	},
	)
	fmt.Printf("%v\n", res)
}

func TestEmojiFile(t *testing.T) {
	f, err := os.Open(EmojiFile)
	if err != nil {
		t.Fatal(err)
	}
	ReadEmojies(f)
}

func TestEmojiMap(t *testing.T) {
	for k, v := range emoji {
		fmt.Println(k, v)
	}
}

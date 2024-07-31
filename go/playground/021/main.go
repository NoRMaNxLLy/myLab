package main

import (
	"log"
	"os"

	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		log.Fatal(err)
	}

	var f func(*html.Node)
	f = func(n *html.Node) {
		if n.Type == html.ElementNode && n.Data == "h1" {
			n.FirstChild.Data = "# " + n.FirstChild.Data
		}

		for c := n.FirstChild; c != nil; c = c.NextSibling {
			f(c)
		}

	}

	f(doc)
	html.Render(os.Stdout, doc)
}

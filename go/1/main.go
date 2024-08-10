package main

import "path/filepath"

func main() {
	println(filepath.Abs("README.md"))

	println(filepath.Base("/usr/bin"))

	println(filepath.Dir("/usr/bin"))

	files, _ := filepath.Glob("/*")
	for _, f := range files {
		println(f)
	}
}

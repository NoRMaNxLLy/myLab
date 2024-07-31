package main

import (
	"fmt"
	"net/netip"
	"os"
)

func main() {
	net, err := netip.ParsePrefix("192.168.1.1/24")
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}

	fmt.Printf("%v\n", net.Bits())
}

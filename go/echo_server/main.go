package main

import (
	"fmt"
	"io"
	"net"
	"os"
)

func handleConn(conn net.Conn) {
	b := make([]byte, 2048)
	for {
		n, err := conn.Read(b)
		if err == io.EOF {
			fmt.Println("received EOF from", conn.RemoteAddr())
			break
		}
		if err != nil {
			fmt.Println(err)
			continue
		}
		fmt.Println("from", conn.RemoteAddr(), string(b[:n-1])) // -1 to remove \n
		conn.Write(b[:n])
	}
	conn.Close()
}

func main() {
	var ipPort = "localhost:8007"
	ln, err := net.Listen("tcp", ipPort)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println("listening on", ln.Addr())
	for {
		conn, err := ln.Accept()
		if err != nil {
			fmt.Println(err)
			continue
		}
		fmt.Println("connection from", conn.RemoteAddr())
		go handleConn(conn)
	}
}

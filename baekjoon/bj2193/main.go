package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	var zero int64 = 1
	var one int64 = 1
	for i := 2; i <= n; i++ {
		nZero := zero + one
		nOne := zero
		zero = nZero
		one = nOne
	}
	fmt.Println(one)
}
package main

import "fmt"

func main() {
	var n, cr, cg, cb int
	fmt.Scan(&n)
	for range n {
		var r, g, b int
		fmt.Scan(&r, &g, &b)
		cr, cg, cb = r+min(cg, cb), g+min(cr, cb), b+min(cr, cg)
	}
	fmt.Println(min(cr, cg, cb))
}

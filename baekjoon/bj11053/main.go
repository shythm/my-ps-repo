package main

import (
	"fmt"
	"slices"
)

func main() {
	var n int
	fmt.Scan(&n)
	seq := make([]int, n)
	for i := range n {
		fmt.Scan(&seq[i])
	}
	dp := [1001]int{}
	for _, v := range seq {
		dp[v] = slices.Max(dp[0:v]) + 1
	}
	fmt.Println(slices.Max(dp[:]))
}

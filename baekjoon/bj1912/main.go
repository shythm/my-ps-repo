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
	dp := make([]int, n)
	dp[0] = seq[0]
	for i := 1; i < n; i++ {
		dp[i] = max(dp[i-1]+seq[i], seq[i])
	}
	fmt.Println(slices.Max(dp[:]))
}

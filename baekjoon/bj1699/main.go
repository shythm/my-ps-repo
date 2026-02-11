package main

import (
	"fmt"
	"math"
)

func main() {
	var n int
	fmt.Scan(&n)
	fmt.Println(solution(n))
}

func solution(n int) int {
	dp := make([]int, n+1)
	for i := range n + 1 {
		dp[i] = math.MaxInt
	}
	root, square := 1, 1
	for square <= n {
		dp[square] = 1
		for k := square + 1; k <= n; k++ {
			dp[k] = min(dp[k], 1+dp[k-square])
		}
		root++
		square = root * root
	}
	return dp[n]
}

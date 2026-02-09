package main

import (
	"fmt"
)

func main() {
	var n int
	fmt.Scanf("%d", &n)
	prices := make([]int, n+1)
	for i := 1; i <= n; i++ {
		fmt.Scanf("%d", &prices[i])
	}
	answer := solution(n, prices)
	fmt.Println(answer)
}

func solution(n int, prices []int) int {
	dp := make([]int, n+1)
	for i := 1; i <= n; i++ {
		dp[i] = prices[i]
	}

	for i := 2; i <= n; i++ {
		for j := 1; j <= i/2; j++ {
			dp[i] = min(dp[i], dp[j]+dp[i-j])
		}
	}

	return dp[n]
}

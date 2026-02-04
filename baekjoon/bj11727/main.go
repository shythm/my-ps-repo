package main

import "fmt"

func main() {
	var n int
	fmt.Scanf("%d", &n)
	fmt.Println(solution(n))
}

func solution(n int) int {
	dp := make([]int, 1001)
	dp[1] = 1
	dp[2] = 3
	for i := 3; i <= n; i++ {
		dp[i] = (dp[i-1] + 2*dp[i-2]) % 10007
	}
	return dp[n]
}

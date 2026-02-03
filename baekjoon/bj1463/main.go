package main

import (
	"fmt"
	"math"
)

func main() {
	var n int
	fmt.Scanf("%d", &n)
	answer := solution(n)
	fmt.Println(answer)
}

func solution(n int) int {
	dp := make([]int, n+1)
	dp[1] = 0
	for i := 2; i <= n; i++ {
		opt := math.MaxInt
		if i%3 == 0 {
			// 3으로 나누어 떨어지는 경우
			opt = min(dp[i/3]+1, opt)
		}
		if i%2 == 0 {
			// 2로 나누어 떨어지는 경우
			opt = min(dp[i/2]+1, opt)
		}
		// 1을 빼는 경우
		opt = min(dp[i-1]+1, opt)
		dp[i] = opt
	}
	return dp[n]
}

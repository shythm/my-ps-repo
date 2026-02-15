package main

import "fmt"

func main() {
	var t int
	fmt.Scan(&t)
	maxN := 0
	numbers := make([]int, t)
	for i := range t {
		fmt.Scan(&numbers[i])
		maxN = max(maxN, numbers[i])
	}
	const MOD = 1_000_000_009
	dp := make([]int, max(4, maxN+1))
	dp[0] = 0
	dp[1] = 1 // 1
	dp[2] = 2 // 1+1, 2
	dp[3] = 4 // 1+1+1, 1+2, 2+1, 3
	for i := 4; i <= maxN; i++ {
		dp[i] = (dp[i-1] % MOD) + (dp[i-2] % MOD) + (dp[i-3] % MOD)
		dp[i] %= MOD
	}
	for _, v := range numbers {
		fmt.Println(dp[v])
	}
}

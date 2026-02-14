package main

import "fmt"

func main() {
	var n, k int
	fmt.Scanf("%d%d", &n, &k)
	dp := make([][]int, k)
	dp[0] = make([]int, n+1)
	for i := range n+1 {
		dp[0][i] = 1
	}
	const MOD = 1_000_000_000
	for i := 1; i < k; i++ {
		dp[i] = make([]int, n+1)
		dp[i][0] = 1
		for j := 1; j <= n; j++ {
			dp[i][j] = (dp[i][j-1] % MOD) + (dp[i-1][j] % MOD)
			dp[i][j] %= MOD
		}
	}
	fmt.Println(dp[k-1][n])
}

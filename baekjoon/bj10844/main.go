package main

import "fmt"

var dp [101][10]int
const MOD = 1_000_000_000

func main() {
	var n int
	fmt.Scan(&n)
	for i := range 10 {
		dp[1][i] = 1
	}
	for i := 2; i <= n; i++ {
		dp[i][0] = dp[i-1][1] % MOD
		for j := 1; j <= 8; j++ {
			dp[i][j] = ((dp[i-1][j-1] % MOD) + (dp[i-1][j+1] % MOD)) % MOD
		}
		dp[i][9] = dp[i-1][8]
	}
	sum := 0
	for i := 1; i <= 9; i++ {
		sum += dp[n][i] % MOD
	}
	sum %= MOD
	fmt.Println(sum)
}
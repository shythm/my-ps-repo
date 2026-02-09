package main

import (
	"fmt"
	"math"
)

func main() {
	var T int
	fmt.Scan(&T)
	tcs := make([]int, T)
	maxN := math.MinInt
	for i := range T {
		fmt.Scan(&tcs[i])
		maxN = max(maxN, tcs[i])
	}
	dp := make([][]int, max(4, maxN+1))
	dp[0] = []int{0, 0, 0, 0}
	dp[1] = []int{0, 1, 0, 0} // _ / 1로 시작하는 경우 / 2로 시작하는 경우 / 3으로 시작하는 경우
	dp[2] = []int{0, 0, 1, 0} // _ / _ / 2 / _
	dp[3] = []int{0, 1, 1, 1} // _ / 1+2 / 2+1 / 3
	sumExceptFor := func(n int, e int) int {
		sum := 0
		for i := range 4 {
			if i == e {
				continue
			}
			sum += dp[n][i] % 1_000_000_009
		}
		return sum % 1_000_000_009
	}
	for i := 4; i <= maxN; i++ {
		dp[i] = []int{
			0,
			sumExceptFor(i-1, 1),
			sumExceptFor(i-2, 2),
			sumExceptFor(i-3, 3),
		}
	}
	for _, v := range tcs {
		fmt.Println((dp[v][1] + dp[v][2] + dp[v][3]) % 1_000_000_009)
	}
}

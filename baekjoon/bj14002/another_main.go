package main

import (
	"fmt"
	"math"
)

func main() {
	var n int
	fmt.Scan(&n)
	seq := make([]int, n)
	for i := range n {
		fmt.Scan(&seq[i])
	}

	dp := make([]int, n)
	parent := make([]int, n)
	for i := range n {
		dp[i] = 1
		parent[i] = -1

		for j := range i {
			if seq[j] < seq[i] && dp[i] < dp[j]+1 {
				dp[i] = dp[j] + 1
				parent[i] = j
			}
		}
	}

	maxIdx := -1
	maxVal := math.MinInt
	for i, v := range dp {
		if v > maxVal {
			maxIdx, maxVal = i, v
		}
	}
	fmt.Println(maxVal)
	lis := []int{}
	for i := maxIdx; i != -1; i = parent[i] {
		lis = append(lis, seq[i])
	}
	for i := len(lis) - 1; i >= 0; i-- {
		fmt.Printf("%d ", lis[i])
	}
	fmt.Println()
}

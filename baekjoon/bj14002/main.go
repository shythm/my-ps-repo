package main

import (
	"fmt"
	"math"
	"slices"
)

const maxElemNum = 1000

func main() {
	var n int
	fmt.Scan(&n)
	seq := make([]int, n)
	for i := range n {
		fmt.Scan(&seq[i])
	}
	dp := make([][]int, n+1)
	dp[0] = make([]int, maxElemNum+1)
	for i, v := range seq {
		dp[i+1] = make([]int, maxElemNum+1)
		copy(dp[i+1], dp[i])
		dp[i+1][v] = slices.Max(dp[i+1][:v]) + 1
	}
	lis := make([]int, 0)
	si := n
	pi := maxElemNum + 1
	for si > 0 && pi > 0 {
		ci, cv := -1, math.MinInt
		for i, v := range dp[si][:pi] {
			if v > cv {
				ci, cv = i, v
			}
		}
		if ci == 0 {
			break
		}
		lis = append(lis, ci)
		for si > 0 && dp[si][ci] == cv {
			si--
		}
		pi = ci
	}
	fmt.Println(len(lis))
	for i := len(lis) - 1; i >= 0; i-- {
		fmt.Printf("%d ", lis[i])
	}
	fmt.Println()
}

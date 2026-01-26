package main

import (
	"fmt"
	"math"
)

const DEBUG bool = false

func main() {
	var n int
	fmt.Scan(&n)
	var answer = Solution(n)
	fmt.Println(answer)
}

func Solution(originalN int) int {
	var answer int = 0
	digits := 0
	k := 0

	for n := originalN; n != 0; n /= 10 {
		digits += 1
		ninePow10 := 9 * int(math.Pow10(digits-1))

		if n/10 == 0 {
			// 마지막 자릿수에 대한 처리
			answer += digits * (originalN - k)
		} else {
			// 아직 남은 자릿수가 있으면
			answer += digits * ninePow10
		}
		k += ninePow10

		if DEBUG {
			fmt.Printf("digits: %d, ninePow10: %d, k: %d, answer: %d\n", digits, ninePow10, k, answer)
		}
	}

	return answer
}

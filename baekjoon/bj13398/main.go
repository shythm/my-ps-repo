package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var n int
	fmt.Fscan(reader, &n)
	seq := make([]int, n)
	for i := range n {
		fmt.Fscan(reader, &seq[i])
	}

	dpNormal := make([]int, n)  // 일반 수열
	dpRemoval := make([]int, n) // 원소 하나가 제거된 수열

	dpNormal[0] = seq[0]
	dpRemoval[0] = seq[0]
	answer := seq[0]

	for i := 1; i < n; i++ {
		// 기본적으로 누적합하다가, 해당 원소에서 새로 시작하는 것이 이득인 경우를 반영한다.
		dpNormal[i] = max(dpNormal[i-1]+seq[i], seq[i])
		answer = max(answer, dpNormal[i])

		// 해당 원소를 제외하거나 vs 이전 누적합(원소 하나가 제거된 수열의 합)에 나를 포함시키거나
		dpRemoval[i] = max(dpNormal[i-1], dpRemoval[i-1]+seq[i])
		answer = max(answer, dpRemoval[i])
	}

	fmt.Println(answer)
}

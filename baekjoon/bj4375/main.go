package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	// for n := 1; n <= 10000; n++ {
	// 	if n%2 == 0 || n%5 == 0 {
	// 		continue
	// 	}
	// 	fmt.Println(n, Solution(n))
	// }

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		num, _ := strconv.Atoi(line)
		fmt.Println(Solution(num))
	}
}

func Solution(n int) int {
	// 각 자릿수가 모두 1로 시작되는 경우는 1 + 10 + 100 + ... 이다. 이를 수열의 합으로 나타내면
	// k는 자릿수이고, S_k = (10^k-1)/9로 나타낼 수 있다(등비수열의 합).
	// 즉, 정수 n의 배수 m이라고 할 때, n*m = S_k = (10^k-1)/9가 되는 m을 구하면 된다.
	// 위의 식을 정리하면 9*n*m = 10^k-1이고 이는 곧 10^k-1을 9*n으로 나누어 떨어지는 k를 구하면 된다는 뜻이다.
	// 따라서 10^k-1를 9*n 모듈러 연산한 값이 0이면 되는데, 모듈러 연산의 성질을 이용하면,
	// 10^k mod 9n - 1 = 0이 되는 것이고(n >= 1), 10^k mod 9n = 1이 되는 k를 찾으면 된다.
	// 심지어 10의 승수 또한 모듈러 연산으로 분해되므로 매 이터레이션마다 모듈러 연산을 해주면 오버플로우도 방지할 수 있다.
	n *= 9
	k := 0
	mod := 1
	for {
		k++
		mod = (mod * 10) % n
		if mod == 1 {
			return k
		}
	}
}

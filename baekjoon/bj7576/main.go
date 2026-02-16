package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
    reader := bufio.NewReader(os.Stdin)
	var m, n int
	fmt.Fscan(reader, &m, &n)
	tomatoes := make([][]int, n)
	for i := range n {
		tomatoes[i] = make([]int, m)
		for j := range m {
			fmt.Fscan(reader, &tomatoes[i][j])
		}
	}
	fmt.Println(solution(tomatoes))
}

type point struct {
	x, y, d int
}

func solution(tomatoes [][]int) int {
	n, m := len(tomatoes), len(tomatoes[0])
	outbound := func(p point) bool {
		return !(0 <= p.x && p.x < m && 0 <= p.y && p.y < n)
	}
	dirs := [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

	queue := []point{}
	for i, row := range tomatoes {
		for j, tomato := range row {
			if tomato == 1 {
				// 익은 토마토들을 첫 탐색 지점으로 설정
				queue = append(queue, point{j, i, 0})
			}
		}
	}

	maxDay := 0
	for len(queue) > 0 {
		p := queue[0]
		queue = queue[1:]

		// 상하좌우 큐에 넣기
		for _, dir := range dirs {
			np := point{p.x + dir[0], p.y + dir[1], p.d + 1}
			if outbound(np) {
				// 경계 밖인 경우
				continue
			}

			if tomatoes[np.y][np.x] == 0 {
				// 익지 않은 토마토인 경우
				tomatoes[np.y][np.x] = 1
				queue = append(queue, np)
				maxDay = max(maxDay, np.d)
			}
		}
	}

	for i := range n {
		for j := range m {
			if tomatoes[i][j] == 0 {
				return -1
			}
		}
	}
	return maxDay
}

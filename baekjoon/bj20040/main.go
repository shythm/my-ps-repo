package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	sc := bufio.NewScanner(os.Stdin)
	sc.Split(bufio.ScanWords)

	// 또 시간초과 나서 추가한 더 빠른 입력 방법
	nextInt := func() int {
		sc.Scan()
		num, _ := strconv.Atoi(sc.Text())
		return num
	}

	n := nextInt()
	m := nextInt()
	
	lines := make([]Line, m)
	for i := range m {
		start := nextInt()
		end := nextInt()
		lines[i] = Line{ start, end }
	}

	answer := Solution(n, lines)
	fmt.Println(answer)
}

type Set struct {
	roots []int
	ranks []int
}

func NewSet(size int) *Set {
	roots := make([]int, size)
	ranks := make([]int, size)
	for i := range size {
		roots[i] = i
	}
	return &Set{ roots: roots, ranks: ranks }
}

func (set *Set) FindRoot(x int) int {
	if (set.roots[x] != x) {
		set.roots[x] = set.FindRoot(set.roots[x])
	}
	return set.roots[x]
}

func (set *Set) Union(x, y int) bool {
	xRoot := set.FindRoot(x)
	yRoot := set.FindRoot(y)
	if xRoot == yRoot { // 같은 집합이라면
		return true
	}

	// 시간초과나서 추가한 Union By Rank 알고리즘: 다른 집합이면 rank가 더 큰 트리 밑으로 편입시킨다.
	if set.ranks[xRoot] < set.ranks[yRoot] {
		set.roots[xRoot] = yRoot
	} else if set.ranks[xRoot] > set.ranks[yRoot] {
		set.roots[yRoot] = xRoot
	} else {
		set.roots[xRoot] = yRoot
		set.ranks[yRoot]++
	}
	return false
}

type Line struct {
	start, end int
}

func Solution(dotCnt int, lines []Line) int {
	set := NewSet(dotCnt)

	for i, v := range lines {
		if set.Union(v.start, v.end) {
			return i+1
		}
	}
	return 0
}

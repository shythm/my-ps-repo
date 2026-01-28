package main

import (
	"fmt"
)

type Tuple[T comparable] struct {
	X1, X2 T
}

func main() {
	caseNum := 0
	for {
		var n, m int
		fmt.Scanf("%d %d", &n, &m)
		if n == 0 && m == 0 {
			break
		}

		caseNum++
		edges := make([]Tuple[int], m)
		for i := range m {
			var x1, x2 int
			fmt.Scanf("%d %d", &x1, &x2)
			edges[i] = Tuple[int]{ X1: x1 - 1, X2: x2 - 1 }
		}

		answer := solution(n, edges)
		fmt.Printf("Case %d: ", caseNum)
		switch answer {
		case 0:
			fmt.Printf("No trees.\n")
		case 1:
			fmt.Printf("There is one tree.\n")
		default:
			fmt.Printf("A forest of %d trees.\n", answer)
		}
	}
}

func solution(nodeCnt int, edges []Tuple[int]) int {
	ds := NewDisjointSet(nodeCnt)
	cycleRoots := make([]bool, nodeCnt)

	for _, v := range edges {
		if ds.Union(v.X1, v.X2) { // 사이클 존재 시
			cycleRoots[ds.FindRoot(v.X1)] = true
		}
	}

	// 노드를 전수조사하여 루트 노드 구하기
	rootSet := make(map[int]struct{})
	for i := range nodeCnt {
		root := ds.FindRoot(i)
		rootSet[root] = struct{}{}
	}
	// 그러나 그 트리가 사이클이 있다면 제외하기
	for i, cycle := range cycleRoots {
		if cycle {
			root := ds.FindRoot(i)
			delete(rootSet, root)
		}
	}
	return len(rootSet)
}

type DisjointSet struct {
	roots []int
	ranks []int
}

func NewDisjointSet(size int) *DisjointSet {
	roots := make([]int, size)
	for i := range size {
		roots[i] = i
	}
	ranks := make([]int, size)
	return &DisjointSet{ roots: roots, ranks: ranks }
}

func (ds *DisjointSet) FindRoot(x int) int {
	if ds.roots[x] != x {
		ds.roots[x] = ds.FindRoot(ds.roots[x])
	}
	return ds.roots[x]
}

func (ds *DisjointSet) Union(x, y int) bool {
	xRoot := ds.FindRoot(x)
	yRoot := ds.FindRoot(y)
	if xRoot == yRoot {
		return true
	}

	if ds.ranks[xRoot] < ds.ranks[yRoot] {
		ds.roots[xRoot] = ds.roots[yRoot]
	} else if ds.ranks[xRoot] > ds.ranks[yRoot] {
		ds.roots[yRoot] = ds.roots[xRoot]
	} else {
		ds.roots[yRoot] = ds.roots[xRoot]
		ds.ranks[xRoot]++;
	}
	return false
}

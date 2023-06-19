# DFS로 cycle path 조사하기

from sys import stdin

T = int(stdin.readline().strip())
for _ in range(T):
    N = int(stdin.readline().strip())

    # 순열 배열 만들기
    permutation = list(map(int, stdin.readline().strip().split()))
    permutation.insert(0, 0)

    # 방문 여부를 저장하는 공간
    visited = [False for _ in range(N + 1)]

    # 사이클 수
    num = 0

    for i in range(1, N + 1):
        
        # 이미 방문한 곳이면 넘어가기
        if visited[i]:
            continue

        cur = i
        visited[cur] = True

        # 경로 따라가기
        while (cur := permutation[cur]) != i:
            visited[cur] = True

        num += 1

    print(num)

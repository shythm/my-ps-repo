# Prim으로 했는데 잘 안돼서... (예제 데이터는 모두 다 잘 되는데...)
# Kruskal 알고리즘을 사용해보기로 했다.
# 맞았다. 잘 된다.

# https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
# 1. Sort all the edges in non-decreasing order of their weight. 
# 2. Pick the smallest edge.
#    Check if it forms a cycle with the spanning tree formed so far.
#    If the cycle is not formed, include this edge. Else, discard it.
# 3. Repeat step 2 until there are (V-1) edges in the spanning tree.

from sys import stdin

# N: 도시, M: 케이블, K: 발전소
N, M, K = map(int, stdin.readline().split())

# 발전소 리스트
power_station = list(map(int, stdin.readline().split()))

# graph 정보 입력받기
graph = [tuple(map(int, stdin.readline().split())) for _ in range(M)]
    
# union-find algorithm
def union(parent, x, y):
    x = find(parent, x)
    y = find(parent, y)
    
    if x < y:
        parent[y] = x
    else:
        parent[x] = y

def find(parent, x):
    while x != parent[x]:
        x = parent[x]
        
    return x

parent = [x for x in range(N + 1)]

# 발전소는 미리 union 시켜놓기
for ps in power_station:
    union(parent, ps, power_station[0])

# weight 정렬하기
graph.sort(key=lambda x: x[2])

# kruskal algorithm
# mst = []
mst = 0

while len(graph):
    u, v, w = graph.pop(0)

    pu = find(parent, u)
    pv = find(parent, v)

    if pu != pv:
        # mst.append((u, v, w))
        mst += w
        union(parent, u, v)

print(mst)
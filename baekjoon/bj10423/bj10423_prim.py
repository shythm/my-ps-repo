# KEY POINT
# 발전소의 인접 도시들의 최소 비용을 가중치로 하여
# 발전소들끼리 complete graph를 형성하여 MST 알고리즘을 수행한다.

from sys import stdin, stdout
from enum import Enum

# N: 도시(vertex) 개수, M: 케이블(edge) 개수, K: 발전소 개수
N, M, K = (int(x) for x in stdin.readline().strip().split())

# N개의 adjacency list를 담을 list 생성 (city, weight)
adj = [[] for _ in range(N + 1)]

# K개의 발전소 리스트 (power, weight)
power = [int(x) for x in stdin.readline().strip().split()]

# M개의 두 도시를 연결하는 케이블의 정보 입력
for m in range(M):
    u, v, w = (int(x) for x in stdin.readline().strip().split())
    # 추가) 만약 두 도시에 모두 발전소가 있다면 무시해버리자
    if u in power and v in power:
        continue

    adj[u].append((v, w))
    adj[v].append((u, w))

# 발전소 초기화
power_weight = []
for p in power:
    # p에 인접한 도시 중 가장 작은 가중치 선택
    _, w = min(adj[p], key=lambda x: x[1])
    power_weight.append((p, w))

# 발전소끼리 연결하기
for i, p in enumerate(power):
    adj[p].extend([(v, w) for v, w in power_weight if v != p])

# print(adj)

MAX_WEIGHT = 10000

#########################
# Prim의 MST 알고리즘 수행
#########################

# MST Table 생성 (status, parent, weight, adjacency list)
class Status(Enum):
    UNSEEN = 0
    FRINGE = 1
    INTREE = 2
    PWRSTA = 3

status: list[Status] = [Status.UNSEEN for _ in range(N + 1)]
parent: list[int] = [0 for _ in range(N + 1)]
weight: list[int] = [MAX_WEIGHT for _ in range(N + 1)] # 사실 이건 MAX_WEIGHT로 초기화해 줄 필욘 없다 (UNSEEN Status일 때 업데이트하기 때문)
fringe: list[int] = []
edge_count: int = 0
stuck: bool = False

city: int = 1 # 처음 방문할 도시
status[city] = Status.INTREE
weight[city] = 0

while edge_count < N - 1: # MST의 edge 수는 vertex 수 보다 하나 작다

    # city의 인접 노드들을 검사하여 MST Table 업데이트
    for c, w in adj[city]:

        # 방문하지 않은 노드인 경우, 후보로 등록 = MST Table 등록
        if status[c] == Status.UNSEEN:
            status[c] = Status.FRINGE
            parent[c] = city
            weight[c] = w
            fringe.append(c)
            
        # 이미 방문했던 노드라면, c와 city 사이의 경로가 더 짧은 경우 업데이트
        if status[c] == Status.FRINGE and w < weight[c]:
            parent[c] = city
            weight[c] = w

    if len(fringe) == 0: break # 더 이상 fringe 노드가 없으면 탐색 종료
    else:
        # fringe 노드들 중 가장 가중치가 작은 city 고르기
        selected = 0
        min_weight = MAX_WEIGHT
        for c in fringe:
            if weight[c] < min_weight:
                selected = c
                min_weight = weight[c]
        
        city = selected
        status[city] = Status.INTREE
        fringe.remove(city)
        edge_count += 1
    
# print('status', status)
# print('weight', weight)
# print('parent', parent)

# 발전소끼리 연결된 그래프는 무효로 하고 총 가중치 구하기
for p in power:
    status[p] = Status.PWRSTA

ret = 0
for c in range(1, N + 1):
    if status[c] == Status.PWRSTA and status[parent[c]] == Status.PWRSTA:
        continue

    if status[c] == Status.INTREE:
        ret += weight[c]

print(ret)
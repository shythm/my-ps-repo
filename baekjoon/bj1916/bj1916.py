# 최단 경로 문제: Dijkstra Algorithm을 이용하여
# 컴퓨터알고리즘 수업 시간에 배운 Dijkstra Algorithm 활용해보자

from sys import stdin

# 도시의 개수 (도시의 번호: 1부터 시작)
MAX_CITY = 1000
N = int(stdin.readline().strip())

# 버스의 개수
M = int(stdin.readline().strip())

# 버스의 정보 (출발지 도시 번호, 도착지 도시 번호, 버스 비용)
# 이떄 버스의 비용은 0이상 100000미만이다. 비용이 0일 때의 처리는 어떻게 하면 좋을까?
adj = [[] for _ in range(N + 1)]
for _ in range(M):
    u, v, w = tuple(map(int, stdin.readline().strip().split()))
    adj[u].append((v, w))
    # adj[v].append((u, w)) # 유향 그래프였다...

# 구하려는 최단 경로(출발지 도시 번호 - 도착지 도시 번호)
start, end = tuple(map(int, stdin.readline().strip().split()))

UNSEEN = 0
FRINGE = 1
INTREE = 2
status = [UNSEEN for _ in range(N + 1)]

MAX_WEIGHT = 100000 - 1
dist = [MAX_WEIGHT for _ in range(N + 1)]

# parent = [0 for _ in range(N + 1)]
fringe = []

status[start] = INTREE
dist[start] = 0
# parent[start] = start
curr = start

while curr != end:
    
    # 현재 도시와 인접한 도시 탐색
    for c, w in adj[curr]:

        # 후보 비용 (curr를 지나 c로 가는 경로 비용)
        cand = dist[curr] + w

        # 만약, c가 이미 방문했던 노드(FRINGE)라면,
        # 현재 도시를 거쳐서 c로 도달하는 비용을 계산해서 업데이트
        if status[c] == FRINGE and cand < dist[c]:
            dist[c] = cand
            # parent[c] = curr
        # 만약, c가 처음 방문하는 노드(UNSEEN)라면, 방문한 노드 상태로 업데이트
        elif status[c] == UNSEEN:
            dist[c] = cand # dist[c] = w만 해버렸음... 이러면 안되지.
            # parent[c] = curr
            status[c] = FRINGE
            fringe.append(c)

    # 더 이상 탐색할 도시가 없으면, 종료
    if len(fringe) == 0:
        break

    # 가장 짧은 경로 구하기
    shortest = 0
    #############
    # 이 부분 실수!
    # 아 그렇구나, 가중치의 최댓값이 아니라 이 값들을 가능한 한 모두 합한 것으로 해야하구나.
    #############
    shortest_dist = (MAX_CITY - 1) * MAX_WEIGHT + 1
    fringe_idx = 0
    for i, f in enumerate(fringe):
        if dist[f] < shortest_dist:
            shortest = f
            shortest_dist = dist[f]
            fringe_idx = i # 속도 최적화

    status[shortest] = INTREE
    # fringe.remove(shortest)
    fringe.pop(fringe_idx) # 속도 최적화
    curr = shortest

# print('status', status)
# print('dist', dist)
# print('parent', parent)
print(dist[end])

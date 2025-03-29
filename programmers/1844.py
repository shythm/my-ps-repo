import heapq

def _solution(maps):
    answer = -1
    
    n, m = len(maps), len(maps[0])
    
    # 인접 노드를 저장하는 자료구조 생성
    adjacent_nodes = [[[] for _ in range(m)] for _ in range(n)]
    for x in range(n):
        for y in range(m):
            if not maps[x][y]:
                continue

            # 상
            if x > 0 and maps[x - 1][y]:
                adjacent_nodes[x][y].append((x - 1, y))
            # 하
            if x < n - 1 and maps[x + 1][y]:
                adjacent_nodes[x][y].append((x + 1, y))
            # 좌
            if y > 0 and maps[x][y - 1]:
                adjacent_nodes[x][y].append((x, y - 1))
            # 우
            if y < m - 1 and maps[x][y + 1]:
                adjacent_nodes[x][y].append((x, y + 1))
    
    print(adjacent_nodes)
    # 방문한 노드 기록
    visited_nodes = [[False for _ in range(m)] for _ in range(n)]
    
    min_paths = []
    heapq.heappush(min_paths, (0, (0, 0)))  # (거리 0, 좌표 (0, 0)) 삽입
    
    while len(min_paths):
        depth, (x, y) = heapq.heappop(min_paths)
        
        if visited_nodes[x][y]:
            continue
        visited_nodes[x][y] = True
        
        # 조기 종료 조건
        if x == n - 1 and y == m - 1:
            answer = depth + 1  # 지나간 칸 수를 계산해야 함
            break
        
        for adj_x, adj_y in adjacent_nodes[x][y]:
            if visited_nodes[adj_x][adj_y]:
                continue
            
            heapq.heappush(min_paths, (depth + 1, (adj_x, adj_y)))
        
    return answer

"""
최단 경로 문제라서 데이크스트라(dijkstra) 알고리즘을 이용했는데,
모든 간선의 가중치가 동일한 경우에는 BFS 기법으로도 최단 경로를 구할 수 있음.

처음에 일반 리스트를 사용해서 구현했지만, 이는 동적배열이므로 맨 앞의 데이터를 추출할 때 O(n)의 연산이 수행됨.
Double-ended Queue(deque)를 사용하여 최적화를 더 수행할 수 있음.
"""
from collections import deque

def solution(maps):
    n, m = len(maps), len(maps[0])
    movements = [(0, -1), (0, 1), (-1, 0), (1, 0)]  # 상, 하, 좌, 우
    depths = [[-1 for _ in range(m)] for _ in range(n)]
    
    queue = deque()
    queue.append((0, 0))
    depths[0][0] = 1
    
    while len(queue):
        cx, cy = queue.popleft()
        
        for dx, dy in movements:
            tx, ty = cx + dx, cy + dy

            # 범위 확인
            if not (-1 < tx < m and -1 < ty < n):
                continue
            # 갈 수 없는 곳인지 확인
            if not maps[ty][tx]:
                continue
            # 이미 방문한 노드 확인
            if depths[ty][tx] != -1:
                continue
            
            depths[ty][tx] = depths[cy][cx] + 1
            queue.append((tx, ty))
    
    return depths[-1][-1]

"""
리스트를 사용한 경우
테스트 1 〉	통과 (10.70ms, 10.3MB)
테스트 2 〉	통과 (2.85ms, 10.4MB)
테스트 3 〉	통과 (11.61ms, 10.4MB)
테스트 4 〉	통과 (4.74ms, 10.3MB)

덱을 사용한 경우
테스트 1 〉	통과 (10.41ms, 10.4MB)
테스트 2 〉	통과 (3.09ms, 10.3MB)
테스트 3 〉	통과 (6.80ms, 10.3MB)
테스트 4 〉	통과 (4.51ms, 10.4MB)

비슷,,, 하네?
"""

print(solution([[1,0,1,1,1],[1,0,1,0,1],[1,0,1,1,1],[1,1,1,0,1],[0,0,0,0,1]]))
print(solution([[1,0]]))
print(solution([[1,0],[0,0]]))
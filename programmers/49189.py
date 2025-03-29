def solution2(n, edge):
    # 최단 경로를 저장할 배열, 가중치를 1로 가정했을 때의 최대 경로는 (n - 1)
    shortest_paths = [n] + [n for _ in range(n)]
    visited_nodes = [True] + [False for _ in range(n)]
    
    # 그래프를 저장할 자료구조(2차원 리스트)
    graph = [[] for _ in range(n + 1)]
    for e in edge:
        v1, v2 = e
        graph[v1].append(v2)
        graph[v2].append(v1)
    
    # Dijkstra 알고리즘 초기화
    shortest_paths[1] = 0

    while True:
        # 현재까지의 최단 경로(시간 복잡도 O(n))
        shortest_path = n
        shortest_node = 0
        for idx, value in enumerate(shortest_paths):
            if visited_nodes[idx]:
                continue
            if value < shortest_path:
                shortest_path = value
                shortest_node = idx
        
        # 종료 조건 확인: 더 이상 방문할 노드가 없을 때
        if shortest_node == 0:
            break
        
        # 방문 여부 갱신
        visited_nodes[shortest_node] = True
        
        # 최단 경로를 가진 노드의 인접 노드 경로 갱신
        for adjacent_node in graph[shortest_node]:
            if visited_nodes[adjacent_node]:
                continue

            # 다음 노드의 거리가 최단경로인지 확인: 가중치는 항상 1
            target_path = shortest_path + 1
            if target_path < shortest_paths[adjacent_node]:
                shortest_paths[adjacent_node] = target_path

    answer = 1
    max_path = 0
    for value in shortest_paths[1:]:
        if value > max_path:
            max_path = value
            answer = 1
            continue
        
        if value == max_path:
            answer += 1

    return answer

import heapq

def solution(n, edge):
    answer = 0
    
    # 그래프를 저장할 자료구조(2차원 리스트)
    graph = [[] for _ in range(n + 1)]
    for e in edge:
        v1, v2 = e
        graph[v1].append(v2)
        graph[v2].append(v1)
    
    # Dijkstra 알고리즘 초기화
    visited_nodes = [True] + [False for _ in range(n)]
    target_nodes = []
    heapq.heappush(target_nodes, (0, 1))

    max_path = 0
    while len(target_nodes):
        # 현재까지의 최단 경로(시간 복잡도 O(n))
        shortest_path, shortest_node = heapq.heappop(target_nodes)

        # 방문 여부 확인 및 갱신
        if visited_nodes[shortest_node]:
            continue
        
        visited_nodes[shortest_node] = True
        if shortest_path > max_path:
            max_path = shortest_path
            answer = 0

        if shortest_path == max_path:
            answer += 1
        
        # 인접 노드 순회
        for adjacent_node in graph[shortest_node]:
            if visited_nodes[adjacent_node]:
                continue
            
            # 계산된 경로를 힙에 추가
            heapq.heappush(target_nodes, (shortest_path + 1, adjacent_node))

    return answer

print(solution(6, [[3, 6], [4, 3], [3, 2], [1, 3], [1, 2], [2, 4], [5, 2]]))
print(solution(6, [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6]]))
print(solution(6, [[1, 2]]))
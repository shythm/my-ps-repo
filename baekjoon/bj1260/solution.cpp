#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>

// #define DEBUG

using namespace std;

void dfs(vector<vector<int>> graph, int start_vertex) {
    stack<int> s;
    vector<bool> visited(graph.size(), false);

    // 내림차순 정렬
    for (auto& adjacent_verticies : graph) {
        sort(adjacent_verticies.begin(), adjacent_verticies.end(), greater<int>());
    }

    s.push(start_vertex);

    while (!s.empty()) {
        auto top = s.top();
        s.pop();
        if (visited[top]) {
            continue;
        }

        cout << top << ' ';
        visited[top] = true;

        for (const auto& adjacent_vertex : graph[top]) {
            s.push(adjacent_vertex);
        }
    }
    cout << '\n';
}

void bfs(vector<vector<int>> graph, int start_vertex) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);

    q.push(start_vertex);
    visited[start_vertex] = true;

    // 내림차순 정렬
    for (auto& adjacent_verticies : graph) {
        sort(adjacent_verticies.begin(), adjacent_verticies.end());
    }

    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        cout << front << ' ';

        for (const auto& adjacent_vertex : graph[front]) {
            if (visited[adjacent_vertex]) {
                continue;
            }
            q.push(adjacent_vertex);
            visited[adjacent_vertex] = true;
        }
    }
    cout << '\n';
}

int main(void) {
    int N, M, start_vertex;
    cin >> N >> M >> start_vertex;

    vector<vector<int>> graph(N + 1);
    for (int i = 0; i < M; i++) {
        int start, end;
        cin >> start >> end;
        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    #ifdef DEBUG
    for (int i = 0; i < graph.size(); i++) {
        cout << i << endl;
        for (const auto& elem : graph[i]) {
            cout << elem << ' ';
        }
        cout << endl;
    }
    cout << endl;
    #endif

    dfs(graph, start_vertex);
    bfs(graph, start_vertex);

    return 0;
}

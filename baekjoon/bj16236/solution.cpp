#include <vector>
#include <deque>
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

// #define DEBUG

struct space {
    int i;
    int j;
    int time;

    bool operator<(const space& other) const {
        if (time != other.time) {
            return time > other.time;
        }
        if (i != other.i) {
            return i > other.i;
        }
        return j > other.j;
    }
};

bool is_valid_space(const space& target, int map_size) {
    if (
        (0 <= target.i && target.i < map_size) &&
        (0 <= target.j && target.j < map_size)
    ) {
        return true;
    }
    return false;
}

int calc_shark_weight(int eaten_count) {
    int weight = 2;
    while (eaten_count > 0) {
        if (eaten_count / weight) {
            eaten_count -= weight;
            weight++;
        } else {
            break;
        }
    }
    return weight;
}

int solution(vector<vector<int>>& map) {
    /**
     * 우선순위 큐에 탐색할 지점을 넣으며 먹을 수 있는 물고기를 찾아가자.
     * 1. 거리에 대해 오름차순
     * 2. 행에 대해 오름차순
     * 3. 열에 대해 오름차순
     */
    int answer = 0; // 아기 상어가 이동한 시간
    size_t map_size = map.size();

    space shark_init_pos; // (거리, 행, 열)

    // 아기 상어의 위치 구하기
    bool shark_init_pos_found = false;
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            if (map[i][j] == 9) { // 9가 있는 곳이 아기 상어의 위치
                map[i][j] = 0; // 빈 공간으로 놓기
                shark_init_pos.i = i;
                shark_init_pos.j = j;
                shark_init_pos_found = true;
                break;
            }
        }
        if (shark_init_pos_found) break;
    }

    priority_queue<space> search_points;
    vector<vector<bool>> visited_points(map_size, vector<bool>(map_size, false));
    int eaten_count = 0; // 아기 상어가 먹은 물고기 수
    int shark_weight_cache = calc_shark_weight(eaten_count);

    // 초기값
    search_points.push(shark_init_pos);
    visited_points[shark_init_pos.i][shark_init_pos.j] = true;

    while (!search_points.empty()) {
        space sp = search_points.top();
        search_points.pop();

        #ifdef DEBUG
        cout << "search point: " << sp.i << ", " << sp.j << ", " << sp.time << endl;
        #endif

        // 먹을 수 있는 물고기인지 확인하자
        if (0 < map[sp.i][sp.j] && map[sp.i][sp.j] < shark_weight_cache) {
            map[sp.i][sp.j] = 0; // 아기 상어가 물고기를 먹는 행위 수행
            shark_weight_cache = calc_shark_weight(++eaten_count); // 상어 무게 갱신
            answer += sp.time; // 아기 상어가 돌아다닌 시간 추가
            sp.time = 0; // 다음 탐색 지점 큐에 넣기 전에 시간 초기화
            while (!search_points.empty()) { // 우선순위 큐 비우기
                search_points.pop();
            }
            for (int i = 0; i < map_size; i++) { // 재탐색을 위해 방문 여부 초기화
                for (int j = 0; j < map_size; j++) {
                    visited_points[i][j] = false;
                }
            }
            visited_points[sp.i][sp.j] = true;

            #ifdef DEBUG
            cout << "shark weight: " << shark_weight_cache << endl;
            for (int i = 0; i < map_size; i++) {
                for (int j = 0; j < map_size; j++) {
                    if (i == sp.i && j == sp.j) {
                        cout << " v";
                        continue;
                    }
                    cout << " " << map[i][j];
                }
                cout << endl;
            }
            cout << "answer: " << answer << endl;
            #endif
        }

        // 다음 탐색 지점 큐에 넣자
        space next_search_points[4] = {
            { .i = sp.i - 1, .j = sp.j, .time = sp.time + 1 }, // 상
            { .i = sp.i, .j = sp.j - 1, .time = sp.time + 1 }, // 좌
            { .i = sp.i, .j = sp.j + 1, .time = sp.time + 1 }, // 우
            { .i = sp.i + 1, .j = sp.j, .time = sp.time + 1 }, // 하
        };
        for (auto nsp : next_search_points) {
            if (is_valid_space(nsp, map_size) == false) { // 유효한 위치인지 검사한다.
                continue;
            }
            if (
                (visited_points[nsp.i][nsp.j] == true) || // 이미 방문한 노드는 큐에 넣지 않는다.
                (map[nsp.i][nsp.j] > shark_weight_cache) // 아기 상어는 자신보다 큰 물고기가 있는 칸은 지나갈 수 없다.
            ) {
                continue;
            }

            visited_points[nsp.i][nsp.j] = true;
            search_points.push(nsp);

            #ifdef DEBUG
            cout << "queued: " << nsp.i << ", " << nsp.j << ", " << nsp.time << endl;
            #endif
        }
    }

    return answer;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> map(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int value;
            cin >> value;
            map[i][j] = value;
        }
    }

    int answer = solution(map);
    cout << answer;

    return 0;
}
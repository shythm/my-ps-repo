#include <vector>
#include <tuple>
#include <iostream>

// #define DEBUG

using namespace std;

enum map_type {
    MAP_TYPE_NONE = 0,
    MAP_TYPE_CCTV_1,
    MAP_TYPE_CCTV_2,
    MAP_TYPE_CCTV_3,
    MAP_TYPE_CCTV_4,
    MAP_TYPE_CCTV_5,
    MAP_TYPE_WALL,
    MAP_TYPE_SIZE
};

enum map_dir {
    MAP_DIR_NORTH = 0,
    MAP_DIR_EAST,
    MAP_DIR_SOUTH,
    MAP_DIR_WEST
};

#define MAP_STATE_NONE       0x00
#define MAP_STATE_NORTH      0x01    // 0001
#define MAP_STATE_EAST       0x02    // 0010
#define MAP_STATE_SOUTH      0x04    // 0100
#define MAP_STATE_WEST       0x08    // 1000
#define MAP_STATE_VISITED    0xFF    // 1111

inline void update_map_state(
    vector<vector<int>>& map_state,     // 갱신할 맵 상태
    const tuple<int, int>& position,    // 탐색 위치
    const map_dir& direction           // 탐색 방향
) {
    int di, dj, mask;
    switch (direction) {
    case MAP_DIR_NORTH:
        di = -1, dj = 0, mask = MAP_STATE_NORTH;
        break;
    case MAP_DIR_EAST:
        di = 0, dj = 1, mask = MAP_STATE_EAST;
        break;
    case MAP_DIR_SOUTH:
        di = 1, dj = 0, mask = MAP_STATE_SOUTH;
        break;
    case MAP_DIR_WEST:
        di = 0, dj = -1, mask = MAP_STATE_WEST;
        break;
    }

    int row_num = map_state.size();
    int col_num = map_state[0].size();

    int i = get<0>(position);
    int j = get<1>(position);
    while (
        // 범위 내에서 탐색
        (0 <= i && i < row_num) && (0 <= j && j < col_num)
    ) {
        if (map_state[i][j] & mask) {
            // 이미 해당 방향으로 탐색했다면 탈출하기
            break;
        }
        map_state[i][j] |= mask;
        i += di;
        j += dj;
    }
}

int solution(
    const vector<vector<map_type>>& map // CCTV 지도
) {
    int row_num = map.size();
    int col_num = map[0].size();

    /**
     * 지도의 상태를 나타내는 3차원 배열이다.
     * 최상위 차원은 지도의 개별 상태를 나타내고, 나머지 두 개의 하위 차원들은 좌표를 나타낸다.
     * 지도를 탐색하면서 새로운 CCTV가 나타나면 새로운 상태를 만들어낼 것이다.
     * 예를 들어, 4개의 상태가 있었고, 1번 CCTV를 만나게 되면 4배의 상태로 불어나 16개의 상태가 될 것이다.
     */
    vector<vector<vector<int>>> map_states;
    vector<vector<vector<int>>> renewed_map_states;

    // 초기 상태 추가
    map_states.emplace_back(row_num, vector<int>(col_num, MAP_STATE_NONE));
    auto& init_map_state = map_states.back();
    for (int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            if (map[i][j] == MAP_TYPE_WALL) {
                /**
                 * 벽이 있는 공간에는 방문한 것으로 두어,
                 * 1. 어느 방향으로든 더 이상 탐색을 진행하지 않도록 하고,
                 * 2. 마지막 사각지대를 구할 때 해당 구역을 제외할 수 있도록 한다.
                 */
                init_map_state[i][j] = MAP_STATE_VISITED;
            }
        }
    }

    vector<vector<vector<map_dir>>> map_type_to_map_dirs(MAP_TYPE_SIZE);
    map_type_to_map_dirs[MAP_TYPE_CCTV_1] = {
        { MAP_DIR_NORTH },
        { MAP_DIR_EAST },
        { MAP_DIR_SOUTH },
        { MAP_DIR_WEST },
    };
    map_type_to_map_dirs[MAP_TYPE_CCTV_2] = {
        { MAP_DIR_NORTH, MAP_DIR_SOUTH },
        { MAP_DIR_EAST, MAP_DIR_WEST },
    };
    map_type_to_map_dirs[MAP_TYPE_CCTV_3] = {
        { MAP_DIR_NORTH, MAP_DIR_EAST },
        { MAP_DIR_EAST, MAP_DIR_SOUTH },
        { MAP_DIR_SOUTH, MAP_DIR_WEST },
        { MAP_DIR_WEST, MAP_DIR_NORTH },
    };
    map_type_to_map_dirs[MAP_TYPE_CCTV_4] = {
        { MAP_DIR_NORTH, MAP_DIR_EAST, MAP_DIR_SOUTH },
        { MAP_DIR_EAST, MAP_DIR_SOUTH, MAP_DIR_WEST },
        { MAP_DIR_SOUTH, MAP_DIR_WEST, MAP_DIR_NORTH},
        { MAP_DIR_WEST, MAP_DIR_NORTH, MAP_DIR_EAST },
    };
    map_type_to_map_dirs[MAP_TYPE_CCTV_5] = {
        { MAP_DIR_NORTH, MAP_DIR_EAST, MAP_DIR_SOUTH, MAP_DIR_WEST },
    };

    for (int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            const auto& map_type = map[i][j];

            switch (map_type) {
            case MAP_TYPE_CCTV_1:
            case MAP_TYPE_CCTV_2:
            case MAP_TYPE_CCTV_3:
            case MAP_TYPE_CCTV_4:
            case MAP_TYPE_CCTV_5: {
                renewed_map_states.clear();
                auto position = make_tuple(i, j);
                const auto& directions_to_explorer = map_type_to_map_dirs[map_type];
                renewed_map_states.reserve(map_states.size() * directions_to_explorer.size());
                for (const auto& map_state : map_states) {
                    for (const auto& directions : directions_to_explorer) {
                        auto new_map_state = map_state;
                        for (const auto& dir : directions) {
                            update_map_state(new_map_state, position, dir);
                        }
                        renewed_map_states.push_back(new_map_state);
                    }
                }
                map_states = renewed_map_states;

                #ifdef DEBUG
                cout << "reached at " << map_type << ", renewed_map_states.size() = " << renewed_map_states.size() << endl;
                #endif

                break;
            }
            default:
                break;
            }
        }
    }

    // 최소 크기 구하기
    int min_blind_spot_num = 64; // N, M의 최댓값이 8이므로, 64가 사각지대의 최댓값이 된다.
    for (const auto& map_state : map_states) {
        int blind_spot_num = 0;
        for (int i = 0; i < row_num; i++) {
            for (int j = 0; j < col_num; j++) {
                if (map_state[i][j] == 0) {
                    blind_spot_num++;
                }
            }
        }
        if (min_blind_spot_num > blind_spot_num) {
            min_blind_spot_num = blind_spot_num;
        }

        #ifdef DEBUG
        cout << "map state log, blind spot num: " << blind_spot_num << endl;
        for (int i = 0; i < row_num; i++) {
            for (int j = 0; j < col_num; j++) {
                cout << map_state[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        #endif
    }

    return min_blind_spot_num;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<map_type>> map(N, vector<map_type>(M, MAP_TYPE_NONE));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int item;
            cin >> item;
            map[i][j] = static_cast<map_type>(item);
        }
    }

    int answer = solution(map);
    cout << answer;

    return 0;
}

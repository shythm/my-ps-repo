#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <iostream>

// #define DEBUG

using namespace std;
using min_heap = priority_queue<int, vector<int>, greater<int>>;

int solution(
    int map_size, // 땅의 크기
    const vector<vector<int>>& s2d2_nutrients_map, // s2d2 로봇이 추가할 양분
    const vector<tuple<int, int, int>>& initial_tree_info, // 초기 나무 정보: x, y, age
    int years // 몇 년 뒤를 시뮬레이션?
) {
    /**
     * 1. 봄: 나무가 자신의 나이만큼 양분을 먹고, 나이가 1증가.
     *   - 양분은 1x1 크기의 칸에 있는 양분만 먹음.
     *   - 나이가 어린 나무부터 양분을 먹음.
     *   - 자신의 나이만큼 양분을 먹을 수 없는 경우 죽음.
     * 2. 여름: 봄에 죽은 나무가 양분으로 변하게 됨.
     *   - 죽은 나무의 나이를 2로 나눈 값이 양분으로 추가.
     * 3. 가을: 나무가 번식.
     *   - 나무의 나이가 5의 배수인 경우에만 번식.
     *   - 인접한 8개의 칸에 나이가 1인 나무가 생김.
     * 4. 겨울: 로봇이 돌아다니면서 땅에 양분을 추가. 각 칸에 추가되는 양분의 양은 정해져 있음.
     */
    vector<vector<int>> nutrients_map(map_size, vector<int>(map_size, 5));
    vector<vector<min_heap>> tree_ages(map_size, vector<min_heap>(map_size, min_heap()));

    // 초기 나무 정보 반영
    for (const auto& item : initial_tree_info) {
        int i = get<0>(item) - 1;
        int j = get<1>(item) - 1;
        int age = get<2>(item);
        tree_ages[i][j].push(age);
    }

    // 인접한 공간 배열 선언
    const int di_arr[8] = { -1, -1, -1,  0,  0,  1,  1,  1 };
    const int dj_arr[8] = { -1,  0,  1, -1,  1, -1,  0,  1 };

    while (years > 0) {
        vector<vector<int>> number_of_breeding(map_size, vector<int>(map_size, 0));

        // 봄, 여름
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                min_heap renewed_tree_ages;

                while (!tree_ages[i][j].empty()) {
                    int age = tree_ages[i][j].top(); // 나이가 어린 나무부터 양분을 먹음.
                    if (age > nutrients_map[i][j]) {
                        break; // 자신의 나이만큼 양분을 먹을 수 없는 경우 죽음.
                    }
                    nutrients_map[i][j] -= age;

                    int new_age = age + 1;
                    renewed_tree_ages.push(new_age);

                    if (new_age % 5 == 0) {
                        number_of_breeding[i][j] += 1; // 번식할 나무 수 추가
                    }
                    tree_ages[i][j].pop();
                }

                while (!tree_ages[i][j].empty()) {
                    int age = tree_ages[i][j].top();
                    // 양분을 먹지 못한 나무는 나이를 2로 나눈 값이 양분으로 다시 추가됨
                    nutrients_map[i][j] += age / 2;
                    tree_ages[i][j].pop();
                }

                // 양분을 먹은 나무들은 복구
                tree_ages[i][j] = std::move(renewed_tree_ages);
            }
        }

        // 가을
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                int count = number_of_breeding[i][j];
                if (count == 0) {
                    continue;
                }
                // 인접한 8개 칸에 나이가 1인 나무를 추가한다.
                for (int k = 0; k < 8; k++) {
                    int ki = i + di_arr[k];
                    int kj = j + dj_arr[k];
                    if ((ki < 0 || ki >= map_size) || (kj < 0 || kj >= map_size)) {
                        continue;
                    }
                    for (int l = 0; l < count; l++) {
                        tree_ages[ki][kj].push(1);
                    }
                }
                number_of_breeding[i][j] = 0;
            }
        }

        // 겨울
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                // 로봇이 돌아다니면서 땅에 양분을 추가.
                nutrients_map[i][j] += s2d2_nutrients_map[i][j];
            }
        }

        #ifdef DEBUG
        cout << "Nutrients:" << endl;
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                cout << nutrients_map[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Tree Ages:" << endl;
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                min_heap ages_tmp = tree_ages[i][j];
                while (!ages_tmp.empty()) {
                    int age = ages_tmp.top();
                    ages_tmp.pop();
                    cout << i << "," << j << ":" << age << " ";
                }
                cout << endl;
            }
        }
        #endif

        years--;
    }

    int answer = 0;
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            answer += tree_ages[i][j].size();
        }
    }
    return answer;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> A(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int a_ij;
            cin >> a_ij;
            A[i][j] = a_ij;
        }
    }

    vector<tuple<int, int, int>> tree_info;
    for (int i = 0; i < M; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        tree_info.push_back(make_tuple(x, y, z));
    }

    int answer = solution(N, A, tree_info, K);
    cout << answer;
    return 0;
}

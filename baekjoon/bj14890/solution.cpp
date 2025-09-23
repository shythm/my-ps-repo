#include <vector>
#include <iostream>

// #define DEBUG

using namespace std;

int solution(const vector<vector<int>>& map, int slope_length) {
    int answer = 0;
    int n = map.size();

    vector<vector<int>> map_diff(n, vector<int>(n, 0)); // 다음 스텝과 현재 스텝의 차이
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == n - 1) break; // boundary 무시
            map_diff[i][j] = map[i][j + 1] - map[i][j];
        }
    }

    for (const auto& road_diff : map_diff) {
        int prev_step_diff = 0;
        int prev_step_diff_idx = -1;
        bool valid_road = true;

        for (int i = 0; i < n; i++) {
            if (!valid_road) break;

            const auto& step_diff = road_diff[i];
            const auto& step_distance = i - prev_step_diff_idx;
            switch (step_diff) {
            case 0:
                // do nothing
                break;
            case 1:
                if (prev_step_diff == 0 || prev_step_diff == 1) {
                    // 거리가 L(slope_length) 미만이면 탈출
                    if (step_distance < slope_length) {
                        valid_road = false;
                    }
                } else if (prev_step_diff == -1) {
                    // 거리가 2L 미만이면 탈출
                    if (step_distance < 2 * slope_length) {
                        valid_road = false;
                    }
                }
                prev_step_diff = 1;
                prev_step_diff_idx = i;
                break;
            case -1:
                if (prev_step_diff == -1) {
                    // 거리가 L 미만이면 탈출
                    if (step_distance < slope_length) {
                        valid_road = false;
                    }
                }
                prev_step_diff = -1;
                prev_step_diff_idx = i;
                break;
            default:
                // 경사가 너무 높아 경사로를 설치할 수 없기에 탈출
                valid_road = false;
                break;
            }
        }

        // 끝에 대한 예외 처리 수행
        if (prev_step_diff == -1 && (n - 1 - prev_step_diff_idx < slope_length)) {
            valid_road = false;
        }

        if (valid_road) answer++;

        #ifdef DEBUG
        cout << "the road is " << (valid_road ? "valid" : "invalid") << endl;
        #endif
    }

    return answer;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L;
    cin >> N >> L;

    vector<vector<int>> map(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    int answer = solution(map, L);

    #ifdef DEBUG
    cout << "original: " << answer << endl;
    #endif

    // reverse
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int temp = map[j][i];
            map[j][i] = map[i][j];
            map[i][j] = temp;
        }
    }
    #ifdef DEBUG
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    #endif

    answer += solution(map, L);

    #ifdef DEBUG
    cout << "reversed: " << answer << endl;
    #endif

    cout << answer;
    return 0;
}
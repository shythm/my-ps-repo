#include <vector>
#include <iostream>

using namespace std;

struct student_favorite {
    int student;
    vector<int> favorites;
};

struct seat_info {
    bool available;
    int near_favorite;
    int near_empty;
};

template <typename T>
bool is_in(const T& target, const vector<T>& source) {
    for (auto item : source) {
        if (target == item) {
            return true;
        }
    }
    return false;
}

int solution(
    int seat_size, // N x N에서 N
    vector<student_favorite>& input_data // 좋아하는 학생의 목록
) {
    int answer = 0;

    vector<vector<int>> seats(seat_size + 2, vector<int>(seat_size + 2, 0)); // 학생들이 앉은 위치를 저장하는 행렬 (패딩 1)
    for (int i = 0; i < seats.size(); i++) { // 경계는 -1로 채우기
        if (i == 0 || i == (seat_size + 1)) {
            for (int j = 0; j < seat_size + 2; j++) {
                seats[i][j] = -1;
            }
            continue;
        }
        seats[i][0] = -1;
        seats[i][seat_size + 1] = -1;
    }

    for (auto item : input_data) {
        vector<vector<seat_info>> seat_infos(seat_size + 2, vector<seat_info>(seat_size + 2, {
            .available = false,
            .near_favorite = 0,
            .near_empty = 0,
        }));


        for (int i = 1; i <= seat_size; i++) {
            for (int j = 1; j <= seat_size; j++) {
                // 해당 자리를 사용할 수 있는지 확인
                if (seats[i][j] != 0) {
                    seat_infos[i][j].available = false;
                    continue;
                } else {
                    seat_infos[i][j].available = true;
                }

                // 인접한 칸에 좋아하는 학생이 몇 명이나 있는지 확인
                int near_favorite = 0;
                if (is_in(seats[i - 1][j], item.favorites)) near_favorite++;
                if (is_in(seats[i + 1][j], item.favorites)) near_favorite++;
                if (is_in(seats[i][j - 1], item.favorites)) near_favorite++;
                if (is_in(seats[i][j + 1], item.favorites)) near_favorite++;
                seat_infos[i][j].near_favorite = near_favorite;

                // 동시에 인접한 칸에 비어 있는 칸이 얼마나 있는지 확인
                int near_empty = 0;
                if (seats[i - 1][j] == 0) near_empty++;
                if (seats[i + 1][j] == 0) near_empty++;
                if (seats[i][j - 1] == 0) near_empty++;
                if (seats[i][j + 1] == 0) near_empty++;
                seat_infos[i][j].near_empty = near_empty;
            }
        }

        int best_x = 0;
        int best_y = 0;
        int best_near_favorite = -1;
        int best_near_empty = -1;

        /**
         * 1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정한다.
         * 2. 1을 만족하는 칸이 여러 개이면, 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
         * 3. 2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로, 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.
         */
        for (int i = 1; i <= seat_size; i++) {
            for (int j = 1; j <= seat_size; j++) {
                const auto& si = seat_infos[i][j];
                if (si.available == false) continue;

                if (
                    (si.near_favorite > best_near_favorite) ||
                    ((si.near_favorite == best_near_favorite) && (si.near_empty > best_near_empty))
                ) {
                    best_x = j;
                    best_y = i;
                    best_near_favorite = si.near_favorite;
                    best_near_empty = si.near_empty;
                }
            }
        }

        seats[best_y][best_x] = item.student;

        // debug
        // cout << "student: " << item.student << endl;
        // for (auto row : seats) {
        //     for (auto elem : row) {
        //         cout << elem << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }

    for (auto item : input_data) {
        int x = 0, y = 0;
        for (int i = 1; i <= seat_size; i++) {
            for (int j = 1; j <= seat_size; j++) {
                if (seats[i][j] == item.student) {
                    x = j;
                    y = i;
                    break;
                }
            }
        }

        int near_favorite = 0;
        if (is_in(seats[y - 1][x], item.favorites)) near_favorite++;
        if (is_in(seats[y + 1][x], item.favorites)) near_favorite++;
        if (is_in(seats[y][x - 1], item.favorites)) near_favorite++;
        if (is_in(seats[y][x + 1], item.favorites)) near_favorite++;

        switch (near_favorite) {
        case 0:
            answer += 0; break;
        case 1:
            answer += 1; break;
        case 2:
            answer += 10; break;
        case 3:
            answer += 100; break;
        case 4:
            answer += 1000; break;
        }
    }

    return answer;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    vector<student_favorite> input_data;
    input_data.reserve(N * N);
    for (int i = 0; i < N * N; i++) {
        int student;
        cin >> student;
        vector<int> favorites(4);
        cin >> favorites[0] >> favorites[1] >> favorites[2] >> favorites[3];
        input_data.push_back({
            .student = student,
            .favorites = favorites,
        });
    }

    int answer = solution(N, input_data);
    cout << answer;
    return 0;
}
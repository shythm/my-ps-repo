#include <iostream>
#include <vector>
#include <limits>

#define ABS(X) ((X > 0) ? (X) : (-X))

using namespace std;

void backtrack_combination(
    vector<int> candidates, // 조합 후보
    int k, // 선택할 수
    vector<int> combination, // 생성된 조합
    vector<vector<int>>& results // 결과를 저장할 컨테이너
) {
    /**
     * 1~N(number)에 대해 k개의 원소를 뽑아 조합을 우선 구해야 한다.
     * 다음 원소를 고르기 위해 사용할 수 있는 배열을 넘겨서, 여기서 선택할 수 있도록 하자.
     * 그리고 선택된 원소를 다시 선택하지 않기 위해 제거하도록 하자.
     */
    if (combination.size() == k) {
        results.push_back(combination);
        return;
    }

    while (!candidates.empty()) {
        int candidate = candidates.back();
        candidates.pop_back();

        combination.push_back(candidate);
        backtrack_combination(candidates, k, combination, results);

        combination.pop_back(); // 선택 취소(백트래킹)
    }
}

int solution(
    vector<vector<int>> ability_matrix,
    vector<vector<int>> combinations
) {
    int answer = numeric_limits<int>::max();

    for (const vector<int>& team_start : combinations) {
        vector<bool> team_start_encoded(ability_matrix.size());
        for (int i : team_start) {
            team_start_encoded[i] = true;
        }
        vector<bool> team_link_encoded;
        for (bool pop : team_start_encoded) {
            team_link_encoded.push_back(!pop);
        }

        int ability = 0;
        for (int i = 0; i < ability_matrix.size(); i++) {
            for (int j = 0; j < ability_matrix.size(); j++) {
                if (team_start_encoded[i] && team_start_encoded[j]) {
                    ability += ability_matrix[i][j];
                }
                if (team_link_encoded[i] && team_link_encoded[j]) {
                    ability -= ability_matrix[i][j];
                }
            }
        }
        ability = ABS(ability);
        
        if (ability < answer) {
            answer = ability;
        }
    }

    return answer;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<vector<int>> ability_matrix;
    ability_matrix.reserve(N);
    for (int i = 0; i < N; i++) {
        vector<int> temp_matrix;
        temp_matrix.reserve(N);
        int temp_input;
        for (int j = 0; j < N; j++) {
            cin >> temp_input;
            temp_matrix.push_back(temp_input);
        }
        ability_matrix.push_back(temp_matrix);
    }

    vector<int> candidates;
    for (int i = 0; i < N; i++) {
        candidates.push_back(i);
    }
    vector<int> empty_combination;
    vector<vector<int>> combinations;
    backtrack_combination(candidates, N / 2, empty_combination, combinations);

    int answer = solution(ability_matrix, combinations);
    cout << answer;

    return 0;
}

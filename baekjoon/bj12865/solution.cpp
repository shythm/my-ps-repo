#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<pair<int, int>> things;
    for (int i = 0; i < N; i++) {
        int W, V;
        cin >> W >> V;
        things.emplace_back(W, V);
    }

    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
    for (int i = 1; i <= N; i++) {
        const int& weight = things[i - 1].first;
        const int& value = things[i - 1].second;

        for (int j = 1; j <= K; j++) {
            // i번째 물건까지 사용한다고 했을 때, j 이하의 무게로 가치를 가장 최대화할 수 있는 경우를 저장한다.
            // i번째 물건의 weight에 도달하기 전까지는 이 물건을 사용할 수 없으므로, 이전의 경우를 사용한다(일단 이것이 최대 가치이다).
            dp[i][j] = dp[i - 1][j];

            // i번째 물건을 담을 수 있는 경우에,
            if (j >= weight) {
                dp[i][j] = max(
                    dp[i][j],
                    dp[i - 1][j - weight] + value // 자기 자신의 가치와 남은 무게로 얻을 수 있는 가치를 더한 경우가 크면 교체
                );
            }
        }
    }

    cout << dp[N][K] << endl;

    return 0;
}
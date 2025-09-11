#include <iostream>
#include <vector>

using namespace std;

#define MOD(A, M) ((((A) % (M)) + (M)) % (M))

struct carriage {
    int durability = 0;
    bool on_stuff = false;
};

int solution(
    int belt_size, // 컨베이어 벨트의 길이(N)
    int unavailable_upper_count, // 내구도가 0인 칸의 개수 상한선(K)
    const vector<int>& durabilities // 각 칸의 내구도
) {
    /**
     * '올리는 위치': 1번 위치
     * '내리는 위치': N번 위치
     * '벨트 칸의 수': 2N개
     * 
     * 1. 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
     * 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다. 만약 이동할 수 없다면 가만히 있는다.
     *   2.1. 로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며, 그 칸의 내구도가 1이상 남아 있어야 한다.
     * 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
     * 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다. 그렇지 않다면 1번으로 돌아간다.
     */
    int answer = 0;
    int delta_move = 0;

    vector<carriage> belt_carriages(belt_size * 2);
    int bc_size = belt_carriages.size();
    for (int i = 0; i < bc_size; i++) {
        belt_carriages[i].durability = durabilities[i];
    }

    while (true) {
        // 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전한다.
        answer++;
        delta_move--;

        int begin = MOD(delta_move, bc_size); // 컨베이어 벨트의 시작에 위치한 carriage index
        int end = MOD(begin + belt_size - 1, bc_size); // 컨베이어 벨트 끝에 위치한 carriage index
        // cout << " step: " << step << " begin: " << begin << " end: " << end << endl;
        
        // 내리는 위치에 도달한 칸의 물건 내리기
        belt_carriages[end].on_stuff = false;

        int curr = MOD(end - 1, bc_size);
        while (curr != begin) {
            int next = MOD(curr + 1, bc_size);

            if (
                (belt_carriages[curr].on_stuff == true) && // 1. 현재 칸에 로봇이 있는가?
                (belt_carriages[next].on_stuff == false) && // 2. 다음 칸에 로봇이 없는가?
                (belt_carriages[next].durability > 0) // 3. 다음 칸의 내구도가 1 이상인가?
            ) {
                // 벨트가 회전하는 방향으로 한 칸 이동할 수 있으므로 이동한다.
                belt_carriages[curr].on_stuff = false;
                belt_carriages[next].on_stuff = true;
                belt_carriages[next].durability--;
            }

            curr = MOD(curr - 1, bc_size);
        }

        // 내리는 위치에 도달한 칸의 물건 내리기(2번 단계에서 내리는 위치에 로봇이 올라갔을 수 있으므로)
        belt_carriages[end].on_stuff = false;

        // 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
        if (belt_carriages[begin].durability > 0) {
            belt_carriages[begin].on_stuff = true;
            belt_carriages[begin].durability--;
        }

        // 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료한다.
        int unavailable_count = 0;
        for (auto item : belt_carriages) {
            if (item.durability <= 0) { // 음수가 될 수 있음
                unavailable_count++;
            }
        }
        if (unavailable_count >= unavailable_upper_count) {
            break;
        }
    }

    return answer;
}

int main(void) {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;
    vector<int> A;
    A.reserve(N * 2);
    for (int i = 0; i < 2 * N; i++) {
        int Ai;
        cin >> Ai;
        A.push_back(Ai);
    }

    int answer = solution(N, K, A);
    cout << answer;

    return 0;
}
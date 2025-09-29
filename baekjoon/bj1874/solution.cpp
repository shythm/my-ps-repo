#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<char> solution(const vector<int>& sequence) {
    /**
     * 스택에 1, 2, ... 순서대로 push한다.
     * 그리고 원하는 수열을 만들기 위해 pop을 해야 한다.
     * 
     * 4, 3, 6, 8, 7, 5, 2, 1
     * + + + + -(4) -(3) + + -(6) + + -(8) -(7) - -(5) - - -(2) -(1)
     * 
     * 규칙을 보자... push하는 것은 오름차순이고! pop하는 것은 내림차순이다...
     * 사실 스택으로 푸는 게 아닌 거 아닐까?
     * 수학적 귀납법으로,,,
     * 
     * 4가 들어왔어(pop). 이후로는 4보다 작은 수를 pop할 수 있겠지?
     * 그런데 이미 3이 pop되었던 상태라면? 스택을 유지해서 확인할 필요가 있긴 해보인다.
     * 
     * 0. 초기에는 0을 집어 넣자.
     * 1. top 확인 후 현재 요소(curr)와 크기 비교
     *   1-1. curr가 크다면? 새 요소를 push한다. -> 왜냐하면 그 숫자까지 push를 계속 해줘야 숫자를 pop하여 뽑아낼 수 있기 때문임.
     *   1-2. curr와 같다면? pop한다. 그리고 현재 요소를 다음 요소로 바꾼다.
     *   1-3. curr가 작다면? 현재 요소가 나올 때까지 pop을 계속하는데, 현재 요소보다 작아지는 순간이 온다면 만들 수 없는 수열임.
     */
    vector<char> answer;
    answer.reserve(100000);

    stack<int> s;
    s.push(0);
    int max_num = 0;
    size_t seq_size = sequence.size();
    int seq_idx = 0;

    while (seq_idx < seq_size) {
        if (s.empty()) {
            answer.push_back('x');
            break;
        }
        const int& top = s.top();
        const int& curr = sequence[seq_idx];

        if (curr > top) {
            s.push(++max_num);
            answer.push_back('+');
        } else if (curr < top) {
            s.pop();
            answer.push_back('-');
            if (s.empty() || curr > s.top()) {
                answer.push_back('x');
                break;
            }
        } else {
            s.pop();
            seq_idx++;
            answer.push_back('-');
        }
    }

    return answer;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> sequence;
    for (int i = 0; i < n; i++) {
        sequence.emplace_back(0);
        cin >> sequence.back();
    }

    auto answer = solution(sequence);
    if (answer.back() == 'x') {
        cout << "NO" << '\n';
    } else {
        for (const auto& elem : answer) {
            cout << elem << '\n';
        }
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool is_valid_parenthesis(const string& input) {
    stack<char> s;

    for (const auto& c : input) {
        /**
         * 유효한 괄호인지 확인해야 한다.
         * `(` 문자가 들어오면 스택에 우선 집어 넣는다.
         * `)` 문자가 들어오면 스택에 에 있는 `(`를 제거한다. 이때 비어있다면 유효한 괄호가 아니다.
         */
        if (c == '(') {
            s.push('(');
        } else if (c == ')') {
            if (s.empty()) {
                return false;
            }
            s.pop();
        }
    }

    return s.size() == 0;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    cin.ignore();

    vector<string> parentheses;
    for (int i = 0; i < T; i++) {
        parentheses.emplace_back();
        auto& str = parentheses.back();
        getline(cin, str);
    }

    for (int i = 0; i < T; i++) {
        cout << (is_valid_parenthesis(parentheses[i]) ? "YES" : "NO") << endl;
    }

    return 0;
}
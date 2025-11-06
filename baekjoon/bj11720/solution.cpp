#include <iostream>
using namespace std;

int main() {
    int N;
    string numbers;
    cin >> N >> numbers;
    int answer = 0;
    for (const auto& ch : numbers) {
        answer += (ch - '0');
    }
    cout << answer;
    return 0;
}
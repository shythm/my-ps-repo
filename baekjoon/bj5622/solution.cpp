#include <iostream>
#include <string>

using namespace std;

int main() {
    string input;
    cin >> input;

    static int times[26] = {
        3, 3, 3,
        4, 4, 4,
        5, 5, 5,
        6, 6, 6,
        7, 7, 7,
        8, 8, 8, 8,
        9, 9, 9,
        10, 10, 10, 10,
    };

    int answer = 0;
    for (const auto& ch : input) {
        answer += times[(int)(ch - 'A')];
    }
    cout << answer << endl;

    return 0;
}
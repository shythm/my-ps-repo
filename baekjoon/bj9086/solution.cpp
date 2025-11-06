#include <iostream>
#include <string>

using namespace std;

int main() {
    int T;
    cin >> T;

    string input;
    getline(cin, input); // flush newline

    for (int i = 0; i < T; i++) {
        getline(cin, input);
        cout << input[0] << input[input.size() - 1] << '\n';
    }

    return 0;
}
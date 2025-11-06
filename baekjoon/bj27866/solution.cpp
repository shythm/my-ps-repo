#include <iostream>

using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    getline(cin, input);
    int count;
    cin >> count;

    cout << input[count - 1];
    return 0;
}
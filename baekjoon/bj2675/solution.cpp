#include <iostream>
#include <string>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int R;
        string S;
        cin >> R >> S;

        for (const char& c : S) {
            for (int j = 0; j < R; j++) {
                cout << c;
            }
        }
        cout << '\n';
    }
    return 0;
}
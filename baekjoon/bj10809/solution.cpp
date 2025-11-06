#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> answer(26, -1);
    string input;
    getline(cin, input);

    int i = 0;
    for (const char& ch : input) {
        auto& target = answer[(int)(ch - 'a')];
        if (target == -1) {
            target = i;
        }
        i++;
    }

    for (const int& item : answer) {
        cout << item << ' ';
    }
    return 0;
}
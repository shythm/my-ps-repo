#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void reverse_string(string& str) {
    for (int i = 0; i < str.size() / 2; i++) {
        char& lc = str[i];
        char& rc = str[str.size() - i - 1];

        // swap
        char temp = lc;
        lc = rc;
        rc = temp;
    }
}

int main() {
    string first, second;
    cin >> first >> second;
    reverse_string(first);
    reverse_string(second);
    
    int first_num = stoi(first);
    int second_num = stoi(second);
    cout << max(first_num, second_num) << endl;

    return 0;
}

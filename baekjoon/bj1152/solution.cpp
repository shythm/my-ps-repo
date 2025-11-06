#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int answer = 0;
    string input;
    getline(cin, input);

    stringstream ss(input);
    string word;
    while (getline(ss, word, ' ')) {
        if (word.size() > 0) answer++;
    }
    cout << answer << endl;

    return 0;
}
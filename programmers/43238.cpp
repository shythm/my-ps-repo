#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    long long left = 0;
    long long right = *max_element(times.begin(), times.end()) * (long long)n;  // 꼭 형변환 해주기! 안하면 int 연산으로 오버플로우 날 수 있음

    while (left < right) {
        long long middle = (left + right) / 2;
        long long limit_n = 0;

        for (int i = 0; i < times.size(); i++) {
            limit_n += middle / times[i];
        }

        if (limit_n < n) {  // 사람들을 모두 처리할 수 없을 때
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

int main()
{
    int n1 = 6;
    vector<int> test1 = {7, 10};
    long long answer1 = solution(n1, test1);
    cout << answer1 << endl;

    return 0;
}
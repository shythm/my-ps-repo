#include <cstdio>
#include <vector>

long long solution(
    std::vector<int>& number_of_applicant, // 각 시험장의 응시자 수
    int supervisor_capacity, // 총감독관이 감시할 수 있는 응시자 수
    int sub_supervisor_capacity // 부감독관이 감시할 수 있는 응시자 수
) {
    /**
     * 우선 각 시험장에는 총감독관이 꼭 한 명씩 있어야 한다.
     * 따라서 모든 시험장에 총감독관은 무조건 한 명 배치하는 것이 최적이고, 각 시험장의 응시자 수에서 이를 차감하면 될 것이다.
     * 그리고 나서 아직 양수인 시험장에 대해서는 나머지 연산 후 올림 처리를 하여 부감독관 수를 계산하면 될 것이다.
     */
    long long answer = 0;

    for (int num : number_of_applicant) {
        num -= supervisor_capacity;
        if (num > 0) {
            answer += (num + sub_supervisor_capacity - 1) / sub_supervisor_capacity; // 부감독관 수 추가
        }
    }
    answer += number_of_applicant.size(); // 총감독관 수 일괄 추가

    return answer;
}

int main(void) {
    int N, B, C;
    std::vector<int> A;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int Ai;
        scanf("%d", &Ai);
        A.push_back(Ai);
    }
    scanf("%d %d", &B, &C);

    long long answer = solution(A, B, C);
    printf("%lld", answer);

    return 0;
}

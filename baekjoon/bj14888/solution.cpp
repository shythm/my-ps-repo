#include <iostream>
#include <deque>
#include <array>
#include <stdexcept>
#include <set>

enum operator_type {
    OP_ADD = 0, OP_SUB, OP_MUL, OP_DIV, OP_COUNT
};

int operator_process(
    std::deque<operator_type> ops,
    std::deque<int> numbers
) {
    while (numbers.size() > 1) {
        if (ops.empty()) {
            throw std::runtime_error("There is no available operator");
        }
        int op = ops.front();
        ops.pop_front();

        int operand1 = numbers.front();
        numbers.pop_front();
        int operand2 = numbers.front();
        numbers.pop_front();

        int result = 0;
        switch (op) {
        case OP_ADD:
            result = operand1 + operand2;
            break;
        case OP_SUB:
            result = operand1 - operand2;
            break;
        case OP_MUL:
            result = operand1 * operand2;
            break;
        case OP_DIV:
            result = operand1 / operand2;
            break;
        }
        numbers.push_front(result);
    }

    return numbers.front();
}

void operator_backtrack(
    std::array<int, OP_COUNT> counter, // 사용할 수 있는 연산자 수를 저장
    std::deque<operator_type> ops, // 현재 만들어진 연산자 배열을 저장
    const std::deque<int>& numbers, // 연산자 배열이 완성되고 결과를 계산할 때 참조할 수
    std::multiset<int>& results // 결과를 저장할 멀티셋
) {
    if (ops.size() == numbers.size() - 1) { // 완성된 연산자 배열의 크기는 주어진 수 배열의 크기보다 1이 작다.
        // 계산 수행 후 result에 넣기
        results.insert(operator_process(ops, numbers));
        return;
    }

    for (int op = 0; op < OP_COUNT; op++) {
        if (counter[op] > 0) { // 해당 연산자를 사용할 수 있는가?
            ops.push_back(static_cast<operator_type>(op));
            counter[op]--;

            operator_backtrack(counter, ops, numbers, results); // 재귀 호출

            ops.pop_back(); // 현재 골랐던 요소를 선택 해제(backtracking)
            counter[op]++;
        }
        // 다음 연산자 선택하여 새롭게 탐색할 것
    }
}

int main(void) {
    /**
     * 주어진 수열 사이에 사칙연산을 집어넣어 연산을 수행한다. 이때,
     * 1. 연산자 우선순위는 무조건 좌에서 우 순서이다(곱셈 먼저 이런거 없음)
     * 2. 연산자를 끼워넣을 수 있는 모든 경우의 수에 대해 탐색해야 한다.
     * 
     * 이에, 연산자를 구성하는 모든 조합을 구한 뒤, 각 조합에 대해 연산을 수행하여 multiset에 넣어 최대/최소를 구해보자.
     * numbers의 길이는 최대 11이므로 끼워넣을 수 있는 연산자의 조합 수는 중복순열 10! / (num_add! * num_sub! * num_mul!, num_div!)이 될 것이다.
     * 
     * 중복 순열을 만들기 위해 backtracking 기법을 이용해본다.
     * 첫 원소를 고른 뒤, 그 다음 원소를 계속 고른다.
     * 
     * A, A, B, B, C
     * 이렇게 있다고 생각해보자.
     * 
     * (A) / (1, 2, 1) -> (A, A) / (0, 2, 1) -> (A, A, B) / (0, 1, 1) -> (A, A, B, B) / (0, 0, 1) -> (A, A, B, B, C) / (0, 0, 0)
     * 백트래킹? 모든 조건에 도달했다면 다시 뒤로 돌아간다.
     * 마지막 상태였던 (A, A, B, B, C) / (0, 0, 0)의 경우에서, 뒤로 돌아가면(**개수가 0이 된 것에 대해서는 백트래킹을 하지 않는다**)
     * (A, A, B, B) / (0, 0, 1) 상태에서 선택 취소로 돌아간다...? (A, A, B) / (0, 1, 1), 그리고 다음 C에 대해 연산 수행.
     * (A, A, B, C) / (0, 1, 0) -> (A, A, B, C, B) / (0, 0, 0). 선택취소로 돌아간다는 의미는,,, 이 경로에서 더 이상 볼 게 없으니까 뒤로 돌아간다는 의미일 것...
     * 
     * 즉, 하나의 원소를 뽑아, 다음에 올 원소를 고르는 과정에서 모든 과정이 끝났다면, 다른 원소를 고르는 행위를 해야 하는데 이게 선택 취소라는 의미라고 보면 될 듯.
     * 
     * 하나의 순열이 완성된다면, 그 순열로 계산하여 답에 추가하는 과정을 한번에 하자.
     */
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, num_add, num_sub, num_mul, num_div;
    std::deque<int> numbers;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int temp;
        std::cin >> temp;
        numbers.push_back(temp);
    }
    std::cin >> num_add >> num_sub >> num_mul >> num_div;

    std::array<int, OP_COUNT> counter = {
        num_add, num_sub, num_mul, num_div
    };
    std::deque<operator_type> ops;
    std::multiset<int> results;

    operator_backtrack(counter, ops, numbers, results);
    
    std::cout << *results.rbegin() << std::endl;
    std::cout << *results.begin() << std::endl;
    return 0;
}

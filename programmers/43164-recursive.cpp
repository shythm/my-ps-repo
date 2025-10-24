#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <iostream>
// #define DEBUG

using namespace std;

struct ticket_t {
    string departure;
    string arrival;
    bool used;
    
    bool operator<(const ticket_t& other) const {
        return arrival < other.arrival;
    }
};

bool dfs(
    map<string, vector<ticket_t>>& ticket_map,
    vector<string>& answer,
    string departure
) {
    answer.push_back(departure);
    
    // 주어진 항공권을 모두 사용해야 하고, 모든 도시를 방문할 수 없는 경우는 주어지지 않으므로, 주어진 항공권을 모두 사용한 경우는 모든 도시를 방문한 경우가 된다.
    bool all_visited = true;
    for (auto& elem : ticket_map) {
        for (auto& ticket : elem.second) {
            all_visited &= ticket.used;
            if (!all_visited) break;
        }
        if (!all_visited) break;
    }
    if (all_visited) {
        return true; // 탐색이 끝난 경우 탈출
    }

    // 도착지에서 사용할 수 있는 티켓 구하기
    auto& tickets = ticket_map[departure];
    
    // 알파벳 순으로 탐색하기(이미 정렬된 경우라고 가정).
    // 이미 사용한 티켓(간선)은 무시할 수 있도록 티켓 사용 유무를 판단할 수 있는 지표 필요함.
    // 재귀로 구현할 경우, 메모리 절약을 위해 참조를 잘 전달해야 할 것.
    for (auto& ticket : tickets) {
        // 이미 사용한 티켓이라면
        if (ticket.used) {
            continue;
        }

        ticket.used = true;
        #ifdef DEBUG
        cout << "search: " << ticket.departure << " -> " << ticket.arrival << ", ";
        for (const auto& item : answer) {
            cout << item << ' ';
        }
        cout << endl;
        #endif
        if (dfs(ticket_map, answer, ticket.arrival)) {
            return true; // 탐색이 끝난 경우 탈출
        }
        ticket.used = false;
    }
    
    answer.pop_back();
    return false; // 모든 티켓을 사용한 경우 fallback
}

vector<string> solution(vector<vector<string>> tickets) {
    map<string, vector<ticket_t>> ticket_map;
    
    for (const auto& ticket : tickets) {
        const string& departure = ticket[0];
        const string& arrival = ticket[1];
        
        ticket_map[departure].push_back({
            .departure = departure,
            .arrival = arrival,
            .used = false,
        });
    }
    
    // 오름차순 정렬
    for (auto& elem : ticket_map) {
        auto& tickets = elem.second;
        sort(tickets.begin(), tickets.end());
    }
    
    #ifdef DEBUG
    cout << "[tickets]" << endl;
    for (const auto& elem : ticket_map) {
        cout << elem.first << " : ";
        for (const auto& ticket : elem.second) {
            cout << ticket.arrival << ' ';
        }
        cout << endl;
    }
    cout << endl;
    #endif
    
    vector<string> answer;
    dfs(ticket_map, answer, "ICN");
    return answer;
}

void print_answer(const vector<string>& answer) {
    for (const auto& item : answer) {
        cout << item << ' ';
    }
    cout << endl;
}

int main(void) {
    vector<vector<string>> tickets_1({
        // [["ICN", "JFK"], ["HND", "IAD"], ["JFK", "HND"]]
        {"ICN", "JFK"},
        {"HND", "IAD"},
        {"JFK", "HND"},
    });

    vector<vector<string>> tickets_2({
        // [["ICN", "SFO"], ["ICN", "ATL"], ["SFO", "ATL"], ["ATL", "ICN"], ["ATL","SFO"]]
        {"ICN", "SFO"},
        {"ICN", "ATL"},
        {"SFO", "ATL"},
        {"ATL", "ICN"},
        {"ATL","SFO"},
    });

    print_answer(solution(tickets_1));
    print_answer(solution(tickets_2));

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class robot {
public:
    enum direction_type {
        NORTH = 0, EAST, SOUTH, WEST
    };

    struct position_type {
        int x, y;
    };

    robot(int position_x, int position_y, int direction) {
        position_ = {
            .x = position_x,
            .y = position_y,
        };
        direction_ = static_cast<direction_type>(direction & 0x03);
    }

    void rotate_counterclockwise() {
        // switch (dir) {
        // case EAST: return NORTH;
        // case WEST: return SOUTH;
        // case SOUTH: return EAST;
        // case NORTH: return WEST;
        // }
        direction_ = static_cast<direction_type>((direction_ - 1) & 0x03);
    }

    position_type get_forward() const {
        position_type new_position(position_);

        switch (direction_) {
        case NORTH:
            new_position.y--;
            break;
        case EAST:
            new_position.x++;
            break;
        case SOUTH:
            new_position.y++;
            break;
        case WEST:
            new_position.x--;
            break;
        }
        return new_position;
    }

    position_type get_backward() const {
        position_type new_position(position_);

        switch (direction_) {
        case NORTH:
            new_position.y++;
            break;
        case EAST:
            new_position.x--;
            break;
        case SOUTH:
            new_position.y--;
            break;
        case WEST:
            new_position.x++;
            break;
        }
        return new_position;
    }

    void move_forward() {
        position_ = get_forward();
    }

    void move_backward() {
        position_ = get_backward();
    }

    position_type get_position() const {
        return position_;
    }

    direction_type get_direction() const {
        return direction_;
    }

private:
    position_type position_;
    direction_type direction_;
};

int solution(
    vector<vector<bool>>& map, // 방 지도(true: 벽, false: 청소되지 않은 빈 칸)
    int robot_position_x, // 로봇의 초기 위치(x)
    int robot_position_y, // 로봇의 초기 위치(y)
    int robot_direction // 로봇이 바라보는 방향(0: 북쪽, 1: 동쪽, 2: 남쪽, 3: 서쪽)
) {
    /**
     * 1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
     * 2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
     *    2.1. 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
     *    2.2. 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
     * 3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우,
     *    3.1. 반시계 방향으로 90도 회전한다.
     *    3.2. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
     *    3.3. 1번으로 돌아간다.
     * 
     * [팁]
     * 방의 가장 북쪽, 가장 남쪽, 가장 서쪽, 가장 동쪽 줄 중 하나 이상에 위치한 모든 칸에는 벽이 있다.
     * 따라서 배열 바운더리 체크는 굳이 할 필요가 없어 보인다.
     * 그리고, 로봇 청소기가 있는 칸은 항상 빈 칸이다.
     */
    int answer = 0;

    vector<vector<bool>> map_cleaned(map); // 청소 여부
    robot r(robot_position_x, robot_position_y, robot_direction);

    while (true) {
        auto pos = r.get_position();

        if (map_cleaned[pos.y][pos.x] == false) {
            // 현재 칸이 아직 청소되지 않은 경우,
            // 현재 칸을 청소한다.
            map_cleaned[pos.y][pos.x] = true;
            answer++;
        }

        if (
            (map_cleaned[pos.y][pos.x + 1]) &&
            (map_cleaned[pos.y][pos.x - 1]) &&
            (map_cleaned[pos.y + 1][pos.x]) &&
            (map_cleaned[pos.y - 1][pos.x])
        ) {
            // 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
            auto next_pos = r.get_backward();
            if (map[next_pos.y][next_pos.x] == false) {
                // 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
                r.move_backward();
                continue;
            } else {
                // 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
                break;
            }
        } else {
            // 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우,
            // 반시계 방향으로 90도 회전한다.
            r.rotate_counterclockwise();
            // 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
            auto next_pos = r.get_forward();
            if (map_cleaned[next_pos.y][next_pos.x] == false) {
                r.move_forward();
            }
        }
    }

    return answer;
}

int main(void) {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    int init_pos_x, init_pos_y, init_dir;
    cin >> init_pos_y >> init_pos_x >> init_dir;
    vector<vector<bool>> map(N);
    for (int i = 0; i < N; i++) {
        vector<bool> map_row(M);
        for (int j = 0; j < M; j++) {
            int temp_input;
            cin >> temp_input;
            if (temp_input) {
                map_row[j] = true;
            } else {
                map_row[j] = false;
            }
        }
        map[i] = std::move(map_row);
    }

    int answer = solution(map, init_pos_x, init_pos_y, init_dir);
    cout << answer << endl;

    return 0;
}

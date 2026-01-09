package bj7569;

import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();
		int h = sc.nextInt();

		int[][][] tomatoes = new int[h][m][n];
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < n; k++) {
					tomatoes[i][j][k] = sc.nextInt();
				}
			}
		}

		var app = new Main();
		int answer = app.solution(tomatoes);
		System.out.println(answer);
	}

	private static final boolean DEBUG = false;

	private static class Node {
		int x, y, z, dist;
		Node(int x, int y, int z, int dist) {
			this.x = x;
			this.y = y;
			this.z = z;
			this.dist = dist;
		}

		@Override
		public String toString() {
			return String.format("x: %d, y: %d, z: %d, dist: %d", x, y, z, dist);
		}
	}

	int solution(int[][][] tomatoes) {
		int answer = 0;

		int h = tomatoes.length;
		int m = tomatoes[0].length;
		int n = tomatoes[0][0].length;

		boolean[][][] visited = new boolean[h][m][n];

		// 1. 익은 토마토를 먼저 찾아서 큐에 넣는다.
		Queue<Node> queue = new LinkedList<>();
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < n; k++) {
					if (tomatoes[i][j][k] == 1) {
						queue.add(new Node(k, j, i, 0));
						visited[i][j][k] = true;
					}
					if (tomatoes[i][j][k] == -1) { // 틀려서 추가한 코드
						// 마지막 정답 체크 때 visited가 모두 true가 아니라면 -1(토마토가 모두 익지 못하는 상황)을 출력해야 하는데,
						// 토마토가 없지만 도달할 수 없는 경우에 걸려 -1이 반환되는 문제를 아래와 같이 해결함.
						visited[i][j][k] = true;
					}
				}
			}
		}

		int[][] diff_arr = {
			{ 0, 0, 1 }, // 상
			{ 0, 0, -1 }, // 하
			{ -1, 0, 0 }, // 좌
			{ 1, 0, 0 }, // 우
			{ 0, 1, 0 }, // 앞
			{ 0, -1, 0 }, // 뒤
		};

		// 2. 큐에서 하나씩 토마토를 빼어 상, 하, 좌, 우, 앞, 뒤 토마토를 또한 큐에 넣는다.
		while (!queue.isEmpty()) {
			Node node = queue.remove();

			for (var diff : diff_arr) {
				int nx = node.x + diff[0];
				int ny = node.y + diff[1];
				int nz = node.z + diff[2];
				int newDist = node.dist + 1;

				if (
					!((0 <= nx && nx < n) && (0 <= ny && ny < m) && (0 <= nz && nz < h)) || // 유효하지 않은 좌표면
					visited[nz][ny][nx] // 이미 방문했으면
				) {
					continue;
				}

				if (tomatoes[nz][ny][nx] == -1) { // 토마토가 없으면
					visited[nz][ny][nx] = true; // 방문한 것으로 친다.
					continue;
				}

				var newNode = new Node(nx, ny, nz, newDist);
				queue.add(newNode);
				visited[nz][ny][nx] = true;
				if (DEBUG) {
					System.out.println(newNode);
				}
				answer = Math.max(answer, newNode.dist);
			}
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < n; k++) {
					if (!visited[i][j][k]) { // 토마토가 모두 익지 못하는 상황
						return -1;
					}
				}
			}
		}

		return answer;
	}
}

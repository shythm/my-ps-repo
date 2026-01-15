package bj17090;

import java.util.*;

public class Main {

	private static final boolean DEBUG = false;

	public static void main(String[] args) {
		var app = new Main();
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();
		sc.nextLine();

		char[][] miro = new char[n][m];
		for (int i = 0; i < n; i++) {
			String line = sc.nextLine();
			for (int j = 0; j < m; j++) {
				miro[i][j] = line.charAt(j);
			}
		}

		int answer = app.solution(miro);
		System.out.println(answer);
	}

	private static class Pair {
		int x;
		int y;

		Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}

		@Override
		public String toString() {
			return String.format("[x: %d, y: %d]", this.x, this.y);
		}
	}

	int solution(char[][] miro) {
		int answer = 0;

		// 패딩 1 추가
		char[][] newMiro = new char[miro.length + 2][miro[0].length + 2];
		for (int i = 0; i < miro.length; i++) {
			for (int j = 0; j < miro[0].length; j++) {
				newMiro[i + 1][j + 1] = miro[i][j];
			}
		}
		miro = newMiro;

		int n = miro.length;
		int m = miro[0].length;

		Queue<Pair> queue = new LinkedList<>();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i == 0 || j == 0 || i == n - 1 || j == m - 1) { // 외곽은 모두 탐색 범위에 추가한다.
					queue.add(new Pair(i, j));
				}
			}
		}

		int[][] diff = {
			{ -1,  0 }, // 상
			{  1,  0 }, // 하
			{  0, -1 }, // 좌
			{  0,  1 }, // 우
		};
		char[] targetDirs = { 'D', 'U', 'R', 'L' };

		while (!queue.isEmpty()) {
			var node = queue.remove();

			for (int i = 0; i < 4; i++) {
				int nx = node.x + diff[i][0];
				int ny = node.y + diff[i][1];
				char targetDir = targetDirs[i];

				// 먼저 새로운 위치가 유효한지 검사
				if (!(0 <= nx && nx < n && 0 <= ny && ny < m)) {
					continue;
				}

				if (miro[nx][ny] == '\0') { // 이미 방문한 경우
					continue;
				}

				// 새로운 위치에 해당하는 칸에서 현재 위치로 도달할 수 있는지 검사
				if (miro[nx][ny] == targetDir) {
					var pair = new Pair(nx, ny);
					queue.add(pair);
					miro[nx][ny] = '\0';  // null 문자를 채움으로써 방문했다는 사실 기록
					answer++; // 경우의 수 하나 증가

					if (DEBUG) {
						System.out.println("New Pair Added: " + pair);
					}
				}
			}
		}

		return answer;
	}
}

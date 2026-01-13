package bj10971;

import java.util.*;

public class Main {
	private static final boolean DEBUG = false;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		var app = new Main();

		int n = sc.nextInt();
		int[][] weights = new int[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				weights[i][j] = sc.nextInt();
			}
		}
		Deque<Integer> path = new ArrayDeque<>();

		int answer = app.solution(n, weights, path, 0);
		System.out.println(answer);
	}

	int solution(int n, int[][] weights, Deque<Integer> path, int distance) {
		int answer = Integer.MAX_VALUE;
		if (path.size() >= n) {
			// 탐색의 끝에 도달한 경우
			var firstIdx = path.getFirst();
			var lastIdx = path.getLast();
			if (weights[lastIdx][firstIdx] == 0) { // [틀려서 수정] 마지막 돌아가는 경로가 없으면 최대치 반환...
				return Integer.MAX_VALUE;
			}
			distance += weights[lastIdx][firstIdx]; // 다시 원래 도시로 돌아가는 비용 합산
			if (DEBUG) {
				System.out.println("Completed: " + path + " -> " + distance);
			}
			return distance;
		}
		var prevIdx = path.peekLast();

		for (int i = 0; i < n; i++) {
			if (path.contains(i)) { // 이미 방문한 도시라면
				continue;
			}

			// 다음 도시를 방문한다.
			int newDistance = 0;
			if (prevIdx != null) {
				if (weights[prevIdx][i] != 0) {
					newDistance = distance + weights[prevIdx][i];
				} else {
					if (DEBUG) {
						System.out.println("This path is invalid: " + path + " with " + i);
					}
					continue; // 방문할 수 없는 도시이므로 다음 도시 탐색
				}
			}

			path.addLast(i);
			answer = Math.min(answer, solution(n, weights, path, newDistance));
			path.pollLast();
		}

		return answer;
	}
}

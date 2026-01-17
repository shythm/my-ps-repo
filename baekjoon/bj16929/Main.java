package bj16929;

import java.util.*;

public class Main {

	public static void main(String[] args) {
		var app = new Main();
		var sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();
		sc.nextLine();

		char[][] map = new char[n][m];
		for (int i = 0; i < n; i++) {
			var line = sc.nextLine();
			for (int j = 0; j < m; j++) {
				map[i][j] = line.charAt(j);
			}
		}

		boolean exists = false;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (app.search(map, new HashSet<>(), j, i, -1)) {
					exists = true;
					break;
				}
			}
			if (exists) break;
		}
		System.out.println(exists ? "Yes" : "No");
	}

	private final int[][] movements = {
		// dx, dy, backwardIdx
		{  0, -1,  1 }, // 상
		{  0,  1,  0 }, // 하
		{ -1,  0,  3 }, // 좌
		{  1,  0,  2 }, // 우
	};

	private String generateKey(int x, int y) {
		return String.format("%d,%d", x, y);
	}

	boolean search(char[][] map, Set<String> graph, int currX, int currY, int backIdx) {
		// 해당 노드가 그래프에 포함되어 있는지 검사한다.
		if (graph.contains(generateKey(currX, currY))) {
			// 그렇다면 사이클 존재.
			return true;
		} else {
			// 그래프에 해당 노드 추가.
			graph.add(generateKey(currX, currY));
		}

		int n = map.length;
		int m = map[0].length;

		// 인접한 칸(상, 하, 좌, 우)을 하나씩 조사하자.
		for (int i = 0; i < movements.length; i++) {
			if (i == backIdx) {
				// 이전 노드로 되돌아가는 경우
				continue;
			}

			int nextX = currX + movements[i][0];
			int nextY = currY + movements[i][1];
			if (!(0 <= nextX && nextX < m && 0 <= nextY && nextY < n)) {
				// 유효하지 않은 인덱스라면
				continue;
			}

			if (map[nextY][nextX] != map[currY][currX]) {
				// 다음 노드가 현재 노드와 같은 타입(알파벳)이 아니라면
				continue;
			}

			if (search(map, graph, nextX, nextY, movements[i][2])) {
				return true;
			}
		}

		return false;
	}
}

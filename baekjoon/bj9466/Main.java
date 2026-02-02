package bj9466;

import java.util.*;

public class Main {
	private static final boolean DEBUG = false;

	public static void main(String[] args) {
		var app = new Main();
		var sc = new Scanner(System.in);

		int T = sc.nextInt();
		for (int i = 0; i < T; i++) {
			int n = sc.nextInt();
			int[] relations = new int[n];
			for (int j = 0; j < n; j++) {
				relations[j] = sc.nextInt() - 1;
			}

			int answer = app.solution(relations);
			System.out.println(answer);
		}
	}

	int solution(int[] relations) {
		int answer = relations.length;
		boolean[] visited = new boolean[relations.length];

		for (int i = 0; i < relations.length; i++) {
			if (DEBUG) {
				System.out.printf("Node #%d:\n", i);
			}

			if (visited[i]) {
				if (DEBUG) {
					System.out.println(" - Already visited");
				}
				continue;
			}
			Deque<Integer> stack = new LinkedList<>();

			int root = i;
			for (; !visited[root]; root = relations[root]) {
				// 스택에 방문 기록 저장
				stack.addLast(root);
				// 방문 표시(재방문 시 사이클 판단 로직으로 넘어가기 위함)
				visited[root] = true;

				if (DEBUG) {
					System.out.printf(" - Node #%d visited.\n", root);
				}
			}

			int counter = 0;
			boolean isCycle = false;
			while (!stack.isEmpty()) {
				int prev = stack.removeLast();
				counter++;
				if (prev == root) {
					// 사이클인 경우
					isCycle = true;
					break;
				}
			}

			if (isCycle) {
				if (DEBUG) {
					System.out.printf(" - The number of cycle nodes is %d.\n", counter);
				}
				answer -= counter;
			}
		}

		return answer;
	}
}

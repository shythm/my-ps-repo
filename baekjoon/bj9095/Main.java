package bj9095;

import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		var app = new Main();

		int T = sc.nextInt();
		for (int i = 0; i < T; i++) {
			int n = sc.nextInt();
			int answer = app.solution(n, 0);
			System.out.println(answer);
		}
	}

	int solution(int n, int result) {
		if (n == result) return 1;
		if (n < result) return 0;

		// n을 1, 2, 3의 합으로 나타낼 수 있는 경우의 수를 구하자.
		int answer = 0;

		answer += solution(n, result + 1);
		answer += solution(n, result + 2);
		answer += solution(n, result + 3);

		return answer;
	}
}

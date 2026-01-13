package bj2133;

import java.util.*;

public class Main {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();

		var app = new Main();
		int answer = app.solution(n, null);
		System.out.println(answer);
	}

	int solution(int n, Set<List<Integer>> candidates) {
		if (n % 2 == 1) {
			return 0; // 홀수라면 타일을 모두 채울 수 없다.
		}
		if (n == 2) {
			return 3; // 2가 들어오면 기본적으로 3가지의 경우밖에 없다.
		}
		if (candidates == null) {
			// 초기 진입 시 수행할 동작
			Set<List<Integer>> newCandidates = new HashSet<>();
			newCandidates.add(Collections.nCopies(n / 2, 2));
			return 2 + solution(n, newCandidates);
		}
		if (candidates.isEmpty()) {
			return 0; // 후보군이 비어있으면 더 이상 진행하지 않는다.
		}

		int answer = 0;
		Set<List<Integer>> newCandidates = new HashSet<>();
		for (var candidate : candidates) {
			// 경우의 수를 구한다.
			int numOfCases = 1;
			for (var item : candidate) {
				numOfCases *= (item == 2) ? 3 : 2; // 숫자 2면 3가지 경우 나머지는 모두 2가지
			}
			answer += numOfCases;
			// System.out.println(candidate + ", " + numOfCases);

			if (candidate.size() > 2) {
				// 새로운 후보들을 생성한다.
				for (int i = 0; i < candidate.size() - 1; i++) {
					List<Integer> newCandidate = new ArrayList<>();
					newCandidate.addAll(candidate.subList(0, i));
					newCandidate.add(candidate.get(i) + candidate.get(i + 1));
					newCandidate.addAll(candidate.subList(i + 2, candidate.size()));
					newCandidates.add(newCandidate);
				}
			}
		}

		answer += solution(n, newCandidates);
		return answer;
	}
}

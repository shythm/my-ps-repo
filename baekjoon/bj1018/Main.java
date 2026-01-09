package bj1018;

import java.util.*;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		sc.nextLine(); // 개행 문자 처리

		char[][] board = new char[n][m];
		for (int i = 0; i < n; i++) {
			String line = sc.nextLine();
			for (int j = 0; j < m; j++) {
				board[i][j] = line.charAt(j);
			}
		}

		Main app = new Main();
		int answer = app.solution(board);
		System.out.println(answer);
	}

	static final int BOARD_SIZE = 8;

	public int solution(char[][] board) {
		int answer = Integer.MAX_VALUE;
		int n = board.length;
		int m = board[0].length;

		for (int row = 0; row + BOARD_SIZE - 1 < n; row++) {
			for (int col = 0; col + BOARD_SIZE - 1 < m; col++) {
				int startWithWhite = BOARD_SIZE * BOARD_SIZE;
				int startWithBlack = BOARD_SIZE * BOARD_SIZE;

				for (int i = row; i < row + BOARD_SIZE; i++) {
					for (int j = col; j < col + BOARD_SIZE; j++) {
						char currColor = ((i + j) % 2 == 0) ? 'W' : 'B';
						if (board[i][j] == currColor) {
							startWithWhite--;
						} else {
							startWithBlack--;
						}
					}
				}

				int minDiff = Math.min(startWithWhite, startWithBlack);
				answer = Math.min(answer, minDiff);
			}
		}

		return answer;
	}
}
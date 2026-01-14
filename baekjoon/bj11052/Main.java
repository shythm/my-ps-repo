package bj11052;

import java.util.*;

public class Main {
    private static final boolean DEBUG = false;

    public static void main(String[] args) {
        var app = new Main();
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] prices = new int[n];
        for (int i = 0; i < n; i++) {
            prices[i] = sc.nextInt();
        }

        int answer = app.solution(n, prices);
        System.out.println(answer);
    }

    int solution(int n, int[] prices) {
        // i 번째 물건을 0개부터 (n / i)개까지 고르며 최댓값을 메모제이션한다.
        // 이때 i는 카드팩에 들어있는 카드의 수와 같다.
        int[][] dp = new int[n + 1][n + 1];

        for (int cardCountOfPack = 1; cardCountOfPack <= n; cardCountOfPack++) {
            int price = prices[cardCountOfPack - 1];

            for (int cardCount = 1; cardCount <= n; cardCount++) {
                int countOfPack = cardCount / cardCountOfPack;

                // 현재 카드팩을 고르지 않는 경우 이전 dp 테이블의 최적해를 이용한다.
                int optimal = dp[cardCountOfPack - 1][cardCount];

                if (countOfPack > 0) { // 현재 카드팩을 고를 수 있으면
                    for (int k = 1; k <= countOfPack; k++) { // 틀려서 해당 이터레이션 추가: 카드팩을 무조건 countOfPack 만큼 고르라는 보장은 없다.
                        optimal = Math.max(
                                optimal,
                                // 현재 카드팩 가격과 그렇게 카드팩을 구매하여 남은 카드의 수에 해당하는 최적해를 이전 dp 테이블로부터 구하여 더한다.
                                (k * price) + dp[cardCountOfPack - 1][cardCount - k * cardCountOfPack]
                        );
                    }
                }

                dp[cardCountOfPack][cardCount] = optimal;
            }
        }

        if (DEBUG) {
            for (int i = 0; i < n + 1; i++) {
                if (i > 0) {
                    System.out.print(i + ", " + prices[i - 1] + ": ");
                } else {
                    System.out.print("(none) ");
                }

                for (int j = 0; j < n + 1; j++) {
                    System.out.print(dp[i][j] + " ");
                }
                System.out.println();
            }
        }

        return dp[n][n];
    }
}

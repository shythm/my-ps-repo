package bj12869;

import java.util.*;

public class Main {

    private static final boolean DEBUG = false;

    public static void main(String[] args) {
        var app = new Main();
        var sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] scvHps = new int[3];
        for (int i = 0; i < n; i++) {
            scvHps[i] = sc.nextInt();
        }

        int[][][] dp = new int[61][61][61];
        int answer = app.search(n, dp, scvHps, new int[]{ 0, 0, 0 }, 0);
        System.out.println(answer);
    }

    int[][][] mutaliskAttackPermutations = {
        {
            { -9 },
        },
        {
            { -9, -3 },
            { -3, -9 },
        },
        {
            { -9, -3, -1 },
            { -9, -1, -3 },
            { -3, -9, -1 },
            { -3, -1, -9 },
            { -1, -9, -3 },
            { -1, -3, -9 },
        }
    };

    int search(int n, int[][][] dp, int[] scvHps, int[] mutaliskAttacks, int depth) {
        /*
         * 한 마리의 뮤탈리스크가 세 마리의 SCV를 가장 빠르게 처치할 수 있는 공격 수를 구해야 한다.
         * 한 마리의 뮤탈리스크는 한 번의 공격에 최대 세 마리의 SCV의 체력을 9, 3, 1만큼 깎을 수 있다.
         * 이때, 우리는 완전탐색으로 (1번 SCV, 2번 SCV, 3번 SCV), (2번 SCV, 1번 SCV, 3번 SCV) 등
         * 모든 경우를 살펴보아 가장 먼저 세 마리의 SCV 체력을 모두 0으로 만드는 경우를 찾아야 하는 것이다.
         * 이때 6(3!)^n 번 탐색을 진행하게 될 텐데, 이는 매우 큰 숫자이다.
         * 따라서 SCV의 체력을 키로 가지는 dp를 만들어 여기에 최적해를 기록하고, 필요한 경우 이를 사용하도록 한다.
         */
        int answer = Integer.MAX_VALUE;

        scvHps = scvHps.clone();
        for (int i = 0; i < n; i++) {
            // 뮤탈리스크가 SCV를 공격한다.
            scvHps[i] = Math.max(scvHps[i] + mutaliskAttacks[i], 0); // upper bound 0
        }

        Arrays.sort(scvHps); // 틀려서 GPT 물어봄 -> DP 기록 시 모두 같은 키로 기록해야 하는데, 그러지 않음. 따라서 오름차순으로 정렬 후 아래와 같이 내림차순으로 돌림.
        int temp = scvHps[0];
        scvHps[0] = scvHps[2];
        scvHps[2] = temp;

        // 만약 dp에 이미 기록된 최적해가 있다면 그것을 사용한다.
        int optimal = dp[scvHps[0]][scvHps[1]][scvHps[2]];
        if (optimal != 0) {
            return optimal;
        }

        if (scvHps[0] == 0 && scvHps[1] == 0 && scvHps[2] == 0) {
            // 모든 SCV의 체력이 0이 되었을 때
            return depth;
        }

        for (int i = 0; i < mutaliskAttackPermutations[n - 1].length; i++) {
            answer = Math.min(
                answer,
                search(n, dp, scvHps, mutaliskAttackPermutations[n - 1][i], depth + 1)
            );
        }

        // 해당 노드에서의 최적해를 구했으면 dp에 기록한다.
        dp[scvHps[0]][scvHps[1]][scvHps[2]] = answer;
        if (DEBUG) {
            System.out.printf("Optimal of (%d, %d, %d): %d%n", scvHps[0], scvHps[1], scvHps[2], answer);
        }

        return answer;
    }
}

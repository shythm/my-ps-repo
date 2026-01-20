package bj2293;

import java.util.*;

public class Main {

	private static final boolean DEBUG = true;

	public static void main(String[] args) {
		var sc = new Scanner(System.in);
		int n = sc.nextInt();
		int k = sc.nextInt();
		List<Integer> coins = new ArrayList<>(n);
		for (int i = 0; i < n; i++) {
			coins.add(sc.nextInt());
		}

		int[] dp = new int[k + 1];
		dp[0] = 1;

		for (var coin : coins) {
			for (int i = coin; i <= k; i++) {
				dp[i] = dp[i] + dp[i - coin];
			}
		}

		System.out.println(dp[k]);
		sc.close();
	}
}

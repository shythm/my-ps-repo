package bj2064;

import java.util.*;

public class Main {

	private static final boolean DEBUG = false;

	public static void main(String[] args) {
		var sc = new Scanner(System.in);

		// IP 주소들의 네트워크 주소를 구해야 한다.
		// 네트워크 주소를 알면 서브넷 마스크도 알 수 있다.
		int n = sc.nextInt();
		sc.nextLine();
		int[] ipAddresses = new int[n];
		for (int i = 0; i < n; i++) {
			String line = sc.nextLine();
			String[] blocks = line.split("\\.");
			for (int j = 0; j < 4; j++) {
				ipAddresses[i] |= (Integer.parseInt(blocks[j]) << (8 * (3 - j)));
			}
		}

		// 0xFFFFFFFF에서 왼쪽 시프트를 하면 서브넷 마스크를 만들 수 있다(이렇게 해야 m이 최소가 되는 네트워크를 만들 수 있다).
		// 모든 ipAddress에 대하여 서브넷 마스크와 bitwise-AND 연산을 하게 되면 네트워크 주소가 나오는데,
		// 그 네트워크 주소들이 모두 같으면 된다.
		int subnetMask = 0xFFFFFFFF;
		while (subnetMask != 0x00000000) {
			boolean isAllSameNetwork = true;
			final int networkAddress = ipAddresses[0] & subnetMask;

			for (int i = 1; i < n; i++) {
				if (networkAddress != (ipAddresses[i] & subnetMask)) {
					isAllSameNetwork = false;
					break;
				}
			}

			if (isAllSameNetwork) {
				if (DEBUG) {
					System.out.println("Network Address: " + Integer.toBinaryString(networkAddress));
					System.out.println("Subnet Mask: " + Integer.toBinaryString(subnetMask));
				}
				System.out.println(convertTpAddressToString(networkAddress));
				System.out.println(convertTpAddressToString(subnetMask));
				break;
			} else {
				subnetMask <<= 1;
			}
		}

		// 서브넷 마스크가 0이 되어버린 경우 대응안해서 틀림
		if (subnetMask == 0) {
			System.out.println(convertTpAddressToString(0));
			System.out.println(convertTpAddressToString(0));
		}

		sc.close();
	}

	private static String convertTpAddressToString(int ipAddress) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < 4; i++) {
			sb.append((ipAddress >>> (8 * (3 - i))) & 0xFF);
			sb.append('.');
		}
		sb.deleteCharAt(sb.length() - 1);
		return sb.toString();
	}
}

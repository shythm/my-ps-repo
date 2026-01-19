package bj14392;

import java.util.*;

public class Main {

    private static final boolean DEBUG = false;

    public static void main(String[] args) {
        var app = new Main();
        var sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();
        sc.nextLine();

        int[][] map = new int[n][m];
        for (int i = 0; i < n; i++) {
            String line = sc.nextLine();
            for (int j = 0; j < m; j++) {
                map[i][j] = line.charAt(j) - '0';
            }
        }

        int answer = app.solution(map);
        System.out.println(answer);
        sc.close();
    }

    public int solution(int[][] map) {
        int answer = 0;
        int numOfRows = map.length;
        int numOfCols = map[0].length;
        int allWallBitmask = 0xFFFFFFFF >>> (32 - numOfCols * numOfRows);

        if (DEBUG) {
            System.out.println(Integer.toBinaryString(allWallBitmask));
        }

        int bitmask = 0;
        while (bitmask <= allWallBitmask) {
            if (DEBUG) {
                System.out.printf("[%s]\n", Integer.toBinaryString(bitmask));
            }
            int result = calcSumOfPieces(map, bitmask);
            answer = Math.max(answer, result);
            bitmask++;

            if (DEBUG) {
                System.out.printf("Result = %d\n\n", result);
            }
        }

        return answer;
    }

    private int calcSumOfPieces(int[][] map, int bitmap) {
        int answer = 0;
        int[][] clonedMap = new int[map.length][];
        for (int i = 0; i < map.length; i++) {
            clonedMap[i] = new int[map[i].length];
            System.arraycopy(map[i], 0, clonedMap[i], 0, map[i].length);
        }
        map = clonedMap;
        int numOfRows = map.length;
        int numOfCols = map[0].length;

        for (int y = 0; y < numOfRows; y++) {
            for (int x = 0; x < numOfCols; x++) {
                // 이미 방문한 위치라면
                if (map[y][x] == -1) {
                    if (DEBUG) {
                        System.out.printf("(%d, %d) Skipped.\n", x, y);
                    }
                    continue;
                }

                if (DEBUG) {
                    System.out.printf("(%d, %d) Calculating...\n", x, y);
                }

                // 현재 위치를 기준으로 조사 진행
                int sum = 0;
                int nx = x;
                int ny = y;
                int baseDirection = (bitmap & (1 << (numOfCols * y + x))) != 0 ? 1 : 0;
                int newDirection = baseDirection;
                while (
                    // 범위를 벗어나지 않고, 다음 위치가 이전 위치와 같은 방향일 때
                    (nx < numOfCols) && (ny < numOfRows) && newDirection == baseDirection
                ) {
                    sum = (sum * 10) + map[ny][nx]; // 자릿수 증가 후 더함
                    if (DEBUG) {
                        System.out.printf("  (%d, %d) = %d Added. Sum = %d\n", nx, ny, map[ny][nx], sum);
                    }

                    map[ny][nx] = -1; // 방문 표시
                    if (baseDirection == 0) nx++;
                    else ny++;
                    newDirection = (bitmap & (1 << (numOfCols * ny + nx))) != 0 ? 1 : 0;

                    if (DEBUG) {
                        System.out.printf("  New bitmask = %s\n", Integer.toBinaryString((1 << (numOfCols * ny + nx))));
                    }
                }
                answer += sum;

                if (DEBUG) {
                    System.out.printf("  -> Calculated: %d\n", sum);
                }
            }
        }

        return answer;
    }
}

import java.util.*;

/**
 * Solution for NEERC'2010 Problem G: Game of 10
 * @author Roman Elizarov
 */
public class game_re {
	private static final int N = 4;
	private static final int WIN_SUM = N * (N + 1) / 2;
	private static final int W_LO = WIN_SUM - N;
	private static final int W_HI = WIN_SUM - 1;
	private static final String WIN_EXTRA = " WIN";

	public static void main(String[] args) throws Exception {
		new game_re().go();
	}

	private final int[][] f = new int[N][N];
	private final int[] rsum = new int[N];
	private final int[] csum = new int[N];
	private final int[] rcnt = new int[N];
	private final int[] ccnt = new int[N];

	void go() throws Exception {
		Scanner in = new Scanner(System.in);
		for (;;) {
			int r0 = in.nextInt() - 1;
			int c0 = in.nextInt() - 1;
			int k0 = in.nextInt();
			move(r0, c0, k0);
			// make winning move if we can
			for (int r = 0; r < N; r++)
				for (int c = 0; c < N; c++) {
					if (f[r][c] == 0 && rsum[r] >= W_LO && rsum[r] <= W_HI && rcnt[r] == N - 1) {
						printMove(r, c, WIN_SUM - rsum[r], WIN_EXTRA);
						return;
					}
					if (f[r][c] == 0 && csum[c] >= W_LO && csum[c] <= W_HI && ccnt[c] == N - 1) {
						printMove(r, c, WIN_SUM - csum[c], WIN_EXTRA);
						return;
					}
				}
			// make symmetric move otherwise
			printMove(N - 1 - r0, c0, N + 1 - k0, "");
		}
	}

	private void printMove(int r, int c, int k, String extra) {
		System.out.println((r + 1) + " " + (c + 1) + " " + k + extra);
		move(r, c, k);
	}

	private void move(int r, int c, int k) {
		assert k >= 1 && k <= N;
		assert f[r][c] == 0;
		f[r][c] = k;
		rsum[r] += k;
		csum[c] += k;
		rcnt[r]++;
		ccnt[c]++;
	}
}

import java.io.*;
import java.util.*;

public class game_md_draw {
	private static BufferedReader in;

	final static int n = 4;
	final static int m = 10;
	
	int[][] a = new int[n][n];

	private boolean react(String s) {
		StringTokenizer st = new StringTokenizer(s);
		int r = Integer.parseInt(st.nextToken()) - 1;
		int c = Integer.parseInt(st.nextToken()) - 1;
		int k = Integer.parseInt(st.nextToken());
		a[r][c] = k;
		int x = n - 1 - r;
		int y = n - 1 - c;
		int p = n + 1 - k;
		boolean win = false;
		loop:
		for (int flip = 0; flip < 2; flip++) {
			for (int i = 0; i < n; i++) {
				int sum = 0;
				int zeros = 0;
				int pos = -1;
				for (int j = 0; j < n; j++) {
					int v = (flip > 0) ? a[i][j] : a[j][i];
					if (v == 0) {
						zeros++;
						pos = j;
					} else {
						sum += v;
					}
				}
				int t = m - sum;
				if (zeros == 1 && t >= 1 && t <= n) {
					if (flip > 0) {
						x = i;
						y = pos;
					} else {
						x = pos;
						y = i;
					}
					win = true;
					p = t;
					break loop;
				}
			}
		}
		a[x][y] = p;
		System.out.println((x + 1) + " " + (y + 1) + " " + p + (win ? " WIN" : ""));
		return !win;
	}

	public void run() throws IOException {
		while (true) {
			String s = in.readLine();
			if (!react(s)) {
				return;
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new BufferedReader(new InputStreamReader(System.in));
		new game_md_draw().run();
		in.close();
	}
}

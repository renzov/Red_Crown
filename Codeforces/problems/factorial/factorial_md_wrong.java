import java.io.*;
import java.util.*;

public class factorial_md_wrong {
	private static String fileName = factorial_md_wrong.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;

	public void run() {
		int n = in.nextInt();
		int m = in.nextInt();
		int[] a = new int[n];
		int[] b = new int[m];
		int max = 0;
		for (int i = 0; i < n; i++) {
			a[i] = in.nextInt();
			max = Math.max(a[i], max);
		}
		for (int i = 0; i < m; i++) {
			b[i] = in.nextInt();
			max = Math.max(b[i], max);
		}
		int[] div = new int[max + 1];
		for (int i = 2; i <= max; i++) {
			if (div[i] > 0) {
				continue;
			}
			for (int j = i; j <= max; j += i) {
				div[j] = i;
			}
		}
		int[][] v = new int[max + 1][];
		v[1] = new int[max + 1];
		for (int x = 2; x <= max; x++) {
			v[x] = v[x - 1].clone();
			int y = x;
			while (y > 1) {
				int z = div[y];
				v[x][z]++;
				y /= z;
			}
		}
		int[] u = new int[max + 1];
		for (int x : a) {
			for (int i = 2; i <= max; i++) {
				u[i] += v[x][i];
			}
		}
		for (int x : b) {
			for (int i = 2; i <= max; i++) {
				u[i] -= v[x][i];
				if (u[i] < 0) {
					out.println(-1);
					return;
				}
			}
		}
		int ans = 0;
		StringBuilder sb = new StringBuilder();
		for (int x = max; x >= 2; x--) {
			int in = Integer.MAX_VALUE;
			for (int i = 2; i <= max; i++) {
				if (v[x][i] > 0) {
					in = Math.min(in, u[i] / v[x][i]);
				}
			}
			if (in > 0) {
				for (int i = 2; i <= max; i++) {
					u[i] -= in * v[x][i];
				}
				sb.append(x).append(" ").append(in).append(" ");
				ans++;
			}
		}
		out.println(ans);
		if (ans > 0) {
			out.println(sb.toString().trim());
		}
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new factorial_md_wrong().run();
		in.close();
		out.close();
	}
}

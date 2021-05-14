import java.io.*;
import java.util.*;

public class binary_md {
	private static String fileName = binary_md.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	private static final int BASE = 10;
	final int[] id = new int[BASE]; {
		for (int i = 0; i < BASE; i++) {
			id[i] = i;
		}
	}
	
	int[] power(int[] f, long n) {
		if (n < 2) {
			return (n == 1) ? f : id;
		} else if (n % 2 == 0) {
			int[] g = power(f, n / 2);
			return compose(g, g);
		} else {
			return compose(power(f, n - 1), f);
		}
	}
	
	int[] compose(int[] g, int[] f) {
		int[] r = new int[BASE];
		for (int i = 0; i < BASE; i++) {
			r[i] = g[f[i]];
		}
		return r;
	}
	
	public void run() {
		int[][] op = new int[BASE][BASE];
		int[][] opt = new int[BASE][BASE];
		for (int i = 0; i < BASE; i++) {
			for (int j = 0; j < BASE; j++) {
				opt[j][i] = op[i][j] = in.nextInt();
			}
		}
		long a = in.nextLong();
		long b = in.nextLong();
		int n = ("" + b).length();
		long ten = 1;
		String ans = "";
		for (int t = 0; t < n; t++) {
			long ax = (a / ten) / 10;
			int ay = (int) ((a / ten) % 10);
			long az = a % ten;
			long bx = (b / ten) / 10;
			int by = (int) ((b / ten) % 10);
			long bz = b % ten;
			int[] f = power(opt[ay], ten - 1 - az);
			if (ax < bx) {
				for (int i = ay + 1; i < BASE; i++) {
					f = compose(power(opt[i], ten), f);
				}
				int[] g = id;
				for (int i = 0; i < BASE; i++) {
					g = compose(power(opt[i], ten), g);
				}
				f = compose(power(g, bx - ax - 1), f);
				for (int i = 0; i < by; i++) {
					f = compose(power(opt[i], ten), f);
				}
			} else {
				for (int i = ay + 1; i < by; i++) {
					f = compose(power(opt[i], ten), f);
				}
			}
			f = compose(power(opt[by], bz + 1), f);
			ans = f[ay] + ans;
			ten *= 10;
		}
		while (ans.length() > 1 && ans.charAt(0) == '0') {
			ans = ans.substring(1);
		}
		out.println(ans);
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new binary_md().run();
		in.close();
		out.close();
	}
}

/*
    Solution for NEERC'2006 Problem I: Interconnect
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class interconnect_re {
	public static void main(String[] args) throws Exception {
		new interconnect_re().go();
	}

	static class Position {
		int[] a;

		Position(int[] a) {
			this.a = a;
		}

		public int hashCode() {
			return Arrays.hashCode(a);
		}

		public boolean equals(Object obj) {
			if (!(obj instanceof Position))
				return false;
			Position o = (Position) obj;
			return Arrays.equals(a, o.a);
		}
	}

	int n;
	int m;

	double[][] c;
	boolean[] f;

	Map<Position,Double> dp = new HashMap<Position, Double>();

	void go() throws Exception {
		Scanner in = new Scanner(new File("interconnect.in"));

		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();

		assert n >= 2 && n <= 30;
		assert m >= 0 && m <= 1000;

		c = new double[n + 1][n + 1];

		for (int i = 0; i < m; i++) {
			int u = in.nextInt();
			int v = in.nextInt();
			in.nextLine();
			assert u >= 1 && u <= n && v >= 1 && v <= n && u != v;
			c[u][v]++;
			c[v][u]++;
		}
		in.close();

		f = new boolean[n + 1];
		int cnt = 0;
		int[] s = new int[n];
		for (int i = 1; i <= n; i++)
			if (!f[i])
				s[cnt++] = scan(i);			
		double result = solve(new Position(trim(s, cnt)));
		
		PrintStream out = new PrintStream(new File("interconnect.out"));
		out.println(result);
		out.close();
	}

	double solve(Position p) {
		int k = p.a.length;
		if (k == 1)
			return 0;
		Double dpres = dp.get(p);
		if (dpres != null)
			return dpres;
		int ss = 0;
		int tc = 0;
		double ds = 0;
		for (int i = 0; i < k; i++) {
			int sq = p.a[i] * (p.a[i] - 1);
			ss += sq;
			tc += sq;
			for (int j = i + 1; j < k; j++) {
				int mu = 2 * p.a[i] * p.a[j]; 
				tc += mu;
				ds += mu * (1 + solve(new Position(merge(p.a, i, j))));
			}
		}
		// res * tc = ss * (1 + res) + ds
		double res = (ds + ss) / (tc - ss);
		dp.put(p, res);
		return res;
	}

	static int[] trim(int[] s, int n) {
		if (s.length <= n)
			return s;
		int[] t = new int[n];
		System.arraycopy(s, 0, t, 0, n);
		Arrays.sort(t);
		return t;
	}

	static int[] merge(int[] s, int i, int j) {
		int n = s.length;
		int[] t = new int[n - 1];
		System.arraycopy(s, 0, t, 0, j);
		System.arraycopy(s, j + 1, t, j, n - j - 1);
		t[i] = s[i] + s[j];
		Arrays.sort(t);
		return t;
	}

	int scan(int i) {
		if (f[i])
			return 0;
		f[i] = true;
		int s = 1;
		for (int j = 1; j <= n; j++)
			if (c[i][j] > 0)
				s += scan(j);
		return s;
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could added to a soulution source
	 * without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public static class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}

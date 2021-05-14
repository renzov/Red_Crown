/*
    Solution for NEERC'2006 Problem C: Celluar Automaton
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;

public class cell_re {
	public static void main(String[] args) throws Exception {
		new cell_re().go();
	}

	int n;
	int m;
	int d;
	int k;

	void go() throws Exception {
		Scanner in = new Scanner(new File("cell.in"));
		n = in.nextInt();
		m = in.nextInt();
		d = in.nextInt();
		k = in.nextInt();
		in.nextLine();

		assert n >= 1 && n <= 500;
		assert m >= 1 && m <= 1000000;
		assert d >= 0 && d <= (n - 1) / 2;
		assert k >= 1 && k <= 10000000;

		int[] c = new int[n];
		for (int i = 0; i < n; i++) {
			c[i] = in.nextInt();
			assert c[i] >= 0 && c[i] < m;
		}
		in.nextLine();
		in.close();

		// d-step
		int[] s = new int[n];
		for (int i = 0; i < n; i++)
			s[i] = Math.min(i, n - i) <= d ? 1 : 0;

		int[] a = new int[n];
		a[0] = 1;

		// invariant: a * s^k
		while (k > 0) {
			if ((k & 1) == 1) {
				a = fold(a, s);
				k--;
			}
			if (k > 0) {
				s = fold(s, s);
				k >>= 1;
			}
		}

		a = fold(c, a);
		
		PrintWriter out = new PrintWriter(new File("cell.out"));
		for (int i = 0; i < n; i++) {
			if (i > 0)
				out.print(" ");
			out.print(a[i]);
		}
		out.close();
	}

	int[] fold(int[] a, int[] b) {
		int[] c = new int[n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int k = (i + j) % n;
				c[k] = (int)((c[k] + (long)a[i] * b[j]) % m);
			}
		}
		return c;
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

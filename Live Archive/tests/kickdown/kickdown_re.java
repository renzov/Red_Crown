/*
    Solution for NEERC'2006 Problem K: Kickdown
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;

public class kickdown_re {
	public static void main(String[] args) throws Exception {
		new kickdown_re().go();
	}

	void go() throws Exception {
		Scanner in = new Scanner(new File("kickdown.in"));
		int[] a = read(in);
		int[] b = read(in);
		in.close();

		int best = Integer.MAX_VALUE;
		for (int i = -a.length; i < b.length; i++) {
			boolean ok = true;
			for (int j = 0; j < b.length; j++) {
				int k = j - i;
				if (k >= 0 && k < a.length && a[k] + b[j] > 3)
					ok = false;
			}
			if (ok) {
				int p = Math.min(i, 0);
				int q = Math.max(i + a.length, b.length);
				best = Math.min(best, q - p);
			}
		}

		PrintWriter out = new PrintWriter(new File("kickdown.out"));
		out.println(best);
		out.close();
	}

	private int[] read(Scanner in) {
		String s = in.next();
		in.nextLine();
		int n = s.length();
		assert n >= 1 && n <= 100;
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			char c = s.charAt(i);
			assert c == '1' || c == '2';
			a[i] = c - '0';
		}		
		return a;
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

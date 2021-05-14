/*
    Solution for NEERC'2006 Problem G: Graveyard
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;

public class graveyard_re {
	public static void main(String[] args) throws Exception {
		new graveyard_re().go();
	}

	void go() throws Exception {
		Scanner in = new Scanner(new File("graveyard.in"));
		int n = in.nextInt();
		int m = in.nextInt();
		assert n >= 2 && n <= 1000;
		assert m >= 1 && m <= 1000;
		in.nextLine();
		in.close();

		double sum = 0;
		for (int i = 1; i < n; i++) {
			double pos = (double)i / n;
			int k = (int)(pos * (n + m) + 0.5);
			double best = Double.POSITIVE_INFINITY;
			for (int j = k - 1; j <= k + 1; j++) {
				double dist = Math.abs(pos - (double)j / (n + m));
				best = Math.min(dist, best);
			}
			sum += best;
		}

		sum *= 10000;

		PrintWriter out = new PrintWriter(new File("graveyard.out"));
		out.println(Math.floor(sum * 10000 + .5) / 10000);
		out.close();
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

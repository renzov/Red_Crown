/*
    Solution for NEERC'2006 Problem J: Java vs C++
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;

public class java_c_re {
	public static void main(String[] args) throws Exception {
		new java_c_re().go();
	}

	static final String ERROR = "Error!";

	void go() throws Exception {
		Scanner in = new Scanner(new File("java_c.in"));
		String s = in.next();
		in.nextLine();
		int n = s.length();
		assert n >= 1 && n <= 100;
		for (int i = 0; i < n; i++) {
			char c = s.charAt(i);
			assert isUpper(c) || isLower(c) || c == '_';
		}
		in.close();

		String result = solve(s);

		PrintWriter out = new PrintWriter(new File("java_c.out"));
		out.println(result);
		out.close();
	}

	boolean isLower(char c) {
		return c >= 'a' && c <= 'z';
	}

	boolean isUpper(char c) {
		return c >= 'A' && c <= 'Z';
	}

	char toLower(char c) {
		return isUpper(c) ? (char)(c - 'A' + 'a') : c;
	}

	char toUpper(char c) {
		return isLower(c) ? (char)(c - 'a' + 'A') : c;
	}

	String solve(String s) {
		if (!isLower(s.charAt(0)))
			return ERROR;
		boolean upper = false;
		boolean under = false;
		int n = s.length();
		for (int i = 0; i < n; i++) {
			char c = s.charAt(i);
			if (isUpper(c))
				upper = true;
			if (c == '_')
				under = true;
		}
		if (upper && under)
			return ERROR;
		StringBuilder sb = new StringBuilder();
		if (upper) {
			// Java -> C++
			for (int i = 0; i < n; i++) {
				char c = s.charAt(i);
				if (isUpper(c))
					sb.append('_');
				sb.append(toLower(c));
			}
		} else {
			// C++ -> Java
			boolean was_under = false;
			for (int i = 0; i < n; i++) {
				char c = s.charAt(i);
				if (c == '_') {
					if (was_under)
						return ERROR;
					was_under = true;
				} else {
					if (was_under) {
						sb.append(toUpper(c));
						was_under = false;
					} else
						sb.append(c);
				}
			}
			if (was_under)
				return ERROR;
		}
		return sb.toString();
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

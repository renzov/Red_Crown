/*
    Solution for NEERC'2006 Problem B: Billing Tables
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;

public class billing_re {
	public static void main(String[] args) throws Exception {
		new billing_re().go();
	}

	static final String INVALID = "invalid";

	static class Node {
		String name;
		Node[] next;

		Node(String name) {
			this.name = name;
		}
	}

	Node root = new Node(INVALID);

	void go() throws Exception {
		Scanner in = new Scanner(new File("billing.in"));
		int n = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= 100;
		String[] as = new String[n];
		String[] bs = new String[n];
		String[] ns = new String[n];
		for (int i = 0; i < n; i++) {
			String a = in.next();
			String ms = in.next();
			String b = in.next();
			String name = in.next();
			in.nextLine();

			assert ms.equals("-");
			assert b.length() >= 1 && b.length() <= a.length() && a.length() <= 11;
			assert b.compareTo(a.substring(a.length() - b.length())) >= 0;
			assert a.matches("[0-9]+");
			assert b.matches("[0-9]+");
			assert name.matches("[a-z]+");

			as[i] = a;
			bs[i] = b;
			ns[i] = name;
		}
		in.close();

		for (int i = n; --i >= 0;)
			put(as[i], bs[i], ns[i]);

		collapse(root);

		PrintWriter out = new PrintWriter(new File("billing.out"));
		if (count(root) != 0)
			ensureNext(root);
		out.println(count(root));
		print(out, root, "");
		out.close();
	}

	void put(String a, String b, String name) {
		int b0 = a.length() - b.length();
		int i = 0;
		while (i < b.length() && a.charAt(b0 + i) == b.charAt(i))
			i++;
		String c = a.substring(0, b0 + i);
		String d = a.substring(b0 + i);
		String e = b.substring(i);
		putRange(expand(root, c), d, e, name);
	}

	void ensureNext(Node node) {
		if (node.name != null) {
			node.next = new Node[10];
			for (int i = 0; i < 10; i++)
				node.next[i] = new Node(node.name);
			node.name = null;
		}
	}

	Node expand(Node node, String a) {
		if (a.length() == 0)
			return node;
		ensureNext(node);
		return expand(node.next[a.charAt(0) - '0'], a.substring(1));

	}

	void putRange(Node node, String a, String b, String name) {
		assert a.length() == b.length();
		if (isEq(a, '0') && isEq(b, '9')) {
			node.name = name;
			node.next = null;
			return;
		}
		ensureNext(node);
		int a0 = a.charAt(0) - '0';
		int b0 = b.charAt(0) - '0';
		for (int i = a0; i <= b0; i++)
			putRange(node.next[i],
					i == a0 ? a.substring(1) : getEq(a.length() - 1, '0'),
					i == b0 ? b.substring(1) : getEq(b.length() - 1, '9'),
					name);
	}

	boolean isEq(String a, char c) {
		for (int i = 0; i < a.length(); i++)
			if (a.charAt(i) != c)
				return false;
		return true;
	}

	String getEq(int n, char c) {
		StringBuilder sb = new StringBuilder(n);
		for (int i = 0; i < n; i++)
			sb.append(c);
		return sb.toString();
	}

	void collapse(Node node) {
		if (node.name != null)
			return;
		String name = "";
		for (int i = 0; i < 10; i++) {
			collapse(node.next[i]);
			if ("".equals(name))
				name = node.next[i].name;
			if (name != null && !name.equals(node.next[i].name))
				name = null;
		}
		if (name != null) {
			node.name = name;
			node.next = null;
		}
	}

	int count(Node node) {
		if (node.name != null)
			return INVALID.equals(node.name) ? 0 : 1;
		int res = 0;
		for (int i = 0; i < 10; i++)
			res += count(node.next[i]);
		return res;

	}

	void print(PrintWriter out, Node node, String pre) {
		if (node.name != null) {
			if (!INVALID.equals(node.name))
				out.printf("%s %s%n", pre, node.name);
			return;
		}
		for (int i = 0; i < 10; i++)
			print(out, node.next[i], pre + (char) (i + '0'));
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


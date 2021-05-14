import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.List;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class ideal_petr {
	static class Vertex {
		int equivalenceClass = -1;
		Edge by = null;
		List<Edge> outgo = new ArrayList<Edge>();
	}

	static class Edge implements Comparable<Edge> {
		Vertex src;
		Vertex dst;
		int color;

		Edge(Vertex src, Vertex dst, int color) {
			this.src = src;
			this.dst = dst;
			this.color = color;
		}

		public int compareTo(Edge o) {
			return color - o.color;
		}
	}

	public void run() {
		int n = in.readInt();
		int m = in.readInt();
		Vertex[] v = new Vertex[n];
		for (int i = 0; i < n; ++i)
			v[i] = new Vertex();
		for (int j = 0; j < m; ++j) {
			int a = in.readInt() - 1;
			int b = in.readInt() - 1;
			int c = in.readInt();
			v[a].outgo.add(new Edge(v[a], v[b], c));
			v[b].outgo.add(new Edge(v[b], v[a], c));
		}
		int numEquivalenceClasses = 1;
		v[0].equivalenceClass = 0;
		Vertex[] queue = new Vertex[n];
		int qTail = 0;
		int qHead = 1;
		queue[0] = v[0];
		while (qTail < qHead) {
			int start = qTail;
			List<Edge> cur = new ArrayList<Edge>();
			while (qTail < qHead && queue[qTail].equivalenceClass == queue[start].equivalenceClass) {
				cur.addAll(queue[qTail].outgo);
				++qTail;
			}
			Collections.sort(cur);
			int lastColor = -1;
			for (Edge e : cur) {
				if (e.dst.equivalenceClass < 0) {
					if (e.color != lastColor) {
						++numEquivalenceClasses;
						lastColor = e.color;
					}
					e.dst.equivalenceClass = numEquivalenceClasses - 1;
					e.dst.by = e;
					queue[qHead++] = e.dst;
				}
			}
		}
		List<Edge> res = new ArrayList<Edge>();
		Vertex cur = v[n - 1];
		while (cur.by != null) {
			res.add(cur.by);
			cur = cur.by.src;
		}
		Collections.reverse(res);
		out.println(res.size());
		for (int i = 0; i < res.size(); ++i) {
			if (i > 0) out.print(" ");
			out.print(res.get(i).color);
		}
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		ideal_petr solver = new ideal_petr();
		solver.run();
		solver.out.close();
	}

	public ideal_petr() {
		String id = getClass().getName().substring(0, getClass().getName().indexOf('_')).toLowerCase();

		try {
			System.setIn(new FileInputStream(id + ".in"));
			System.setOut(new PrintStream(new FileOutputStream(id + ".out")));
//			System.setIn(new FileInputStream("input.txt"));
//			System.setOut(new PrintStream(new FileOutputStream("output.txt")));
		} catch (FileNotFoundException e) {
			throw new RuntimeException();
		}
		in = new InputReader(System.in);
		out = new PrintWriter(System.out);
	}

	private static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar, numChars;

		public InputReader(InputStream stream) {
			this.stream = stream;
		}

		private int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public int readInt() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public long readLong() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			long res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public String readString() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuffer res = new StringBuffer();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		private String readLine0() {
			StringBuffer buf = new StringBuffer();
			int c = read();
			while (c != '\n' && c != -1) {
				buf.appendCodePoint(c);
				c = read();
			}
			return buf.toString();
		}

		public String readLine() {
			String s = readLine0();
			while (s.trim().length() == 0)
				s = readLine0();
			return s;
		}

		public String readLine(boolean ignoreEmptyLines) {
			if (ignoreEmptyLines)
				return readLine();
			else
				return readLine0();
		}

		public BigInteger readBigInteger() {
			try {
				return new BigInteger(readString());
			} catch (NumberFormatException e) {
				throw new InputMismatchException();
			}
		}

		public char readCharacter() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			return (char) c;
		}

		public double readDouble() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			double res = 0;
			while (!isSpaceChar(c) && c != '.') {
				if (c < '0' || c > '9') {
					if (c == 'e' || c == 'E') {
						int e = readInt();
						return res * Math.pow(10, e);
					}
					throw new InputMismatchException();
				}
				res *= 10;
				res += c - '0';
				c = read();
			}
			if (c == '.') {
				c = read();
				double m = 1;
				while (!isSpaceChar(c)) {
					if (c == 'e' || c == 'E') {
						int e = readInt();
						return res * Math.pow(10, e);
					}
					if (c < '0' || c > '9')
						throw new InputMismatchException();
					m /= 10;
					res += (c - '0') * m;
					c = read();
				}
			}
			return res * sgn;
		}
	}
}

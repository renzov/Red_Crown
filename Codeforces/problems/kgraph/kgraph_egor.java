import java.io.*;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Comparator;
import java.util.InputMismatchException;
import java.util.TreeSet;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class kgraph_egor {
	public void run() {
		int n = in.readInt();
		int m = in.readInt();
		int[] a = new int[m];
		int[] b = new int[m];
		for (int i = 0; i < m; i++) {
			a[i] = in.readInt() - 1;
			b[i] = in.readInt() - 1;
		}
		final int[] d = new int[n];
		for (int i = 0; i < m; i++) {
			d[a[i]]++;
			d[b[i]]++;
		}
		int k = 0;
		for (int i = 0; i < n; i++)
			k = Math.max(k, d[i]);
		if (k % 2 == 0)
			k++;
		int[] dd = new int[n];
		int[][] e = new int[n][];
		for (int i = 0; i < n; i++)
			e[i] = new int[d[i]];
		for (int i = 0; i < m; i++) {
			e[a[i]][dd[a[i]]++] = b[i];
			e[b[i]][dd[b[i]]++] = a[i];
		}
		TreeSet<Integer> q = new TreeSet<Integer>(new Comparator<Integer>() {
			public int compare(Integer o1, Integer o2) {
				if (d[o1] != d[o2])
					return d[o1] - d[o2];
				return o1 - o2;
			}
		});
		for (int i = 0; i < n; i++)
			q.add(i);
		int[] s = new int[n];
		for (int i = 0; i < n; i++) {
			int v = q.first();
			s[i] = v;
			q.remove(v);
			for (int vv : e[v]) {
				if (q.contains(vv)) {
					q.remove(vv);
					d[vv]--;
					q.add(vv);
				}
			}
		}
		int[] ans = new int[n];
		boolean[] p = new boolean[n];
		boolean[] w = new boolean[k];
		for (int i = n - 1; i >= 0; i--) {
			int v = s[i];
			Arrays.fill(w, 0, Math.min(d[v] + 1, k), false);
			for (int vv : e[v]) {
				if (p[vv])
					w[ans[vv]] = true;
			}
			for (int j = 0; j < k; j++) {
				if (!w[j]) {
					ans[v] = j;
					break;
				}
			}
			p[v] = true;
		}
		out.println(k);
		for (int z : ans)
			out.println(z + 1);
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		kgraph_egor solver = new kgraph_egor();
		solver.run();
		solver.out.close();
	}

	public kgraph_egor() {
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

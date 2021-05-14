import java.io.*;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Comparator;
import java.util.InputMismatchException;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class evacuation_egor {
	public void run() {
		int n = in.readInt();
		final int[] a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = in.readInt();
		int m = in.readInt();
		final int[] b = new int[m];
		for (int i = 0; i < m; i++)
			b[i] = in.readInt();
		Integer[] o1 = new Integer[n];
		Integer[] o2 = new Integer[m];
		for (int i = 0; i < n; i++)
			o1[i] = i;
		for (int j = 0; j < m; j++)
			o2[j] = j;
		Arrays.sort(o1, new Comparator<Integer>() {
			public int compare(Integer o1, Integer o2) {
				return a[o1] - a[o2];
			}
		});
		Arrays.sort(o2, new Comparator<Integer>() {
			public int compare(Integer o1, Integer o2) {
				return b[o1] - b[o2];
			}
		});
		long[] d = new long[n + 1];
		long[] e = new long[n + 1];
		int[][] last = new int[m + 1][n + 1];
		Arrays.fill(d, Long.MAX_VALUE / 2);
		d[o1[0]] = 0;
		for (int ii = 0; ii < m; ii++) {
			int i = o2[ii];
			e[o1[0]] = Long.MAX_VALUE / 2;
			for (int jj = 1; jj <= n; jj++) {
				int j = jj == n ? n : o1[jj];
				int lj = o1[jj - 1];
				if (e[lj] < d[lj]) {
					e[j] = e[lj] + Math.abs(a[lj] - b[i]);
					last[ii][jj] = ii;
				} else {
					e[j] = d[lj] + Math.abs(a[lj] - b[i]);
					last[ii][jj] = ii - 1;
				}
			}
			long[] t = d;
			d = e;
			e = t;
		}
		int curi = m - 1;
		int curj = n;
		int[] ans = new int[n];
		while (curi != -1) {
			ans[o1[curj - 1]] = o2[curi] + 1;
			curi = last[curi][curj];
			curj--;
		}
		out.println(d[n]);
		out.print(ans[0]);
		for (int i = 1; i < n; i++)
			out.print(" " + ans[i]);
		out.println();
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		evacuation_egor solver = new evacuation_egor();
		solver.run();
		solver.out.close();
	}

	public evacuation_egor() {
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

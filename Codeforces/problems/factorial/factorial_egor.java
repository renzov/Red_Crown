import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class factorial_egor {
	private boolean isPrime(int n) {
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0)
				return false;
		}
		return true;
	}

	public void run() {
		int n = in.readInt();
		int m = in.readInt();
		int[] p = getPrimes(10000);
		int[][] f = new int[10007][p.length];
		for (int i = 1; i < f.length; i++) {
			for (int j = 0; j < p.length; j++) {
				f[i][j] = get(i, p[j]);
			}
		}
		int[] q = new int[p.length];
		for (int i = 0; i < n; i++) {
			int x = in.readInt();
			for (int j = 0; j < p.length; j++)
				q[j] += f[x][j];
		}
		for (int i = 0; i < m; i++) {
			int x = in.readInt();
			for (int j = 0; j < p.length; j++)
				q[j] -= f[x][j];
		}
		boolean good = true;
		for (int i = 0; i < p.length; i++) {
			if (q[i] < 0) {
				good = false;
				break;
			}
		}
		if (!good) {
			out.println(-1);
			return;
		}
		List<Integer> ans = new ArrayList<Integer>();
		for (int i = f.length - 1; i >= 2; i--) {
			int mx = Integer.MAX_VALUE;
			for (int j = 0; j < p.length; j++) {
				if (f[i][j] != 0)
					mx = Math.min(mx, q[j] / f[i][j]);
			}
			if (mx != 0) {
				ans.add(i);
				ans.add(mx);
				for (int j = 0; j < p.length; j++)
					q[j] -= mx * f[i][j];
			}
		}
		out.println(ans.size() / 2);
		if (ans.size() != 0) {
			boolean ff = true;
			for (int a : ans) {
				if (!ff)
					out.print(" ");
				else
					ff = false;
				out.print(a);
			}
			out.println();
		}
	}

	private int get(int n, int p) {
		int res = 0;
		while (n >= p) {
			n /= p;
			res += n;
		}
		return res;
	}

	private int[] getPrimes(int n) {
		boolean[] isNotPrimes = new boolean[n];
		for (int i = 2; i * i <= n; i++) {
			if (isNotPrimes[i])
				continue;
			for (int j = i * i; j < n; j += i)
				isNotPrimes[j] = true;
		}
		int q = 0;
		for (int i = 2; i < n; i++) {
			if (!isNotPrimes[i])
				q++;
		}
		int ind = 0;
		int[] res = new int[q];
		for (int i = 2; i < n; i++) {
			if (!isNotPrimes[i])
				res[ind++] = i;
		}
		return res;
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		factorial_egor solver = new factorial_egor();
		solver.run();
		solver.out.close();
	}

	public factorial_egor() {
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

import java.io.*;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.InputMismatchException;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class binary_petr {
	int[][] op;

	public void run() {
		op = new int[10][10];
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
				op[i][j] = in.readInt();
		long a = in.readLong();
		long b = in.readLong();
		String res = "";
		long p10 = 1;
		for (int digit = 0; digit <= 18; ++digit) {
			res = (char) ('0' + oneDigit(a, b, p10, digit)) + res;
			p10 *= 10;
		}
		out.println(new BigInteger("0" + res));
	}

	private int oneDigit(long a, long b, long p10, int digit) {
		if (digit == 18) {
			if (b == p10)
				if (a == p10)
					return 1;
				else
					return op[0][1];
			else
				return 0;
		}
		int first = (int) ((a / p10) % 10);
		++a;
		return applyIt(first, a, b, p10);
	}

	private int applyIt(int first, long a, long b, long p10) {
		if (a > b)
			return first;
		if (a % (p10 * 10) != 0) {
			long aChanged = Math.min((a / p10 + 1) * p10, b + 1);
			first = iterate(first, (int) ((a / p10) % 10), aChanged - a);
			return applyIt(first, aChanged, b, p10);
		}
		if (b % (p10 * 10) != (p10 * 10 - 1)) {
			long bChanged = Math.max((b / p10) * p10 - 1, a - 1);
			return iterate(applyIt(first, a, bChanged, p10), (int) ((b / p10) % 10), b - bChanged);
		}
		int[] major = new int[10];
		for (int i = 0; i < 10; ++i)
			major[i] = i;
		for (int dig = 0; dig < 10; ++dig) {
			major = combine(major, iterateTransform(dig, p10));
		}
		major = transformManyTimes(major, (b + 1 - a) / p10 / 10);
		first = major[first];
		return first;
	}

	private int iterate(int start, int what, long cnt) {
		int[] transform = new int[10];
		for (int i = 0; i < 10; ++i)
			transform[i] = op[i][what];
		return applyManyTimes(start, transform, cnt);
	}

	private int[] iterateTransform(int what, long cnt) {
		int[] transform = new int[10];
		for (int i = 0; i < 10; ++i)
			transform[i] = op[i][what];
		return transformManyTimes(transform, cnt);
	}

	private int[] combine(int[] a, int[] b) {
		int[] c = new int[10];
		for (int i = 0; i < 10; ++i)
			c[i] = b[a[i]];
		return c;
	}

	private int[] transformManyTimes(int[] transform, long cnt) {
		int[] res = new int[10];
		for (int i = 0; i < 10; ++i)
			res[i] = applyManyTimes(i, transform, cnt);
		return res;
	}

	private int applyManyTimes(int start, int[] transform, long cnt) {
		long[] seen = new long[10];
		Arrays.fill(seen, -1);
		for (long step = 0; step < cnt; ++step) {
			if (seen[start] >= 0) {
				long period = step - seen[start];
				long periods = Math.max(0, (cnt - step) / period - 5);
				step += period * periods;
			}
			seen[start] = step;
			start = transform[start];
		}
		return start;
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		binary_petr solver = new binary_petr();
		solver.run();
		solver.out.close();
	}

	public binary_petr() {
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

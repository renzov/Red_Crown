
import java.io.*;
import java.math.BigInteger;
import java.util.InputMismatchException;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class game_petr {
	public void run() {
		int[][] data = new int[4][4];

		while (true) {
			int r = in.readInt() - 1;
			int c = in.readInt() - 1;
			int k = in.readInt();
			data[r][c] = k;
			int[] cnt = new int[4];
			for (int i = 0; i < 4; ++i) {
				int sum = 0;
				int got = 0;
				int posSum = 0;
				for (int j = 0; j < 4; ++j)
					if (data[i][j] != 0) {
						sum += data[i][j];
						++got;
						posSum += j;
					}
				if (got == 3 && 10 - sum >= 1 && 10 - sum <= 4) {
					out.println((i + 1) + " " + (7 - posSum) + " " + (10 - sum) + " WIN");
					out.flush();
					return;
				}
			}
			for (int j = 0; j < 4; ++j) {
				int sum = 0;
				int got = 0;
				int posSum = 0;
				for (int i = 0; i < 4; ++i)
					if (data[i][j] != 0) {
						sum += data[i][j];
						++got;
						posSum += i;
					}
				if (got == 3 && 10 - sum >= 1 && 10 - sum <= 4) {
					out.println((7 - posSum) + " " + (j + 1) + " " + (10 - sum) + " WIN");
					out.flush();
					return;
				}
				cnt[j] = got;
			}
			int cc = c ^ 1;
			data[r][cc] = 5 - k;
			out.println((r + 1) + " " + (cc + 1) + " " + (5 - k));
			out.flush();
		}
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		game_petr solver = new game_petr();
		solver.run();
		solver.out.close();
	}

	public game_petr() {
		String id = getClass().getName().substring(0, getClass().getName().indexOf('_')).toLowerCase();

//		try {
//			System.setIn(new FileInputStream(id + ".in"));
//			System.setOut(new PrintStream(new FileOutputStream(id + ".out")));
//			System.setIn(new FileInputStream("input.txt"));
//			System.setOut(new PrintStream(new FileOutputStream("output.txt")));
//		} catch (FileNotFoundException e) {
//			throw new RuntimeException();
//		}
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
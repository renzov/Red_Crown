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
public class hands_egor {
	private static class Hand {
		private final int[] c;
		private final int rank;
		private final int[] cc = new int[5];


		public Hand(int[] c) {
			this.c = c;
			rank = rank();
		}

		public int rank() {
			boolean flush = isFlush();
			boolean straight = isStraight();
			boolean quads = false;
			boolean trips = false;
			int numPairs = 0;
			for (int i = 0; i < 5; i++) {
				int q = 0;
				for (int j = i; j < 5; j++) {
					if (c[i] / 4 == c[j] / 4)
						q++;
				}
				if (q == 4) {
					for (int j = 0; j < 4; j++) {
						cc[j] = c[i] / 4;
					}
					for (int j = 0; j < 5; j++) {
						if (c[i] / 4 != c[j] / 4)
							cc[4] = c[j] / 4;
					}
					quads = true;
					break;
				}
				else if (q == 3) {
					for (int j = 0; j < 3; j++) {
						cc[j] = c[i] / 4;
					}
					int ind = 3;
					for (int j = 0; j < 5; j++) {
						if (c[i] / 4 != c[j] / 4)
							cc[ind++] = c[j] / 4;
					}
					trips = true;
					if (cc[3] == cc[4])
						numPairs = 1;
					else
						numPairs = 0;
					break;
				} else if (q == 2)
					numPairs++;
			}
			if (straight && flush)
				return 8;
			if (quads)
				return 7;
			if (trips && numPairs == 1)
				return 6;
			if (flush) {
				for (int i = 0; i < 5; i++)
					cc[i] = c[i] / 4;
				return 5;
			}
			if (straight)
				return 4;
			if (trips) {
				//Arrays.sort(cc, 3, 5);
				return 3;
			}
			if (numPairs == 2) {
				int ind = 0;
				for (int i = 0; i < 5; i++) {
					for (int j = i + 1; j < 5; j++) {
						if (c[i] / 4 == c[j] / 4) {
							cc[ind++] = c[i] / 4;
							cc[ind++] = c[j] / 4;
						}
					}
				}
				for (int i = 0; i < 5; i++) {
					if (c[i] / 4 != cc[0] && c[i] / 4 != cc[2])
						cc[4] = c[i] / 4;
				}
				if (cc[0] > cc[2]) {
					int ccc = cc[2];
					cc[2] = cc[3] = cc[0];
					cc[0] = cc[1] = ccc;
				}
			}
			if (numPairs == 1) {
				int ind = 0;
				for (int i = 0; i < 5; i++) {
					for (int j = i + 1; j < 5; j++) {
						if (c[i] / 4 == c[j] / 4) {
							cc[ind++] = c[i] / 4;
							cc[ind++] = c[j] / 4;
						}
					}
				}
				for (int i = 0; i < 5; i++) {
					if (c[i] / 4 != cc[0])
						cc[ind++] = c[i] / 4;
				}
				//Arrays.sort(cc, 2, 5);
			}
			if (numPairs == 0) {
				for (int i = 0; i < 5; i++)
					cc[i] = c[i] / 4;
			}
			return numPairs;
		}

		private boolean isFlush() {
			int x = c[0] % 4;
			for (int cc : c) {
				if (cc % 4 != x)
					return false;
			}
			return true;
		}

		public boolean isStraight() {
			boolean good = true;
			for (int i = 1; i < 5; i++) {
				if (c[i] / 4 != c[i - 1] / 4 + 1)
					good = false;
			}
			if (good) {
				for (int i = 0; i < 5; i++)
					cc[i] = c[i] / 4;
				return true;
			}
			if (c[0] / 4 == 0 && c[1] / 4 == 9 && c[2] / 4 == 10 && c[3] / 4 == 11 && c[4] / 4 == 12) {
				cc[0] = c[1] / 4;
				cc[1] = c[2] / 4;
				cc[2] = c[3] / 4;
				cc[3] = c[4] / 4;
				cc[4] = c[0] / 4;
			}
			return c[0] / 4 == 0 && c[1] / 4 == 9 && c[2] / 4 == 10 && c[3] / 4 == 11 && c[4] / 4 == 12;
		}
	}

	private static Comparator<Hand> COMPARATOR = new Comparator<Hand>() {
		public int compare(Hand o1, Hand o2) {
			if (o1.rank != o2.rank)
				return o1.rank - o2.rank;
			for (int i = 0; i < 5; i++) {
				if (o1.cc[i] != o2.cc[i])
					return o2.cc[i] - o1.cc[i];
			}
			return 0;
		}
	};

	public void run() {
		TreeSet<Hand> s = new TreeSet<Hand>(COMPARATOR);
		for (int i = 0; i < 13; i++) {
			for (int j = i; j < 13; j++) {
				for (int k = j; k < 13; k++) {
					for (int l = k; l < 13; l++) {
						for (int m = l; m < 13; m++) {
							int a = i * 4;
							int b = j * 4;
							if (a == b)
								b++;
							int c = k * 4;
							if (c <= b)
								c = b + 1;
							int d = l * 4;
							if (d <= c)
								d = c + 1;
							int e = m * 4;
							if (e <= d)
								e = d + 1;
							if (e >= 52)
								continue;
							Hand hand = new Hand(new int[]{a, b, c, d, e});
							s.add(hand);
							e++;
							if (e >= 52)
								continue;
							hand = new Hand(new int[]{a, b, c, d, e});
							s.add(hand);
						}
					}
				}
			}
		}
		//System.err.println(s.size());
		int[] c = new int[5];
		for (int i = 0; i < 5; i++) {
			char v = in.readCharacter();
			char t = in.readCharacter();
			int res;
			if (v == 'A')
				res = 0;
			else if (v == 'K')
				res = 4;
			else if (v == 'Q')
				res = 8;
			else if (v == 'J')
				res = 12;
			else if (v == 'T')
				res = 16;
			else
				res = 20 + ('9' - v) * 4;
			if (t == 'C')
				res++;
			else if (t == 'H')
				res += 2;
			else if (t == 'D')
				res += 3;
			c[i] = res;
		}
		Arrays.sort(c);
		out.println(s.headSet(new Hand(c)).size() + 1);
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		hands_egor solver = new hands_egor();
		solver.run();
		solver.out.close();
	}

	public hands_egor() {
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

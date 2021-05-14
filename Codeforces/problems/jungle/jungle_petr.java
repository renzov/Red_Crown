import java.io.*;
import java.math.BigInteger;
import java.util.InputMismatchException;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class jungle_petr {
	private static final double EPS = 1e-7;

	static class Point {
		final double x;
		final double y;

		public Point(InputReader in) {
			x = in.readDouble();
			y = in.readDouble();
		}

		int crossProductSign(Point other) {
			double z = x * other.y - y * other.x;
			if (Math.abs(z) < 1e-12)
				return 0;
			else if (z < 0)
				return -1;
			else
				return 1;
		}

		Point(double x, double y) {
			this.x = x;
			this.y = y;
		}

		Point subtract(Point other) {
			return new Point(x - other.x, y - other.y);
		}

		Point normalize() {
			double z = Math.sqrt(x * x + y * y);
			return new Point(x / z, y / z);
		}
	}

	public void run() {
		int n = in.readInt();
		Point[] p = new Point[n];
		for (int i = 0; i < n; ++i) {
			p[i] = new Point(in);
		}
		for (int i = 0; i < n - 1 - i; ++i) {
			Point tmp = p[i];
			p[i] = p[n - 1 - i];
			p[n - 1 - i] = tmp;
		}
		out.println(solve(p));
	}

	private int solve(Point[] p) {
		int left = 0;
		int right = p.length - 2;
		while (right - left > 1) {
			int delta = (right + left) / 2;
			if (isEmpty(p, delta))
				right = delta;
			else
				left = delta;
		}
		return right;
	}

	static class Border {
		Point start;
		Point v;
		double left;
		double right;

		Border(Point start, Point v, double left, double right) {
			this.start = start;
			this.v = v;
			this.left = left;
			this.right = right;
		}
	}

	static class MyDeque {
		Border[] inside;
		int first;
		int last;

		public MyDeque(int maxSize) {
			inside = new Border[maxSize];
			first = 0;
			last = 0;
		}

		public boolean isEmpty() {
			return first == last;
		}

		public Border getFirst() {
			return inside[first];
		}

		public Border getLast() {
			return inside[last - 1];
		}

		public void removeFirst() {
			++first;
		}

		public void removeLast() {
			--last;
		}

		public void addLast(Border x) {
			inside[last++] = x;
		}
	}

	private boolean isEmpty(Point[] p, int delta) {
		Border[] sides = new Border[p.length];
		for (int i = 0; i < p.length; ++i) {
			sides[i] = new Border(p[i], p[(i + delta + 1) % p.length].subtract(p[i]).normalize(), -Double.MAX_VALUE, Double.MAX_VALUE);
		}

		MyDeque borders = new MyDeque(sides.length + 10);
		for (Border side : sides) {
			if (borders.isEmpty()) {
				borders.addLast(side);
				continue;
			}
			double left = -Double.MIN_VALUE;
			while (true) {
				if (borders.isEmpty())
					return true;
				Border border = borders.getLast();
				if (border.v.crossProductSign(side.v) <= 0)
					return true;
				{
					double a = -side.v.y;
					double b = side.v.x;
					double c = -(a * side.start.x + b * side.start.y);
					double mx = -(a * border.start.x + b * border.start.y + c) / (a * border.v.x + b * border.v.y) ;
					border.right = Math.min(border.right, mx);
					if (border.right <= border.left + EPS) {
						borders.removeLast();
						continue;
					}
				}
				{
					double a = -border.v.y;
					double b = border.v.x;
					double c = -(a * border.start.x + b * border.start.y);
					left = -(a * side.start.x + b * side.start.y + c) / (a * side.v.x + b * side.v.y);
				}
				break;
			}
			double right = Double.MAX_VALUE;
			{
				Border tmpBorder = borders.getFirst();
				if (side.v.crossProductSign(tmpBorder.v) > 0)
					while (true) {
						if (borders.isEmpty())
							return true;
						Border border = borders.getFirst();
						if (side.v.crossProductSign(border.v) <= 0)
							return true;
						{
							double a = -side.v.y;
							double b = side.v.x;
							double c = -(a * side.start.x + b * side.start.y);
							double mx = -(a * border.start.x + b * border.start.y + c) / (a * border.v.x + b * border.v.y);
							border.left = Math.max(border.left, mx);
							if (border.right < border.left + EPS) {
								borders.removeFirst();
								continue;
							}
						}
						{
							double a = -border.v.y;
							double b = border.v.x;
							double c = -(a * border.start.x + b * border.start.y);
							right = -(a * side.start.x + b * side.start.y + c) / (a * side.v.x + b * side.v.y);
						}
						break;
					}
			}
			if (!(right <= left + EPS)) {
				side.left = left;
				side.right = right;
				borders.addLast(side);
			}
		}
		return false;
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		jungle_petr solver = new jungle_petr();
		solver.run();
		solver.out.close();
	}

	public jungle_petr() {
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

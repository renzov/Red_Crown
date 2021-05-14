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
public class dome_petr {
	static class Point implements Comparable<Point> {
		double r;
		double h;
		double dist;

		public Point(InputReader in) {
			double x = in.readDouble();
			double y = in.readDouble();
			double z = in.readDouble();
			r = Math.hypot(x, y);
			h = z;
			dist = Math.hypot(r, h);
		}

		Point(double r, double h) {
			this.r = r;
			this.h = h;
			dist = Math.hypot(r, h);
		}

		public Point subtract(Point other) {
			return new Point(r - other.r, h - other.h); 
		}

		public int compareTo2(Point o) {
			double z = (h * o.r - r * o.h) / dist / o.dist;
			if (Math.abs(z) < 1e-12) {
				return 0;
			} else if (z > 0) {
				return -1;
			} else {
				return 1;
			}
		}

		public int compareTo(Point o) {
			double z = (h * o.r - r * o.h) / dist / o.dist;
			if (Math.abs(z) < 1e-12) {
				z = dist - o.dist;
				if (Math.abs(z) < 1e-12)
					return 0;
				else if (z > 0)
					return -1;
				else
					return 1;
			} else if (z > 0) {
				return -1;
			} else {
				return 1;
			}
		}

		@Override
		public String toString() {
			return "Point{" +
					"r=" + r +
					", h=" + h +
					", dist=" + dist +
					'}';
		}
	}

	public void run() {
		int n = in.readInt();
		List<Point> p = new ArrayList<Point>();
		double maxR = 0;
		double maxH = 0;
		for (int i = 0; i < n; ++i) {
			Point pp = new Point(in);
			maxR = Math.max(maxR, pp.r);
			maxH = Math.max(maxH, pp.h);
			if (pp.r > 0 && pp.h > 0)
				p.add(pp);
		}
		p.add(new Point(maxR, 0));
		p.add(new Point(0, maxH));
		Collections.sort(p);
		if (p.get(0).r != 0)
			throw new RuntimeException();
		if (p.get(p.size() - 1).h != 0)
			throw new RuntimeException();
		List<Point> hull = new ArrayList<Point>();
		for (Point x : p) {
			hull.add(x);
			while (hull.size() >= 3) {
				Point a = hull.get(hull.size() - 3);
				Point b = hull.get(hull.size() - 2);
				Point c = hull.get(hull.size() - 1);
				if (b.subtract(a).compareTo2(c.subtract(b)) >= 0) {
					hull.remove(hull.size() - 2);
				} else {
					break;
				}
			}
		}
		System.err.println(hull);
		double resV = 1e100;
		double resH = -1.0;
		double resR = -1.0;
		for (int i = 1; i + 1 < hull.size(); ++i) {
			Point a = hull.get(i - 1);
			Point b = hull.get(i);
			Point c = hull.get(i + 1);
			Point ba = b.subtract(a);
			double ha = b.h - (ba.h / ba.r) * b.r;
			double hb;
			if (Math.abs(b.r - c.r) / Math.max(b.r, c.r) < 1e-12) {
				hb = 1e100;
			} else {
				Point cb = c.subtract(b);
				hb = b.h - (cb.h / cb.r) * b.r;
			}
			double hBest = 3 * b.h;
			System.err.println(ha + " " + hb + " " + hBest);
			double curH;
			double curR;
			double curV;
			if (hBest < ha) {
				curH = ha;
			} else if (hBest > hb) {
				curH = hb;
			} else {
				curH = hBest;
			}
			curR = b.r * curH / (curH - b.h);
			curV = Math.PI * curR * curR * curH / 3.0;
			if (curV < resV) {
				resV = curV;
				resR = curR;
				resH = curH;
			}
		}
		out.println(resH + " " + resR);
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		dome_petr solver = new dome_petr();
		solver.run();
		solver.out.close();
	}

	public dome_petr() {
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

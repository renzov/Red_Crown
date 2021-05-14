import java.io.*;
import java.util.Locale;

/**
 * Solution for NEERC'2010 Problem J: Jungle Outpost
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class jungle_re {
	private static final int MAX_N = 50000;
	private static final int MAX_ABS = 1000000; // == 10^6

	private static final double EPS = 1e-6; // for distances
	private static final double SIN_EPS = 1e-14; // for sin/cos of angles

	public static void main(String[] args) throws Exception {
		new jungle_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static class Point {
		double x;
		double y;

		Point(Scanner in) {
			int x = in.nextInt();
			int y = in.nextInt();
			in.nextLine();
			assert Math.abs(x) <= MAX_ABS;
			assert Math.abs(y) <= MAX_ABS;
			this.x = x;
			this.y = y;
		}

		public Point(Point p) {
			x = p.x;
			y = p.y;
		}

		boolean sameAs(Point o) {
			return len(x - o.x, y - o.y) < EPS;
		}

		@Override
		public String toString() {
			return String.format(Locale.US, "(%.3f,%.3f)", x, y);
		}
	}

	int n;
	Point[] towers;
	
	void read() throws Exception {
		Scanner in = new Scanner(new File("jungle.in"));
		n = in.nextInt();
		in.nextLine();
		assert 3 <= n && n <= MAX_N;
		towers = new Point[n];
		for (int i = 0; i < n; i++)
			towers[i] = new Point(in);
		in.close();
	}

	static double det(double a11, double a12, double a21, double a22) {
		return a11 * a22 - a12 * a21;
	}

	static double sinangle(Point p11, Point p12, Point p21, Point p22) {
		double a11 = p12.x - p11.x;
		double a12 = p12.y - p11.y;
		double a21 = p22.x - p21.x;
		double a22 = p22.y - p21.y;
		return det(a11, a12, a21, a22) / len(a11, a12) / len(a21, a22);
	}

	static double len(double x, double y) {
		return Math.sqrt(x * x + y * y);
	}

	static class HalfPlane { // a * x + b * y >= c
		final Point p;
		final Point q;
		final double a;
		final double b;
		final double c;

		HalfPlane(Point p, Point q) {
			this.p = new Point(p);
			this.q = new Point(q);
			double a = q.y - p.y;
			double b = p.x - q.x;
			double d = len(a, b);
			assert d > EPS;
			a /= d;
			b /= d;
			double c = a * p.x + b * p.y;
			this.a = a;
			this.b = b;
			this.c = c;
		}

		boolean onLine(double x, double y) {
			return Math.abs(a * x + b * y - c) < EPS;
		}

		public boolean isEmpty() {
			return len(q.x - p.x, q.y - p.y) < EPS;
		}

		@Override
		public String toString() {
			return p + "->" + q;
		}
	}

	static class Edge {
		HalfPlane[] e;
		int l;
		int r;
		boolean cycle;

		Edge(int n) {
			e = new HalfPlane[2 * n];
		}

		void clear() {
			l = 0;
			r = 0;
			cycle = false;
		}

		boolean trim(HalfPlane v) {
			assert !v.isEmpty();
			if (l == r) {
				e[r++] = v;
				return false;
			}
			// rotate cycle appropriately if needed
			if (cycle) {
				// CCW u->v must be followed by CW u->v
				while (true) {
					HalfPlane u = e[l];
					double d = (v.a * (u.q.x - u.p.x) + v.b * (u.q.y - u.p.y)) / len(u.q.x - u.p.x, u.q.y - u.p.y) ;
					if (d > SIN_EPS)
						break; // if first is CCW - ok
					// otherwise rotate it to the end and repeat
					l++;
					e[r++] = u;
				}
			}
			// trim right
			int rt = findTrim(v, l, r, true);
			if (rt < 0) {
				assert cycle; // no intersection can be only in cycle mode
				return rt != -r; // if stopped not on the right side, means intersection is empty
			}
			r = rt;
			if (!v.isEmpty()) {
				e[r++] = v;
				int lt = findTrim(v, l, r - 1, false);
				if (cycle)
					assert lt >= 0; // must have intersected if that was already a cycle
				if (lt >= 0) {
					l = lt;
					if (v.isEmpty())
						r--;
				}
			}
			assert l <= r;
			if (l == r)
				return true; // it became 100% empty!
			cycle |= e[l].p.sameAs(e[r - 1].q);
			// cycle must have at least 3 sides
			return cycle && r - l < 3;
		}

		int findTrim(HalfPlane v, int l, int r, boolean rightFlag) {
			// finds right trimming point on [l, r) interval
			while (l < r) {
				int m = (l + r) / 2;
				HalfPlane u = e[m];
				double x0 = u.p.x;
				double y0 = u.p.y;
				double ux = u.q.x - x0;
				double uy = u.q.y - y0;
				double d = v.a * ux + v.b * uy;
				double len = len(ux, uy);
				if (rightFlag && d / len > -SIN_EPS) { // u->v has to be clockwise
					l = m + 1;
					continue;
				}
				if (!rightFlag && d / len < SIN_EPS) { // u->v has to be counter-clockwise
					r = m;
					continue;
				}
				double t = (v.c - v.a * x0 - v.b * y0) / d;
				if (t * len > len + EPS) {
					l = m + 1;
					continue;
				}
				if (t * len < -EPS) {
					r = m;
					continue;
				}
				double xc = x0 + t * ux;
				double yc = y0 + t * uy;
				assert u.onLine(xc, yc);
				assert v.onLine(xc, yc);
				Point upt = rightFlag ? u.q : u.p;
				upt.x = xc;
				upt.y = yc;
				Point vpt = rightFlag ? v.p : v.q;
				vpt.x = xc;
				vpt.y = yc;
				return rightFlag ?
						(u.isEmpty() ? m : m + 1) :
						(u.isEmpty() ? m + 1 : m);
			}
			// no intersection found
			return -r;
		}

	}

	int r;
	Edge edge;

	void solve() {
		// check 2 clockwiseness and "no 3 points on a line"
		for (int i = 0; i < n; i++) {
			Point a = towers[i];
			Point b = towers[(i + 1) % n];
			Point c = towers[(i + 2) % n];
			assert sinangle(a, b, b, c) < -SIN_EPS;
		}
		// binary search answer
		edge = new Edge(n);
		int l = 0; // definitely protected
		r = n; // becomes unprotected
		while (l < r - 1) {
			int m = (l + r) / 2;
			if (isEmptyProtection(m))
				r = m;
			else
				l = m;
		}
	}

	private boolean isEmptyProtection(int m) {
		if (m >= n - 2)
			return true;
		edge.clear();
		for (int i = 0; i < n; i++) {
			Point p = towers[i];
			Point q = towers[(i + m + 1) % n];
			if (edge.trim(new HalfPlane(p, q)))
				return true;
		}
		return false;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("jungle.out");
		out.println(r);
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a soulution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
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

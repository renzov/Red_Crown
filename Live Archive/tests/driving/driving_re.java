/*
    Solution for NEERC'2006 Problem D: Driving Directions
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.io.*;
import java.util.*;
import java.util.List;

public class driving_re {
	static final double EPS = 1e-8;

	public static void main(String[] args) throws Exception {
		new driving_re().go(args);
	}

	static class Point extends Point2D.Double {
		Point(double x, double y) {
			super(x, y);
		}

		public boolean equals(Object o) {
			if (!(o instanceof Point))
				return false;
			Point p = (Point) o;
			return Math.abs(x - p.x) < EPS && Math.abs(y - p.y) < EPS;
		}

		public int hashCode() {
			long a = (long)(x / (EPS * 10));
			long b = (long)(y / (EPS * 10));
			int ah = (int) (a >> 32);
			int al = (int) a;
			int bh = (int) (b >> 32);
			int bl = (int) b;
			return ah + 37 * (al + 37 * (bh + 37 * bl));
		}

		public String toString() {
			return new Formatter(Locale.US).format("(%.4f,%.4f)", x, y).toString();
		}
	}

	static final int[] DX = new int[]{0, -1, 0, 1};
	static final int[] DY = new int[]{-1, 0, 1, 0};

	int r;
	int n;
	Point a;
	Point b;
	Point[] c1;
	Point[] c2;
	Point[][] d;
	Point[][] e;

	Map<Point, Set<Point>> line = new HashMap<Point, Set<Point>>();
	Map<Point, Set<Point>> circ = new HashMap<Point, Set<Point>>();
	Map<Point, Set<Point>> corn = new HashMap<Point, Set<Point>>();

	SortedMap<Double, Set<Point>> d2p = new TreeMap<Double, Set<Point>>();
	Map<Point, Double> p2d = new HashMap<Point, Double>();
	Set<Point> done = new HashSet<Point>();

	void go(String[] args) throws Exception {
		Scanner in = new Scanner(new File(args.length > 0 ? args[0] : "driving.in"));

		r = in.nextInt();
		n = in.nextInt();
		in.nextLine();

		assert r >= 1 && r <= 100;
		assert n >= 0 && n <= 30;

		int xa = in.nextInt();
		int ya = in.nextInt();
		int xb = in.nextInt();
		int yb = in.nextInt();
		in.nextLine();

		assert good(xa) && good(ya) && good(xb) && good(yb);

		a = new Point(xa, ya);
		b = new Point(xb, yb);

		c1 = new Point[n];
		c2 = new Point[n];
		d = new Point[n][4];
		e = new Point[n][8];

		for (int i = 0; i < n; i++) {
			int x1 = in.nextInt();
			int y1 = in.nextInt();
			int x2 = in.nextInt();
			int y2 = in.nextInt();
			in.nextLine();

			assert good(x1) && good(y1) && good(x2) && good(y2) && x1 < x2 && y1 < y2;

			c1[i] = new Point(x1, y1);
			c2[i] = new Point(x2, y2);
			d[i][0] = new Point(x1, y1);
			d[i][1] = new Point(x1, y2);
			d[i][2] = new Point(x2, y2);
			d[i][3] = new Point(x2, y1);
			for (int j = 0; j < 4; j++) {
				e[i][2 * j] = move(d[i][j], j);
				e[i][2 * j + 1] = move(d[i][j], (j + 1) % 4);
			}
		}

		assert isValid(a) && isValid(b);
		assert!selfIntersections() : "self intersections";
		in.close();

		build();
		double result = solve();

		//findPath();
		//show();

		PrintStream out = new PrintStream(new File("driving.out"));
		if (result < 0)
			out.println("no solution");
		else
			out.printf(Locale.US, "%.6f", result);
		out.close();
	}

	Point move(Point a, int j) {
		return new Point(a.x + DX[j] * r, a.y + DY[j] * r);
	}

	Point mid(Point a, Point b) {
		return new Point(mid(a.x, b.x), mid(a.y, b.y));
	}

	double mid(double a, double b) {
		return (a + b) / 2;
	}

	void build() {
		checkLine(a, b);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 4; j++) {
				Point e1 = e[i][2 * j + 1];
				Point e2 = e[i][(2 * j + 2) % 8];
				if (checkLine(e1, e2)) {
					checkCorn(d[i][j], e1);
					checkCorn(d[i][(j + 1) % 4], e2);
				}
				checkTouch(a, d[i][j]);
				checkTouch(b, d[i][j]);
				for (int p = 0; p < n; p++)
					for (int q = 0; q < 4; q++) {
						checkCircInter(d[i][j], d[p][q]);
						checkOut(d[i][j], d[p][q]);
						Point m = mid(d[i][j], d[p][q]);
						if (!isValid(m))
							continue;
						checkTouch(m, d[i][j]);
						checkTouch(m, d[p][q]);
					}
			}

		//for (Map.Entry<Point,Set<Point>> e: corn.entrySet()) {
		//	System.out.println("CORN " + e.getKey());
		//	for (Point p: e.getValue())
		//		System.out.println(" -> " + p);
		//}

		for (Map.Entry<Point, Set<Point>> e : corn.entrySet()) {
			final Point c = e.getKey(); // center
			List<Point> list = new ArrayList<Point>(e.getValue());
			final Point d = list.get(0); // representative
			Collections.sort(list, new Comparator<Point>() {
				public int compare(Point a, Point b) {
					double z = getSin(c, a, d) - getSin(c, b, d);
					return z < -EPS ? -1 : z > EPS ? 1 : 0;
				}
			});
			Point p = null;
			for (Point q : list) {
				if (p != null) {
					Point cmid = cmid(c, p, q);
					if (isValid(cmid)) {
						getCirc(p).add(q);
						getCirc(q).add(p);
						//System.out.printf(Locale.US, "CIRC: %s - %s : %.6f center %s%n", p, q, cdist(p, q), cmid);
					}
				}
				p = q;
			}
		}
	}

	void putPointDist(Point a, Double d) {
		p2d.put(a, d);
		Set<Point> ps = d2p.get(d);
		if (ps == null)
			d2p.put(d, ps = new HashSet<Point>());
		ps.add(a);
	}

	void removeD2P(Point a, Double d) {
		Set<Point> ps = d2p.get(d);
		if (ps != null) {
			ps.remove(a);
			if (ps.isEmpty())
				d2p.remove(d);
		}
	}

	void adjust(Point a, double dist) {
		if (done.contains(a))
			return;
		Double d0 = p2d.get(a);
		if (d0 == null || dist < d0) {
			if (d0 != null)
				removeD2P(a, d0);
			putPointDist(a, dist);
		}
	}

	double solve() {
		putPointDist(a, 0.0);
		while (!done.contains(b) && !d2p.isEmpty()) {
			Double dmin = d2p.firstKey();
			Set<Point> ps = d2p.get(dmin);
			Point p = ps.iterator().next();
			ps.remove(p);
			if (ps.isEmpty())
				d2p.remove(dmin);
			done.add(p);
			Set<Point> lines = line.get(p);
			if (lines != null)
				for (Point q : lines)
					adjust(q, dmin + dist(p, q));
			Set<Point> circs = circ.get(p);
			if (circs != null)
				for (Point q : circs)
					adjust(q, dmin + cdist(p, q));
		}
		return done.contains(b) ? p2d.get(b) : -1;
	}

	double getSin(Point a, Point b, Point c) {
		double db = dist(a, b);
		double dc = dist(a, c);
		if (Math.abs(db) < 0 || Math.abs(dc) < 0)
			return 0;
		return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) / db / dc;
	}

	Point cmid(Point c, Point a, Point b) {
		double vx = a.x + b.x - 2 * c.x;
		double vy = a.y + b.y - 2 * c.y;
		double vmul = r / len(vx, vy);
		vx *= vmul;
		vy *= vmul;
		return new Point(c.x + vx, c.y + vy);
	}

	void checkCircInter(Point a, Point b) {
		double d = dist(a, b);
		if (d < EPS || d > 2 * r + EPS)
			return;
		Point m = mid(a, b);
		if (d > 2 * r - EPS) {
			if (isValid(m)) {
				checkCorn(a, m);
				checkCorn(b, m);
			}
			return;
		}
		double nx = a.y - b.y;
		double ny = b.x - a.x;
		double mul = Math.sqrt(sqr(r) - sqr(d / 2)) / d;
		nx *= mul;
		ny *= mul;
		Point p = new Point(m.x + nx, m.y + ny);
		Point q = new Point(m.x - nx, m.y - ny);
		if (!isValid(p) || !isValid(q))
			return;
		//System.out.printf("INTER: %s - %s ==> %s, %s%n", a, b, p, q);
		checkCorn(a, p);
		checkCorn(a, q);
		checkCorn(b, p);
		checkCorn(b, q);
	}

	void checkOut(Point a, Point b) {
		double nx = a.y - b.y;
		double ny = b.x - a.x;
		double nlen = len(nx, ny);
		if (Math.abs(nlen) < EPS)
			return;
		nx /= nlen;
		ny /= nlen;
		nx *= r;
		ny *= r;
		Point a1 = new Point(a.x + nx, a.y + ny);
		Point a2 = new Point(a.x - nx, a.y - ny);
		Point b1 = new Point(b.x + nx, b.y + ny);
		Point b2 = new Point(b.x - nx, b.y - ny);
		if (checkLine(a1, b1)) {
			checkCorn(a, a1);
			checkCorn(b, b1);
		}
		if (checkLine(a2, b2)) {
			checkCorn(a, a2);
			checkCorn(b, b2);
		}
	}

	void checkTouch(Point a, Point c) {
		double d = dist(a, c);
		if (d < r - EPS)
			return;
		if (d < r + EPS) {
			checkCorn(c, a);
			return;
		}
		double sina = r / d;
		double d1 = r * sina;
		double vx = a.x - c.x;
		double vy = a.y - c.y;
		double vlen = len(vx, vy);
		vx /= vlen;
		vy /= vlen;
		double x0 = c.x + vx * d1;
		double y0 = c.y + vy * d1;
		double nx = -vy;
		double ny = vx;
		double n = Math.sqrt(sqr(r) - sqr(d1));
		Point p1 = new Point(x0 + n * nx, y0 + n * ny);
		Point p2 = new Point(x0 - n * nx, y0 - n * ny);
		if (checkLine(a, p1))
			checkCorn(c, p1);
		if (checkLine(a, p2))
			checkCorn(c, p2);
	}

	boolean checkLine(Point a, Point b) {
		if (!isValid(a) || !isValid(b))
			return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 4; j++) {
				Point d1 = d[i][j];
				Point d2 = d[i][(j + 1) % 4];
				if (intersect(a, b, d1, d2) || tooClose(a, b, d1))
					return false;
			}
		getLine(a).add(b);
		getLine(b).add(a);
		//System.out.printf(Locale.US, "LINE: %s - %s : %.6f%n", a, b, dist(a, b));
		return true;
	}

	void checkCorn(Point c, Point b) {
		if (!isValid(b)) // todo: get rid of this check? 
			return;
		getCorn(c).add(b);
	}

	Set<Point> get(Map<Point, Set<Point>> m, Point a) {
		Set<Point> res = m.get(a);
		if (res == null)
			m.put(a, res = new HashSet<Point>());
		return res;
	}


	Set<Point> getLine(Point a) {
		return get(line, a);
	}

	Set<Point> getCirc(Point a) {
		return get(circ, a);
	}

	Set<Point> getCorn(Point a) {
		return get(corn, a);
	}

	boolean isValid(Point a) {
		for (int i = 0; i < n; i++) {
			Point d1 = c1[i];
			Point d2 = c2[i];
			if (a.x <= d1.x - r + EPS|| a.x >= d2.x + r - EPS || a.y <= d1.y - r + EPS || a.y >= d2.y + r - EPS)
				continue;
			if (between(a.x, d1.x, d2.x) || between(a.y, d1.y, d2.y))
				return false;
			for (int j = 0; j < 4; j++)
				if (tooClose(a, d[i][j]))
					return false;
		}
		return true;
	}

	boolean intersect(Point a, Point b, Point c, Point d) {
		if (!intersect(a.x, b.x, c.x, d.x) || !intersect(a.y, b.y, c.y, d.y))
			return false;
		return samedir(a, c, b, d) && samedir(c, a, d, b);
	}

	boolean intersect(double a, double b, double c, double d) {
		return between(a, c, d) || between(b, c, d) || between(c, a, b) || between(d, a, b);
	}

	boolean between(double a, double b, double c) {
		if (b > c) {
			double t = b;
			b = c;
			c = t;
		}
		return a > b - EPS && a < c + EPS;
	}

	boolean between(Point a, Point b, Point c) {
		return between(a.x, b.x, c.x) && between(a.y, b.y, c.y);
	}

	boolean samedir(Point a, Point b, Point c, Point d) {
		return dir(a, b, c) * dir(a, c, d) >= 0;
	}

	int dir(Point a, Point b, Point c) {
		double d = getSin(a, b, c);
		return d < -EPS ? -1 : d > EPS ? 1 : 0;
	}

	boolean tooClose(Point a, Point b, Point c) {
		return dist(a, b, c) < r - EPS && between(land(a, b, c), a, b);
	}

	boolean tooClose(Point a, Point b) {
		return dist(a, b) < r - EPS;
	}

	double cdist(Point a, Point b) {
		double d = dist(a, b);
		double cosa = 1 - sqr(d) / (2 * sqr(r));
		return Math.acos(cosa) * r;
	}

	double dist(Point a, Point b, Point c) {
		return dist(land(a, b, c), c);
	}

	Point land(Point a, Point b, Point c) {
		double u = a.y - b.y;
		double v = b.x - a.x;
		double len = len(u, v);
		u /= len;
		v /= len;
		double w = u * a.x + v * a.y;
		double d = w - c.x * u - c.y * v;
		return new Point(c.x + d * u, c.y + d * v);
	}

	double dist(Point a, Point b) {
		return dist(a.x, a.y, b.x, b.y);
	}

	double dist(double x1, double y1, double x2, double y2) {
		return len(x1 - x2, y1 - y2);
	}

	double len(double x, double y) {
		return Math.sqrt(sqr(x) + sqr(y));
	}

	double sqr(double v) {
		return v * v;
	}

	//----------------- just for debug ------------------

	ArrayList<Point> path = new ArrayList<Point>();

	void findPath() {
		if (!done.contains(b))
			return;
		Point q = b;
		while (a != null && !q.equals(a)) {
			path.add(q);
			double qdist = p2d.get(q);
			Point prev = null;
			String type = "N/A";
		findprev:
			{
				for (Map.Entry<Point, Set<Point>> e : line.entrySet())
					if (e.getValue().contains(q)) {
						Point p = e.getKey();
						Double pdist = p2d.get(p);
						double dpq = dist(p, q);
						if (pdist != null && dpq > EPS && Math.abs(qdist - pdist - dpq) < EPS) {
							prev = p;
							type = "LINE";
							break findprev;
						}
					}
				for (Map.Entry<Point,Set<Point>> e : circ.entrySet())
					if (e.getValue().contains(q)) {
						Point p = e.getKey();
						Double d0 = p2d.get(p);
						double dpq = cdist(p, q);
						if (d0 != null && dpq > EPS && Math.abs(qdist - d0 - dpq) < EPS) {
							prev = p;
							type = "CIRC";
							break findprev;
						}
					}
			}
			System.out.printf(Locale.US, "PATH: %s -> %s (%s) dist=%.6f%n", q, prev, type, p2d.get(prev));
			q = prev;
		}
		path.add(a);
	}

	double minx = 1000;
	double maxx = -1000;
	double miny = 1000;
	double maxy = -1000;

	void updateMM(Point a) {
		minx = Math.min(minx, a.x);
		maxx = Math.max(maxx, a.x);
		miny = Math.min(miny, a.y);
		maxy = Math.max(maxy, a.y);
	}

	void show() {
		updateMM(a);
		updateMM(b);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 8; j++) {
				updateMM(e[i][j]);
			}
		}
		double dx = (maxx - minx) / 10;
		double dy = (maxy - miny) / 10;
		minx -= dx;
		maxx += dx;
		miny -= dy;
		maxy += dy;

		JComponent canvas = new JComponent() {
			protected void paintComponent(Graphics g) {
				Graphics2D g2d = (Graphics2D)g;
				double sx = getWidth() / (maxx - minx);
				double sy = getHeight() / (maxy - miny);
				double s = Math.min(sx, sy);
				g2d.scale(s, -s);
				g2d.translate(-minx, -maxy);
				float pixel = (float)(1 / s);
				BasicStroke solid = new BasicStroke(pixel);
				BasicStroke solid3 = new BasicStroke(3 * pixel);
				BasicStroke dash = new BasicStroke(pixel, BasicStroke.CAP_SQUARE, BasicStroke.JOIN_MITER, 10.0f, new float[] {5 * pixel, 5 * pixel}, 0.0f);
				for (int i = 0; i < n; i++) {
					double x = c1[i].x;
					double y = c1[i].y;
					double w = c2[i].x - x;
					double h = c2[i].y - y;
					g2d.setStroke(solid);
					g2d.draw(new Rectangle2D.Double(x, y, w, h));
					g2d.setStroke(dash);
					g2d.draw(new RoundRectangle2D.Double(x - r, y - r, w + 2*r, h + 2*r, 2*r, 2*r));
				}
				g2d.setStroke(solid3);
				g2d.draw(new Ellipse2D.Double(a.x - pixel, a.y - pixel, 2*pixel, 2*pixel));
				g2d.draw(new Ellipse2D.Double(b.x - pixel, b.y - pixel, 2*pixel, 2*pixel));
				Point a = null;
				for (Point b: path) {
					if (a != null)
						g2d.draw(new Line2D.Double(a, b));
					a = b;
				}
			}
		};

		JFrame frame = new JFrame("Driving Directions");
		frame.getContentPane().add(canvas);
		Rectangle bounds = frame.getGraphicsConfiguration().getBounds();
		frame.setSize(new Dimension(bounds.width / 2, bounds.height / 2));
		frame.setLocationByPlatform(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}


	//----------------- just for validation ------------------

	boolean good(int x) {
		return x >= -1000 && x <= 1000;
	}

	boolean selfIntersections() {
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = 0; k < 4; k++)
					if (inside(d[i][k], j) || inside(d[j][k], i))
						return true;
			}
		}
		return false;
	}

	boolean inside(Point a, int i) {
		Point d1 = c1[i];
		Point d2 = c2[i];
		return between(a.x, d1.x, d2.x) && between(a.y, d1.y, d2.y);
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could added to a soulution source
	 * without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public static class Scanner {
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


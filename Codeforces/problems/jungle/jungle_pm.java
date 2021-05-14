import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class jungle_pm implements Runnable {

	private static final double EPS = 1e-15;

	private void solve() throws IOException {
		int n = nextInt();
		Vector[] p = new Vector[n];
		for (int i = 0; i < n; i++) {
			p[i] = new Vector(nextInt(), nextInt());
		}

		int low = 0;
		int high = (n - 1) / 2;
		while (high > low + 1) {
			int k = (high + low) / 2;
			if (canPlace(n, p, k)) {
				low = k;
			} else {
				high = k;
			}
		}
		out.println(high);
	}

	private boolean canPlace(int n, Vector[] p, int k) {
		List<Vector> path = new ArrayList<Vector>();
		path.add(p[0]);
		path.add(p[(k + 1) % n]);
		for (int i = 1; i < n; i++) {
			Vector a = p[i];
			Vector b = p[(i + k + 1) % n];
			Line l = a.lineTo(b);
			int side = l.side(p[(i + 1) % n]);
			while (path.size() > 1) {
				Vector c = path.get(path.size() - 2);
				Vector d = path.get(path.size() - 1);
				if (l.side(c) == -side) {
					myAssert(l.side(d) == side);
					Vector u = c.lineTo(d).intersect(l);
					path.set(path.size() - 1, u);
					path.add(b);
					break;
				} else {
					path.remove(path.size() - 1);
				}
			}
			if (path.size() == 1) {
				return false;
			}
		}
		return true;
	}

	private void myAssert(boolean b) {
		if (!b) throw new RuntimeException("Assertion fault");
	}

	class Vector {
		final double x, y;

		Vector(double x, double y) {
			this.x = x;
			this.y = y;
		}

		Vector add(Vector v) {
			return new Vector(x + v.x, y + v.y);
		}

		Vector subtract(Vector v) {
			return new Vector(x - v.x, y - v.y);
		}

		Line line() {
			return new Line(y, -x, 0);
		}

		Line lineTo(Vector v) {
			return ((v.subtract(this)).line()).parallel(v);
		}

		@Override
		public String toString() {
			return "("+ x + ", " + y + ")";
		}
	}

	class Line {
		final double a, b, c;

		Line(double a, double b, double c) {
			this.a = a;
			this.b = b;
			this.c = c;
		}

		Line parallel(Vector v) {
			return new Line(a, b, a * v.x + b * v.y);
		}

		Vector intersect(Line l) {
			double 	d = a *	l.b - b * l.a;
			if (Math.abs(d) < EPS) throw new RuntimeException("Lines are parallel");
			double dx = c * l.b - b * l.c;
			double dy = a * l.c - c * l.a;
			return new Vector(dx / d, dy / d);
		}

		int side(Vector v) {
			double d = a * v.x + b * v.y - c;
			if (d < -EPS) {
				return -1;
			} else if (d > EPS) {
				return 1;
			} else {
				return 0;
			}
		}
	}


	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;

	String next() throws IOException {
		while (st == null || !st.hasMoreTokens()) {
			st = new StringTokenizer(br.readLine());
		}
		return st.nextToken();
	}

	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	public static void main(String[] args) {
		new jungle_pm().run();
	}

	public void run()  {
		try {
			br = new BufferedReader(new FileReader("jungle.in"));
			out = new PrintWriter("jungle.out");
			solve();
			br.close();
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}

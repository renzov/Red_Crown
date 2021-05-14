import com.vividsolutions.jts.geom.*;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class jungle_pm_jts implements Runnable {

	GeometryFactory gf = new GeometryFactory(new PrecisionModel(1e9));

	private void solve() throws IOException {
		int n = nextInt();
		Coordinate[] p = new Coordinate[n + 1];
		for (int i = 0; i < n; i++) {
			p[i] = new Coordinate(nextInt(), nextInt());
		}
		p[n] = p[0];

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

	private boolean canPlace(int n, Coordinate[] p, int k) {
		Geometry pp = null;
		for (int i = 0; i < n; i++) {
			Coordinate[] q = new Coordinate[7];
			double x1 = p[i].x;
			double y1 = p[i].y;
			double x2 = p[(i + k + 1) % n].x;
			double y2 = p[(i + k + 1) % n].y;
			q[0] = new Coordinate(x1, y1);
			q[1] = new Coordinate(x2, y2);
			double dx = x2 - x1;
			double dy = y2 - y1;
			double d = Math.hypot(dx, dy);
			dx /= d;
			dy /= d;
			double z = 3e8;
			q[2] = new Coordinate(x1 + z * dx, y1 + z * dy);
			q[3] = new Coordinate(x1 + z * (dx + dy), y1 + z * (dy - dx));
			q[4] = new Coordinate(x1 + z * (-dx + dy), y1 + z * (-dy - dx));
			q[5] = new Coordinate(x1 - z * dx, y1 - z * dy);
			q[6] = q[0];
			Polygon f = gf.createPolygon(
					gf.createLinearRing(q), null
			);
			if (pp == null) {
				pp = f;
			} else {
				pp = pp.intersection(f);
			}
		}
		if (pp.getCoordinates().length == 0) return false;
		return true;
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
		new jungle_pm_jts().run();
	}

	public void run() {
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
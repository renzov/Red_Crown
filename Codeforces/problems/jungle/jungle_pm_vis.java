import com.vividsolutions.jts.geom.*;
import com.vividsolutions.jts.geom.Polygon;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class jungle_pm_vis {

	GeometryFactory gf = new GeometryFactory(new PrecisionModel(1e9));
	private static final int SIZE = 1000;
	BufferedImage image;
	private double minx;
	private double maxx;
	private double miny;
	private double maxy;
	private double w;
	private double cx;
	private double cy;

	private void solve() throws IOException {
		int n = nextInt();
		Coordinate[] p = new Coordinate[n + 1];
		for (int i = 0; i < n; i++) {
			p[i] = new Coordinate(nextInt(), nextInt());
		}
		p[n] = p[0];
		final List<Geometry> res = new ArrayList<Geometry>();
		Geometry init = gf.createPolygon(gf.createLinearRing(p), null);
		res.add(init);
		int step = Math.max(n / 5, 1);
		for (int k = step; k < n / 2; k += step) {
			try {
				Geometry pp = null;
				int m = n - k;
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
				if (pp.getCoordinates().length < 3) break;
				res.add(pp);
				System.out.println(k);
			} catch (Exception e) {
				e.printStackTrace();
				//break;
			}
		}

		System.out.println(n + " " + res.size());

		minx = 1e100;
		maxx = -1e100;
		miny = 1e100;
		maxy = -1e100;
		for (Coordinate coordinate : res.get(0).getCoordinates()) {
			minx = Math.min(minx, coordinate.x);
			maxx = Math.max(maxx, coordinate.x);
			miny = Math.min(miny, coordinate.y);
			maxy = Math.max(maxy, coordinate.y);
		}
		w = Math.max(maxx - minx, maxy - miny);
		cx = (minx + maxx) / 2;
		cy = (miny + maxy) / 2;
		w = w * 1.1;

		minx = cx - w / 2;
		maxx = cx + w / 2;
		miny = cy - w / 2;
		maxy = cy + w / 2;

		image = drawPolygons(res);
		final JPanel panel = new JPanel() {
			@Override
			public void paint(Graphics g) {
				g.drawImage(image, 0, 0, null);
			}
		};

		JFrame mainFrame = new JFrame("Jungle Outpost Visualizer");
		mainFrame.setLayout(new BorderLayout());
		mainFrame.getContentPane().add(panel);
		mainFrame.setSize(SIZE + 10, SIZE + 25);
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent mouseEvent) {
				int x = mouseEvent.getX();
				int y = mouseEvent.getY();
				if (mouseEvent.getButton() == MouseEvent.BUTTON1) {
					cx = minx + (x * w / SIZE);
					cy = miny + (y * w / SIZE);
					w /= 2;
					minx = cx - w / 2;
					miny = cy - w / 2;
				} else {
					cx = minx + (x * w / SIZE);
					cy = miny + (y * w / SIZE);
					w *= 2;
					minx = cx - w / 2;
					miny = cy - w / 2;
				}
				image = drawPolygons(res);
				panel.repaint();
			}
		});
		mainFrame.setVisible(true);

	}

	private BufferedImage drawPolygons(List<Geometry> polygons) {

		BufferedImage bi = new BufferedImage(SIZE, SIZE, BufferedImage.TYPE_INT_RGB);
		Graphics2D g = (Graphics2D) bi.getGraphics();

		g.fill(new Rectangle(0, 0, SIZE, SIZE));
		g.setColor(Color.black);

		int z = 2;
		for (Geometry polygon : polygons) {
			Coordinate[] p = polygon.getCoordinates();
			for (int i = 0; i < p.length - 1; i++) {
				g.drawOval(getX(p[i].x) - z, getY(p[i].y) - z, 2 * z, 2 * z);
				g.drawLine(
						getX(p[i].x),
						getY(p[i].y),
						getX(p[i + 1].x),
						getY(p[i + 1].y)
				);
			}

		}

		return bi;
	}

	private int getX(double x) {
		return (int) (SIZE * (x - minx) / w);
	}

	private int getY(double y) {
		return (int) (SIZE * (y - miny) / w);
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

	public static void main(String[] args) throws IOException {
		{
			InputStream in = new FileInputStream("tests/63");
			OutputStream out = new FileOutputStream("jungle.in");
			byte[] buf = new byte[100000];
			int c;
			while ((c = in.read(buf)) > 0) {
				out.write(buf, 0, c);
			}
			in.close();
			out.close();
		}
		try {
			new jungle_pm_vis().run();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	private void run() throws IOException {
		br = new BufferedReader(new FileReader("jungle.in"));
		out = new PrintWriter("jungle.out");
		solve();
	}

}
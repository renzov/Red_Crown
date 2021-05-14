import com.vividsolutions.jts.geom.Coordinate;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

/**
 * To be documented
 * Date: Nov 9, 2010
 * Time: 8:16:10 PM
 *
 * @author Pavel Mavrin
 */
public class StressTest {

	Runnable solution1 = new jungle_pm();
	Runnable solution2 = new jungle_pm_jts();

	public static void main(String[] args) throws FileNotFoundException {
		new StressTest().run();
	}

	void run() throws FileNotFoundException {
		int n = 20;
		int r = 1000;
		double min = 1e100;
		Random random = new Random(1324645L);
		while (true) {
			Coordinate[] p = new Coordinate[n + 1];
			double[] a = new double[n];
			for (int i = 0; i < n; i++) {
				a[i] = (Math.PI * 2 / 3) * random.nextInt(3) + Math.PI / 6 * random.nextDouble();
//				a[i] = (Math.PI * 2 / 3) * random.nextInt(3) + Math.PI * 2 / 3 * random.nextDouble();
			}
			Arrays.sort(a);
			int[] x = new int[n];
			int[] y = new int[n];
			for (int i = 0; i < n; i++) {
				x[i] = (int) (r * Math.cos(a[i]));
				y[i] = -(int) (r * Math.sin(a[i]));
			}
			for (int i = 0; i < n; i++) {
				p[i] = new Coordinate(x[i], y[i]);
			}
			p[n] = p[0];
			boolean ok = true;
			for (int i = 0; i < n; i++) {
				int j = (i + 1) % n;
				int k = (i + 2) % n;
				if ((x[j] - x[i]) * (y[k] - y[i]) >= (y[j] - y[i]) * (x[k] - x[i])) {
					ok = false;
				}
			}
			//System.out.print(".");
			if (!ok) continue;
			//System.out.println("!");
			PrintWriter out = new PrintWriter("jungle.in");
			out.println(n);
			for (int i = 0; i < n; i++) {
				out.println(x[i] + " " + y[i]);
			}
			out.close();

			try {
				solution1.run();
				Scanner scanner = new Scanner(new File("jungle.out"));
				int ans1 = scanner.nextInt();
				scanner.close();

				System.out.print(ans1 + " ");

				solution2.run();
				scanner = new Scanner(new File("jungle.out"));
				int ans2 = scanner.nextInt();
				scanner.close();

				System.out.println(ans2);
				if (ans1 != ans2) {
					break;
				}
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("!!!");
				break;
			}

		}
	}

}

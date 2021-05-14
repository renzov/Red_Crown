import com.vividsolutions.jts.geom.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Tests {

    public static final int MIN_X = -1000000;
    public static final int MAX_X = 1000000;
    public static final int MAX_N = 50000;

    int testNumber = 0;
    private static final double EPS = 1e-15;

    PrintWriter comments;

    void printTest(Test t, String comment) throws FileNotFoundException {
        myAssert(isValidTest(t));
        int n = t.x.length;
        myAssert(n >= 3 && n <= MAX_N);
        for (int i = 0; i < n; i++) {
            int x = t.x[i];
            int y = t.y[i];
            assert (x >= MIN_X && x <= MAX_X);
            assert (y >= MIN_X && y <= MAX_X);
        }

        testNumber++;
        System.out.println("Print test " + testNumber);
        comments.println("Test " + testNumber + ": " + comment);
        PrintWriter out = new PrintWriter("tests/" + (testNumber / 10) + (testNumber % 10));
        out.println(n);
        for (int i = 0; i < n; i++) {
            int x = t.x[i];
            int y = t.y[i];
            out.println(x + " " + y);
        }
        out.close();

    }

    private void myAssert(boolean b) {
        if (!b) throw new RuntimeException("Assertion fault");
    }


    public static void main(String[] args) {
        try {
            new Tests().run();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    Random random;

    private void run() throws IOException {
        random = new Random(1324645L);

        new File("tests").mkdir();
        comments = new PrintWriter("tests/tests.lst");

        {
            printTest(new Test(new int[]{0, 50, 60}, new int[]{0, 50, 10}), "First sample test");
        }
        {
            printTest(new Test(new int[]{0, 0, 10, 20, 25}, new int[]{0, 10, 20, 10, 0}), "Second sample test");
        }


        for (int i = 0; i < 10; i++) {
            int n = i + 3;
            int r = 10 + random.nextInt(10);
            printTest(buildSmallValidTest(n, r), n + " vertex random test");
        }
        for (int i = 0; i < 10; i++) {
            int n = 20 + random.nextInt(50);
            int r = 1000 + random.nextInt(1000);
            printTest(buildValidTest(n, r), "Small random test");
        }

        for (int i = 0; i < 10; i++) {
            int n = 1000 - random.nextInt(100);
            int r = MAX_X - random.nextInt(MAX_X / 10);
            printTest(buildValidTest(n, r), "Big random test");
        }

        for (int i = 0; i < 10; i++) {
            int n = 10000 - random.nextInt(1000);
            int r = MAX_X - random.nextInt(MAX_X / 10);
            printTest(buildValidTest(n, r), "Huge random test");
        }

        for (int i = 0; i < 5; i++) {
            int n = MAX_N - random.nextInt(MAX_N / 10);
            int r = MAX_X - random.nextInt(MAX_X / 10);
            printTest(buildValidTest(n, r), "Nearly maximal random test");
        }

        for (int i = 0; i < 5; i++) {
            int n = MAX_N;
            int r = MAX_X;
            printTest(buildValidTest(n, r), "Maximal random test");
        }

        for (int i = 0; i < 10; i++) {
            int n = MAX_N - random.nextInt(MAX_N / 100);
            int r = MAX_X - random.nextInt(MAX_X / 100);
            Test t = buildValidTest(n, r);
            int k = n / 2;
            for (int j = k; j < n; j++) {
                t.x[j] = -t.x[j - k];
                t.y[j] = -t.y[j - k];
            }
            printTest(buildValidTest(n, r), "Nearly maximal symmetric test");
        }

        {
            int s = 0;
            int n = 1;
            while (s + n + (n + 1) < MAX_X) {
                s += (n + 1);
                n++;
            }
            n--;
            int[] x = new int[n * 8];
            int[] y = new int[n * 8];
            Test t = new Test(x, y);
            x[0] = 0;
            y[0] = s + n;
            int m = 1;
            for (int i = n; i > 0; i--) {
                x[m] = x[m - 1] + (i + 1);
                y[m] = y[m - 1] - 1;
                m++;
            }
            for (int i = 1; i <= n; i++) {
                x[m] = x[m - 1] + 1;
                y[m] = y[m - 1] - (i + 1);
                m++;
            }
            for (int i = 2 * n; i < 8 * n; i++) {
                x[i] = y[i - 2 * n];
                y[i] = -x[i - 2 * n];
            }
            t.randomShift();
            printTest(t, "Large square built of parabola parts");
        }
        {
            int s = 0;
            int n = 1;
            while (s + n + n < MAX_X) {
                s += n;
                n++;
            }
            n--;
            if (n % 2 == 1) n--;
            int n2 = n / 2 - 1;
            int s2 = 0;
            for (int i = 1; i <= n2; i++) {
                s2 += i;
            }
            int[] x = new int[n * 3];
            int[] y = new int[n * 3];
            Test t = new Test(x, y);
            x[0] = 0;
            y[0] = MAX_X;
            int m = 1;
            for (int i = n; i > 0; i--) {
                x[m] = x[m - 1] + i;
                y[m] = y[m - 1] - 1;
                m++;
            }
            x[m] = s2;
            y[m] = -MAX_X + n2;
            m++;
            for (int i = 1; i <= n2; i++) {
                x[m] = x[m - 1] - i;
                y[m] = y[m - 1] - 1;
                m++;
            }
            m--;
            for (int i = m; i < n * 3; i++) {
                x[i] = -x[m - (i - m)];
                y[i] = y[m - (i - m)];
            }
            t.randomShift();
            printTest(t, "Large triangle-like test built of parabola parts");
        }
        {
            int s = 0;
            int n = 1;
            while (s + n < MAX_X) {
                s += n;
                n++;
            }
            n--;
            int[] x = new int[n * 4];
            int[] y = new int[n * 4];
            Test t = new Test(x, y);
            x[0] = 0;
            y[0] = n;
            int m = 1;
            for (int i = n; i > 0; i--) {
                x[m] = x[m - 1] + i;
                y[m] = y[m - 1] - 1;
                m++;
            }
            for (int i = 1; i <= n; i++) {
                x[m] = x[m - 1] - i;
                y[m] = y[m - 1] - 1;
                m++;
            }
            for (int i = 2 * n; i < 4 * n; i++) {
                x[i] = -x[i - 2 * n];
                y[i] = -y[i - 2 * n];
            }
            t.randomShift();
            printTest(t, "Large strip built of parabola parts");
        }
        {
            int s = 0;
            int n = 1;
            while (s + n < MAX_X) {
                s += n;
                n++;
            }
            n--;
            int[] x = new int[n * 2 + 1];
            int[] y = new int[n * 2 + 1];
            Test t = new Test(x, y);
            x[0] = 0;
            y[0] = n;
            int m = 1;
            for (int i = n; i > 0; i--) {
                x[m] = x[m - 1] + i;
                y[m] = y[m - 1] - 1;
                m++;
            }
            for (int i = 1; i <= n; i++) {
                x[m] = x[m - 1] - i;
                y[m] = y[m - 1] - 1;
                m++;
            }
            t.randomShift();
            printTest(t, "Half of large strip built of parabola parts");
        }

        {
            int n = 1000;
            int r = MAX_X;
            printTest(buildRombicLikeTest(n, r, 1000, r, r), "Big Triangle-like test");
        }
        {
            int n = 1000;
            int r = MAX_X;
            printTest(buildRombicLikeTest(n, r, 1000, 1000, r), "Big Triangle-like test");
        }

        for (int i = 0; i < 5; i++) {
            int n = MAX_N;
            int r = MAX_X;
            Test t = buildValidTest(n, r);
            t.randomShift();
            n /= 6;
            int[] x = new int[n * 3];
            int[] y = new int[n * 3];
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < n; k++) {
                    x[j * n + k] = t.x[j * 2 * n + k];
                    y[j * n + k] = t.y[j * 2 * n + k];
                }
            }
            t = new Test(x, y);
            t.randomShift();
            printTest(t, "Big test with small answer");
        }
        for (int i = 0; i < 5; i++) {
            int n = MAX_N;
            int r = MAX_X;
            Test t = buildValidTest(n, r);
            t.randomShift();

            int[] x = new int[n / 2];
            int[] y = new int[n / 2];
            int m = 0;
            for (int j = 0; j < n; j++) {
                double p = (Math.sin(Math.PI * 6 * j / n) + 1) / 2;
                if (m + (n - j) == (n / 2)) p = 2;
                if (random.nextDouble() < p) {
                    x[m] = t.x[j];
                    y[m] = t.y[j];
                    m++;
                }
                if (m == n / 2) {
                    break;
                }
            }
            t = new Test(x, y);
            t.randomShift();
            printTest(t, "Big test with small answer, vertices are not grouped");
        }

        FitnessFunction maximalArea = new FitnessFunction() {
            public double calc(Test t) {
                return getResult(t).place.getArea();
            }
        };
        FitnessFunction minimalArea = new FitnessFunction() {
            public double calc(Test t) {
                return -getResult(t).place.getArea();
            }
        };
        FitnessFunction maximalAnswer = new FitnessFunction() {
            public double calc(Test t) {
                return getResult(t).k;
            }
        };
        FitnessFunction minimalAnswer = new FitnessFunction() {
            public double calc(Test t) {
                return -getResult(t).k;
            }
        };

        printTest(
                findBestTest(
                        buildSmallValidTest(21, MAX_X),
                        10000,
                        maximalArea
                )
                , "Large spot test");
        printTest(
                findBestTest(
                        buildSmallValidTest(21, MAX_X),
                        10000,
                        minimalArea
                )
                , "Small spot test");

//		{
//			int n = 20;
//			printTest(findBestTest(n, new FitnessFunction() {
//				public double calc(Test t) {
//					return getResult(t).k;
//				}
//			}));
//		}

        comments.close();


    }

// Test optimization

    class Test {
        int[] x;
        int[] y;

        Test(int[] x, int[] y) {
            this.x = x;
            this.y = y;
        }

        void randomShift() {
            int n = x.length;
            int k = random.nextInt(n);
            int[] xx = new int[n];
            int[] yy = new int[n];
            for (int i = 0; i < n; i++) {
                xx[i] = x[(i + k) % n];
                yy[i] = y[(i + k) % n];
            }
            x = xx;
            y = yy;
        }
    }

    interface FitnessFunction {
        double calc(Test t);
    }

    private Test findBestTest(Test t, int iterations, FitnessFunction f) {
        double ff = f.calc(t);
        int n = t.x.length;
        double z = 0;
        for (int i = 0; i < n; i++) {
            z += Math.hypot(t.x[i] - t.x[(i + 1) % n], t.y[i] - t.y[(i + 1) % n]);
        }
        z /= n;
        int zz = (int) z;
        boolean p = false;
        int q = 0;
        for (int iteration = 0; iteration < iterations; iteration++) {
            if (q > 1000) {
                q = 0;
                zz /= 2;
                if (zz == 0) zz = 1;
            }
            q++;
            if (iteration % 1000 == 0) System.out.println(iteration + " of " + iterations);
            int u = random.nextInt(n);
            int dx, dy;
            do {
                dx = random.nextInt(2 * zz + 1) - zz;
                dy = random.nextInt(2 * zz + 1) - zz;
            } while (dx == 0 && dy == 0);
            t.x[(u + 2) % n] += dx;
            t.y[(u + 2) % n] += dy;
            if (t.x[(u + 2) % n] < MIN_X || t.x[(u + 2) % n] > MAX_X ||
                    t.y[(u + 2) % n] < MIN_X || t.y[(u + 2) % n] > MAX_X) {
                t.x[(u + 2) % n] -= dx;
                t.y[(u + 2) % n] -= dy;
                continue;
            }
            boolean ok = true;
            for (int e = 0; e < 3; e++) {
                int i = (u + e) % n;
                int j = (u + e + 1) % n;
                int k = (u + e + 2) % n;
                if (1l * (t.x[j] - t.x[i]) * (t.y[k] - t.y[i]) >= 1l * (t.y[j] - t.y[i]) * (t.x[k] - t.x[i])) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                double ff2 = f.calc(t);
                if (ff2 >= ff) {
                    if (ff2 > ff) {
//						System.out.println("!!" + ff2);
                        q = 0;
                    }
                    ff = ff2;
                } else {
                    t.x[(u + 2) % n] -= dx;
                    t.y[(u + 2) % n] -= dy;
                }
            } else {
                t.x[(u + 2) % n] -= dx;
                t.y[(u + 2) % n] -= dy;
            }
        }
        return t;
    }

    private Test buildSmallValidTest(int n, int r) {
        double min = 1e100;
        while (true) {
            double[] a = new double[n];
            for (int i = 0; i < n; i++) {
                a[i] = (Math.PI * 2) * random.nextDouble();
            }
            Arrays.sort(a);
            {
                double[] b = new double[n];
                int k = random.nextInt(n);
                for (int i = 0; i < n; i++) {
                    b[i] = a[(i + k) % n];
                }
                a = b;
            }
            int[] x = new int[n];
            int[] y = new int[n];
            for (int i = 0; i < n; i++) {
                x[i] = (int) (r * Math.cos(a[i]));
                y[i] = -(int) (r * Math.sin(a[i]));
            }
            Test t = new Test(x, y);
            if (isValidTest(t)) return t;
        }
    }

    private Test buildValidTest(int n, int r) {
        // Smart method. When there are not so much coordinates.
        Point[][] p = new Point[4][];
        int[] sx = new int[4];
        int[] sy = new int[4];
        int nn = n - 4;


        p[0] = new Point[nn / 4];
        nn -= nn / 4;
        p[1] = new Point[nn / 3];
        nn -= nn / 3;
        p[2] = new Point[nn / 2];
        nn -= nn / 2;
        p[3] = new Point[nn];

        for (int i = 0; i < 4; i++) {
            do {
                int d = (r / p[i].length) * 2;
                //boolean[][] z = new boolean[d + 1][d + 1];
                Set<Point> z = new HashSet<Point>();
                sx[i] = 0;
                sy[i] = 0;
                for (int j = 0; j < p[i].length; j++) {
                    while (true) {
                        int x = random.nextInt(d) + 1;
                        int y = random.nextInt(d) + 1;
                        int dd = gcd(x, y);
                        x /= dd;
                        y /= dd;
                        Point pp = new Point(x, y);
                        if (!z.contains(pp)) {
                            p[i][j] = pp;
                            z.add(pp);
                            break;
                        } else {
                            //System.out.println(z.size());
                            //System.out.print(".");
                        }
                    }
                    sx[i] += p[i][j].x;
                    sy[i] += p[i][j].y;
                }
            } while (false);//sx[i] >= MAX_X && sy[i] >= MAX_X);
            Arrays.sort(p[i]);
        }

        int a = 1;
        int b = 1;
        int c = 1;
        int d = 1;
        if (sy[0] + sy[1] > sy[2] + sy[3]) {
            c += sy[0] + sy[1] - sy[2] - sy[3];
        } else {
            a += sy[2] + sy[3] - sy[0] - sy[1];
        }

        if (sx[0] + sx[3] > sx[1] + sx[2]) {
            b += sx[0] + sx[3] - sx[1] - sx[2];
        } else {
            d += sx[1] + sx[2] - sx[0] - sx[3];
        }

        int[] x = new int[n];
        int[] y = new int[n];
        x[0] = 0;
        y[0] = MAX_X;
        int k = 1;
        for (int i = 0; i < p[0].length; i++) {
            x[k] = x[k - 1] + p[0][i].x;
            y[k] = y[k - 1] - p[0][i].y;
            k++;
        }
        x[k] = x[k - 1];
        y[k] = y[k - 1] - a;
        k++;
        for (int i = p[1].length - 1; i >= 0; i--) {
            x[k] = x[k - 1] - p[1][i].x;
            y[k] = y[k - 1] - p[1][i].y;
            k++;
        }
        x[k] = x[k - 1] - b;
        y[k] = y[k - 1];
        k++;
        for (int i = 0; i < p[2].length; i++) {
            x[k] = x[k - 1] - p[2][i].x;
            y[k] = y[k - 1] + p[2][i].y;
            k++;
        }
        x[k] = x[k - 1];
        y[k] = y[k - 1] + c;
        k++;
        for (int i = p[3].length - 1; i >= 0; i--) {
            x[k] = x[k - 1] + p[3][i].x;
            y[k] = y[k - 1] + p[3][i].y;
            k++;
        }

        return new Test(x, y);
    }

    private Test buildRombicLikeTest(int n, int rt, int rb, int rl, int rr) {
        //
        Point[][] p = new Point[4][];
        int[] sx = new int[4];
        int[] sy = new int[4];
        int nn = n - 4;

        double a1 = Math.hypot(rt, rr);
        double a2 = Math.hypot(rb, rr);
        double a3 = Math.hypot(rb, rl);
        double a4 = Math.hypot(rt, rl);

        int mm = Math.max((int) (nn * a1 / (a1 + a2 + a3 + a4)), 1);
        p[0] = new Point[mm];
        nn -= mm;
        mm = Math.max((int) (nn * a2 / (a2 + a3 + a4)), 1);
        p[1] = new Point[mm];
        nn -= mm;
        mm = Math.max((int) (nn * a3 / (a3 + a4)), 1);
        p[2] = new Point[mm];
        nn -= mm;
        p[3] = new Point[nn];

        int[] rx = new int[]{rr, rr, rl, rl};
        int[] ry = new int[]{rt, rb, rb, rt};

        for (int i = 0; i < 4; i++) {
            do {
                int dx = (rx[i] / p[i].length) * 2;
                int dy = (ry[i] / p[i].length) * 2;
                //boolean[][] z = new boolean[d + 1][d + 1];
                Set<Point> z = new HashSet<Point>();
                sx[i] = 0;
                sy[i] = 0;
                for (int j = 0; j < p[i].length; j++) {
                    while (true) {
                        int x = random.nextInt(dx) + 1;
                        int y = random.nextInt(dy) + 1;
                        int dd = gcd(x, y);
                        x /= dd;
                        y /= dd;
                        Point pp = new Point(x, y);
                        if (!z.contains(pp)) {
                            p[i][j] = pp;
                            z.add(pp);
                            break;
                        } else {
                            //System.out.println(z.size());
                            //System.out.print(".");
                        }
                    }
                    sx[i] += p[i][j].x;
                    sy[i] += p[i][j].y;
                }
            } while (false);//sx[i] >= MAX_X && sy[i] >= MAX_X);
            Arrays.sort(p[i]);
        }

        int a = 1;
        int b = 1;
        int c = 1;
        int d = 1;
        if (sy[0] + sy[1] > sy[2] + sy[3]) {
            c += sy[0] + sy[1] - sy[2] - sy[3];
        } else {
            a += sy[2] + sy[3] - sy[0] - sy[1];
        }

        if (sx[0] + sx[3] > sx[1] + sx[2]) {
            b += sx[0] + sx[3] - sx[1] - sx[2];
        } else {
            d += sx[1] + sx[2] - sx[0] - sx[3];
        }

        int[] x = new int[n];
        int[] y = new int[n];
        x[0] = 0;
        y[0] = MAX_X;
        int k = 1;
        for (int i = 0; i < p[0].length; i++) {
            x[k] = x[k - 1] + p[0][i].x;
            y[k] = y[k - 1] - p[0][i].y;
            k++;
        }
        x[k] = x[k - 1];
        y[k] = y[k - 1] - a;
        k++;
        for (int i = p[1].length - 1; i >= 0; i--) {
            x[k] = x[k - 1] - p[1][i].x;
            y[k] = y[k - 1] - p[1][i].y;
            k++;
        }
        x[k] = x[k - 1] - b;
        y[k] = y[k - 1];
        k++;
        for (int i = 0; i < p[2].length; i++) {
            x[k] = x[k - 1] - p[2][i].x;
            y[k] = y[k - 1] + p[2][i].y;
            k++;
        }
        x[k] = x[k - 1];
        y[k] = y[k - 1] + c;
        k++;
        for (int i = p[3].length - 1; i >= 0; i--) {
            x[k] = x[k - 1] + p[3][i].x;
            y[k] = y[k - 1] + p[3][i].y;
            k++;
        }

        return new Test(x, y);
    }

    private int gcd(int x, int y) {
        if (y == 0) return x;
        else return gcd(y, x % y);
    }

    class Point implements Comparable<Point> {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Point point = (Point) o;

            if (x != point.x) return false;
            if (y != point.y) return false;

            return true;
        }

        @Override
        public int hashCode() {
            int result = x;
            result = 31 * result + y;
            return result;
        }

        public int compareTo(Point point) {
            return Long.signum(1l * y * point.x - 1l * x * point.y);
        }
    }

    private boolean isValidTest(Test t) {
        int n = t.x.length;
        int[] x = t.x;
        int[] y = t.y;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int k = (i + 2) % n;
            if (1l * (x[j] - x[i]) * (y[k] - y[i]) >= 1l * (y[j] - y[i]) * (x[k] - x[i])) {
                return false;
            }
        }
        return true;
    }
// Solution

    GeometryFactory gf = new GeometryFactory(new PrecisionModel(1e9));

    class Result {
        int k;
        Geometry place;

        Result(int k, Geometry place) {
            this.k = k;
            this.place = place;
        }
    }

    private Result getResult(Test t) {
        int n = t.x.length;
        Coordinate[] p = new Coordinate[n + 1];
        for (int i = 0; i < n; i++) {
            p[i] = new Coordinate(t.x[i], t.y[i]);
        }
        p[n] = p[0];
        int low = 0;
        int high = (n - 1) / 2;
        while (high > low + 1) {
            int k = (high + low) / 2;
            if (place(n, p, k) != null) {
                low = k;
            } else {
                high = k;
            }
        }
        return new Result(high, place(n, p, high - 1));
    }

    private Geometry place(int n, Coordinate[] p, int k) {
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
            double z = MAX_X * 3;
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
        if (pp.getCoordinates().length == 0) return null;
        return pp;
    }


}
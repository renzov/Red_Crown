import java.io.*;
import java.util.*;

public class Tests {
    static int MAX_COORD = 1000;
    static int nTests;
    static Random random = new Random(352532535676L);
    static class Point {
        public final double x;
        public final double y;
        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }
    static final Comparator<Point> increasing = new Comparator<Point>() {
        public int compare(Point l, Point r) {
            return Double.compare(l.x * l.y, r.x * r.y);
        }
    };
    static void writeImpl(double... coords) {
        try {
            new File("tests").mkdir();
            PrintWriter out = new PrintWriter(String.format("tests/%02d", ++nTests));
            out.println(coords.length / 3);
            for (int i = 0; i < coords.length; i += 3) {
	            coords[i + 2] = Math.max(0.01, coords[i + 2]); // make sure it is non-zero
                out.printf(Locale.US, "%.2f %.2f %.2f%n", coords[i], coords[i + 1], coords[i + 2]);
            }
            out.close();
        } catch (IOException ex) {
            ex.printStackTrace();
            System.exit(0);
        }
    }
    static void write(Point[] pts) {
        double[] coords = new double[pts.length * 3];
        for (int i = 0, j = 0; i < pts.length; ++i) {
            double angle = random.nextDouble() * Math.PI * 2;
            double cos = Math.cos(angle);
            double sin = Math.sin(angle);
            coords[j++] = Math.abs(pts[i].x) * cos;
            coords[j++] = Math.abs(pts[i].x) * sin;
            coords[j++] = pts[i].y;
        }
        writeImpl(coords);
    }
    static void writeL(Point[] pts) {
        double[] coords = new double[pts.length * 3];
        for (int i = 0, j = 0; i < pts.length; ++i) {
            int sin, cos;
            switch (random.nextInt(4)) {
                case 0 : cos = 1; sin = 0; break;
                case 1 : cos = -1; sin = 0; break;
                case 2 : cos = 0; sin = 1; break;
                default: cos = 0; sin = -1; break;
            }
            coords[j++] = pts[i].x * cos;
            coords[j++] = pts[i].x * sin;
            coords[j++] = pts[i].y;
        }
        writeImpl(coords);
    }

    static void writeRandom(int n) {
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            pts[i] = new Point(random.nextDouble() * MAX_COORD, random.nextDouble() * (MAX_COORD - 1) + 1);
        }
        Arrays.sort(pts, increasing);
        write(pts);
    }

    static void writeLinear(int n, boolean jitter) {
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            int x = random.nextInt(30000);
            int y = 100000 - 3 * x;
            pts[i] = new Point(x * 1e-2, y * 1e-2);
        }
        if (jitter) {
            write(pts);
        } else {
            writeL(pts);
        }
    }

    static void writeCircle(int n) {
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            double angle = random.nextDouble() * Math.PI / 2;
            double cos = Math.cos(angle);
            double sin = Math.sin(angle);
            pts[i] = new Point(MAX_COORD * cos, MAX_COORD * sin);
        }
        write(pts);
    }

    static void writeAntiCircle(int n) {
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            double angle = random.nextDouble() * Math.PI / 2;
            double cos = Math.cos(angle);
            double sin = Math.sin(angle);
            pts[i] = new Point(MAX_COORD * (1 - cos), (MAX_COORD - 1) * (1 - sin) + 1);
        }
        write(pts);
    }

    public static void main(String[] args) throws IOException {
        writeImpl(1, 0, 1);
        writeImpl(1, 0, 1, 0, 1.5, 0.5);
        writeImpl(1, 0, 1, 0, 1.5, 0.5, -0.5, -0.5, 1);
        writeImpl(1, 0, 1, 0, 1, 1);
        writeImpl(1, 0, 3, 0, 2, 2, 2, 0, 2);
        writeImpl(1, 0, 4, 0, 1, 4, 0, 2, 2);
        writeImpl(1, 0, 5, 0, 1, 5, 0, 2, 2);
        writeImpl(1, 0, 5, 0, 1, 4, 0, 2, 2);
        writeImpl(1, 0, 5, 0, 1, 4, -1, 0, 3, 0, -1, 2, 0, 2, 2, 1, 0, 2, 0, 0, 1);
        writeImpl(4, 0, 4, 5, 0, 2);
        writeImpl(4, 0, 4, 5, 0, 1, -5, 0, 1);
        for (int x : new int[] { 1, 100 }) {
            writeImpl(x, 0, 1, 0, x, 10, -x, 0, 6, 0, -x, 4);
        }
        for (int i = 2; i <= 10; i += 2) {
            writeRandom(i * 1000);
            writeLinear(i * 1000, false);
            writeLinear(i * 1000, true);
            writeCircle(i * 1000);
            writeAntiCircle(i * 1000);
        }
        long[] seeds = {
            -3348538676897074043L, 4138493820934744273L, 1910755848716892310L,
            -7152070508404328783L, 5463273378926227074L, -8572636506706544972L,
            -5592454411309794477L, -8526054138173443731L, 5298684141434597596L,
            442092559413991290L
        };
        for (long seed : seeds) {
            Random old = random;
            random = new Random(seed);
            writeLinear(10000, true);
            random = old;
        }
    }
}

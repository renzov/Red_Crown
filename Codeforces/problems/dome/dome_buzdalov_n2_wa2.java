import java.io.*;
import java.util.*;

public class dome_buzdalov_n2_wa2 {
    static final double EPS = 1e-9;

    static boolean eq(double a, double b) {
        return Math.abs(a - b) <= EPS;
    }
    static int cmp(double a, double b) {
        return eq(a, b) ? 0 : a < b ? -1 : 1;
    }
    static boolean lt(double a, double b) {
        return a < b && !eq(a, b);
    }
    static boolean le(double a, double b) {
        return a < b || eq(a, b);
    }
    static boolean gt(double a, double b) {
        return a > b && !eq(a, b);
    }
    static boolean ge(double a, double b) {
        return a > b || eq(a, b);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("dome.in"));
        int n = Integer.parseInt(in.readLine());
        double[] x = new double[n];
        double[] y = new double[n];
        for (int i = 0; i < n; ++i) {
            String s = in.readLine();
            int fws = s.indexOf(' ');
            int lws = s.lastIndexOf(' ');
            double _x = Double.parseDouble(s.substring(0, fws));
            double _y = Double.parseDouble(s.substring(fws + 1, lws));
            double _z = Double.parseDouble(s.substring(lws + 1));
            x[i] = Math.sqrt(_x * _x + _y * _y);
            y[i] = _z;
        }
        in.close();

        double ansZ = 0;
        double ansR = 0;
        double ansV = 0;
        for (int i = 0; i < n; ++i) {
            double cx = x[i];
            double cy = y[i];
            double max = Double.POSITIVE_INFINITY;
            double min = 0;
            for (int j = 0; j < n; ++j) {
                double nx = x[j];
                double ny = y[j];
                if (gt(nx, cx)) {
                    max = Math.min(max, -(ny - cy) / (nx - cx));
                } else if (lt(nx, cx)) {
                    min = Math.max(min, -(ny - cy) / (nx - cx));
                }
            }
            double opt = 2 * cy / cx;
            if (min <= opt && opt <= max) {
                double optR = cx + cy / opt;
                double optZ = cy + cx * opt;
                double optV = optR * optR * optZ;
                if (optV > ansV) {
                    ansV = optV;
                    ansR = optR;
                    ansZ = optZ;
                }
            }
        }

        PrintWriter out = new PrintWriter("dome.out");
        out.println(ansZ + " " + ansR);
        out.close();
    }
}

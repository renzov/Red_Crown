import java.io.*;
import java.util.*;

public class dome_buzdalov_n2_wa1 {
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
            {
                double currR = 1.5 * cx;
                double currZ = 3.0 * cy;
                double currV = currR * currR * currZ;
                if (currV > ansV) {
                    ansV = currV;
                    ansZ = currZ;
                    ansR = currR;
                }
            }
            for (int j = 0; j < n; ++j) {
                double nx = x[j];
                double ny = y[j];
                if (lt(nx, cx) && gt(ny, cy)) {
                    double currR = cx + (nx - cx) / (cy - ny) * cy;
                    double currZ = cy + (ny - cy) / (cx - nx) * cx;
                    double currV = currR * currR * currZ;
                    if (currV > ansV) {
                        ansV = currV;
                        ansZ = currZ;
                        ansR = currR;
                    }
                }
            }
        }

        PrintWriter out = new PrintWriter("dome.out");
        out.println(ansZ + " " + ansR);
        out.close();
    }
}

import java.io.*;
import java.util.*;

public class dome_buzdalov {
    static double minRadius(double height, double[] r, double[] z) {
        double ans = 0;
        for (int i = 0; i < r.length; ++i) {
            ans = Math.max(ans, r[i] * height / (height - z[i]));
        }
        return ans;
    }

    public static double[] solve(double[] r, double[] z) {
        double maxZ = 0;
        for (double zz : z) {
            maxZ = Math.max(maxZ, zz);
        }
        double left = maxZ, right = 1e6;
        for (int it = 0; it < 100; ++it) {
            double minMid = (left * 2 + right) / 3;
            double maxMid = (left + 2 * right) / 3;
            double minMidA = minRadius(minMid, r, z);
            double maxMidA = minRadius(maxMid, r, z);
            if (minMidA * minMidA * minMid < maxMidA * maxMidA * maxMid) {
                right = maxMid;
            } else {
                left = minMid;
            }
        }
        return new double[] { left, minRadius(left, r, z) };
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        Scanner in = new Scanner(new File("dome.in"));
        int n = in.nextInt();
        double[] r = new double[n];
        double[] z = new double[n];
        boolean hasOutsider = false;
        for (int i = 0; i < n; ++i) {
            double x = in.nextDouble();
            double y = in.nextDouble();
            r[i] = Math.sqrt(x * x + y * y);
            hasOutsider |= r[i] > 0;
            z[i] = in.nextDouble();
        }
        in.close();
        if (!hasOutsider) {
            throw new AssertionError("!");
        }

        double[] ans = solve(r, z);

        PrintWriter out = new PrintWriter("dome.out");
        out.printf(Locale.US, "%f %f%n", ans[0], ans[1]);
        out.close();
    }
}

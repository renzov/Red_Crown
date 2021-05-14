import java.io.*;
import java.util.*;

public class dome_buzdalov_n2 {
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

        double ansZ = Double.POSITIVE_INFINITY;
        double ansR = Double.POSITIVE_INFINITY;
        double ansV = Double.POSITIVE_INFINITY;
        for (int i = 0; i < n; ++i) {
            double cx = x[i];
            double cy = y[i];
            double min = 0;
            double max = Double.POSITIVE_INFINITY;
            for (int j = 0; j < n; ++j) {
                double nx = x[j];
                double ny = y[j];
                if (nx < cx) {
                    min = Math.max(min, (ny - cy) / (cx - nx));
                } else if (nx > cx) {
                    max = Math.min(max, (cy - ny) / (nx - cx));
                } else if (ny > cy) {
                    max = -1;
                }
            }
            if (min <= 2 * cy / cx && 2 * cy / cx <= max) {
                double optZ = 3 * cy;
                double optR = 1.5 * cx;
                double optV = optR * optR * optZ;
                if (optV < ansV) {
                    ansV = optV;
                    ansR = optR;
                    ansZ = optZ;
                }
            } else if (min <= max) {
                double minZ = cy + cx * min;
                double minR = cx + cy / min;
                double minV = minR * minR * minZ;
                double maxZ = cy + cx * max;
                double maxR = cx + cy / max;
                double maxV = maxR * maxR * maxZ;
                if (minV <= maxV) {
                    if (minV < ansV) {
                        ansV = minV;
                        ansR = minR;
                        ansZ = minZ;
                    }
                } else {
                    if (maxV < ansV) {
                        ansV = maxV;
                        ansR = maxR;
                        ansZ = maxZ;
                    }
                }
            }
        }

        PrintWriter out = new PrintWriter("dome.out");
        out.println(ansZ + " " + ansR);
        out.close();
    }
}

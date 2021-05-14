import java.io.*;
import java.util.*;

public class graveyard_as {

    public void run() throws IOException {
        Scanner in = new Scanner(new File("graveyard.in"));
        PrintWriter out = new PrintWriter(new File("graveyard.out"));

        int n = in.nextInt();
        int m = in.nextInt();
        assert (2 <= n && n <= 1000);
        assert (1 <= m && m <= 1000);

        m += n;

        double[] a = new double[n];
        double[] b = new double[m];
        for (int i = 0; i < n; i++) {
            a[i] = 10000.0 * i / n;
        }
        for (int i = 0; i < m; i++) {
            b[i] = 10000.0 * i / m;
        }

        double[][] d = new double[m][n];
        d[0][0] = 0;
        for (int i = 1; i < m; i++) {
            d[i][0] = 0;
            for (int j = 1; j <= i && j < n; j++) {
                if (j < i) {
                    d[i][j] = d[i - 1][j];
                } else {
                    d[i][j] = Double.MAX_VALUE;
                }
                d[i][j] = Math.min(d[i][j], d[i - 1][j - 1] + Math.abs(a[j] - b[i]));
            }
        }

        out.printf("%.9f\n", d[m - 1][n - 1]);

        in.close();
        out.close();
    }

    public static void main(String[] arg) throws IOException {
        Locale.setDefault(Locale.US);
        new graveyard_as().run();
    }
}

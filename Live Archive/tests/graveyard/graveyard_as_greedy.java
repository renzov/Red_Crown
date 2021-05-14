import java.io.IOException;
import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Locale;

public class graveyard_as_greedy {

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

        boolean[] u = new boolean[m];
        double r = 0;
        for (int i = 0; i < n; i++) {
            double best = Double.MAX_VALUE;
            int bj = -1;
            for (int j = 0; j < m; j++) {
                if (!u[j] && Math.abs(a[i] - b[j]) < best) {
                    best = Math.abs(a[i] - b[j]);
                    bj = j;
                }
            }
            u[bj] = true;
            r += best;
        }

        out.printf("%.9f\n", r);

        in.close();
        out.close();
    }

    public static void main(String[] arg) throws IOException {
        Locale.setDefault(Locale.US);
        new graveyard_as_greedy().run();
    }
}

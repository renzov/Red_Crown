import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

import static java.lang.Math.abs;
import static java.lang.Math.min;

public class evacuation_as {
    Scanner in;
    PrintWriter out;

    final static int MAXN = 5000;
    final static int MAXC = 1000000000;
    final static long BIG = 2L * MAXN * MAXC;

    class Location implements Comparable<Location> {
        int i;
        long p;

        Location(int i, long p) {
            this.i = i;
            this.p = p;
        }

        public int compareTo(Location o) {
            return p < o.p ? -1 : p > o.p ? 1 : i - o.i;
        }
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        assertRange(n, 1, MAXN, "n");
        final Location[] a = new Location[n];
        for (int i = 0; i < n; i++) {
            int t = in.nextInt();
            assertRange(t, 1, MAXC, "team " + (i + 1) + " location");
            a[i] = new Location(i, t);
        }
        Arrays.sort(a);
        for (int i = 0; i < n - 1; i++) {
            doAssert(a[i].p != a[i + 1].p, "Locations of teams " + a[i].i + " and " + (a[i + 1].i + 1) + " are the same");
        }

        int m = in.nextInt();
        assertRange(m, 1, n, "m");
        final Location[] b = new Location[m];
        for (int i = 0; i < m; i++) {
            int t = in.nextInt();
            assertRange(t, 1, MAXC, "shelter " + (i + 1) + " location");
            b[i] = new Location(i, t);
        }
        Arrays.sort(b);
        for (int i = 0; i < m - 1; i++) {
            doAssert(b[i].p != b[i + 1].p, "Locations of shelters " + a[i].i + " and " + (a[i + 1].i + 1) + " are the same");
        }

        final long[][] d = new long[m][n];

        d[0][0] = abs(a[0].p - b[0].p);
        for (int i = 1; i < n; i++) {
            d[0][i] = d[0][i - 1] + abs(a[i].p - b[0].p);
        }

        for (int i = 1; i < m; i++) {
            Arrays.fill(d[i], BIG);
            for (int j = i; j < n; j++) {
                d[i][j] = min(d[i][j - 1], d[i - 1][j - 1]) + abs(a[j].p - b[i].p);
            }
        }

        out.println(d[m - 1][n - 1]);
        final int[] ans = new int[n];
        new Object() {
            public void go(int i, int j) {
                if (j < 0) {
                    return;
                }
                ans[a[j].i] = b[i].i;
                if (i == 0) {
                    go(i, j - 1);
                } else {
                    if (d[i - 1][j - 1] < d[i][j - 1]) {
                        go(i - 1, j - 1);
                    } else {
                        go(i, j - 1);
                    }
                }
            }
        }.go(m - 1, n - 1);

        for (int i = 0; i < n; i++) {
            out.print(ans[i] + 1);
            if (i < n - 1) {
                out.print(" ");
            }
        }
        out.println();
    }

    public void run() {
        try {
            in = new Scanner(new File("evacuation.in"));
            out = new PrintWriter(new File("evacuation.out"));

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void assertRange(int n, int lower, int upper, String name) {
        doAssert(lower <= n && n <= upper, name + " is not within [" + lower + ", " + upper + "]");
    }

    public void doAssert(boolean b, String... msg) {
        StringBuilder message = new StringBuilder();
        for (String z : msg) {
            message.append(z);
        }
        if (!b) {
            throw new AssertionError(message.toString());
        }
    }

    public static void main(String[] arg) {
        new evacuation_as().run();
    }
}
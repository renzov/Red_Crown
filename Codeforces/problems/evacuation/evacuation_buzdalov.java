import java.io.*;
import java.util.*;

public class evacuation_buzdalov {
    static class Indexed implements Comparable<Indexed> {
        final int index;
        final int value;
        public Indexed(int index, int value) {
            this.index = index;
            this.value = value;
        }
        public int compareTo(Indexed that) {
            return value - that.value;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("evacuation.in"));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer fl = new StringTokenizer(in.readLine());
        Indexed[] teams = new Indexed[n];
        for (int i = 0; i < n; ++i) {
            teams[i] = new Indexed(i, Integer.parseInt(fl.nextToken()));
        }
        int m = Integer.parseInt(in.readLine());
        StringTokenizer sl = new StringTokenizer(in.readLine());
        Indexed[] shelters = new Indexed[m];
        for (int i = 0; i < m; ++i) {
            shelters[i] = new Indexed(i, Integer.parseInt(sl.nextToken()));
        }
        in.close();
        Arrays.sort(teams);
        Arrays.sort(shelters);

        long INF = 9000000000000000000L;
        long[][] v = new long[n + 1][m + 1];
        boolean[][] b = new boolean[n + 1][m + 1];
        for (long[] vv : v) {
            Arrays.fill(vv, INF);
        }
        v[0][0] = 0;
        for (int t = 0; t < n; ++t) {
            for (int s = 0; s <= m; ++s) {
                if (s > 0) {
                    long val = v[t][s] + Math.abs(teams[t].value - shelters[s - 1].value);
                    if (v[t + 1][s] > val) {
                        v[t + 1][s] = val;
                        b[t + 1][s] = false;
                    }
                }
                if (s < m) {
                    long val = v[t][s] + Math.abs(teams[t].value - shelters[s].value);
                    if (v[t + 1][s + 1] > val) {
                        v[t + 1][s + 1] = val;
                        b[t + 1][s + 1] = true;
                    }
                }
            }
        }

        int[] ans = new int[n];
        for (int i = n - 1, cs = m; i >= 0; --i) {
            ans[teams[i].index] = shelters[cs - 1].index + 1;
            if (b[i + 1][cs]) {
                --cs;
            }
        }

        PrintWriter out = new PrintWriter("evacuation.out");
        out.println(v[n][m]);
        for (int i = 0; i < n; ++i) {
            out.print(ans[i] + " ");
        }
        out.println();
        out.close();
    }
}

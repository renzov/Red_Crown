import java.util.*;
import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;

public class interconnect_pm {

    private static int nn;

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("interconnect.in"));
        PrintWriter out = new PrintWriter("interconnect.out");
        int n = in.nextInt();
        nn = (n * (n - 1)) / 2;
        int m = in.nextInt();
        int[] p = new int[n];
        for (int i = 0; i < n; i++) p[i] = i;
        for (int i = 0; i < m; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            u--;
            v--;
            int k = p[u];
            for (int j = 0; j < n; j++) {
                if (p[j] == k) {
                    p[j] = p[v];
                }
            }
        }
        List<Integer> st = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int j = 0; j < n; j++) {
                if (p[j] == i) s++;
            }
            if (s > 0) {
                st.add(s);
            }
        }
        Collections.sort(st);
        List<Integer> fn = new ArrayList<Integer>();
        fn.add(n);
        mem.put(fn, 0.0);
        out.println(get(st));
        System.out.println(mem.size());
        out.close();
    }

    static Map<List<Integer>, Double> mem = new HashMap<List<Integer>, Double>();

    private static double get(List<Integer> st) {
        Double ret = mem.get(st);
        if (ret != null) return ret;
        int m = st.size();
        int[][] a = new int[m][m];
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                a[i][j] = st.get(i) * st.get(j);
            }
        }
        int s = 0;
        for (int i = 0; i < m; i++) {
            s += st.get(i) * (st.get(i) - 1) / 2;
        }
        double res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                List<Integer> ss = new ArrayList<Integer>(st.size() - 1);
                boolean q = true;
                int z = st.get(i) + st.get(j);
                for (int k = 0; k < m; k++) {
                    if (k != i && k != j) {
                        int zz = st.get(k);
                        if (q && zz >= z) {
                            q = false;
                            ss.add(z);
                        }
                        ss.add(zz);
                    }
                }
                if (q)
                    ss.add(z);
                double p = a[i][j] * 1.0 / (nn - s);
                double e = a[i][j] * 1.0 / ((1 - s * 1.0 / nn) * (1 - s * 1.0 / nn) * nn);
                e = e + get(ss) * p;
                res += e;
            }
        }
        mem.put(st, res);
        return res;
    }

}

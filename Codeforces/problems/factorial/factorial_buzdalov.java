import java.io.*;
import java.util.*;

public class factorial_buzdalov {
    static final int MAX_V = 10006;
    static int[] primes;
    static {
        boolean[] nip = new boolean[1 + MAX_V];
        int cnt = 0;
        for (int i = 2; i < nip.length; ++i) {
            if (!nip[i]) {
                ++cnt;
                for (int j = i * i; j < nip.length; j += i) {
                    nip[j] = true;
                }
            }
        }
        primes = new int[cnt];
        for (int i = 2, j = 0; i < nip.length; ++i) {
            if (!nip[i]) {
                primes[j++] = i;
            }
        }
    }

    static int[] factorize(int val) {
        int[] rv = new int[primes.length];
        for (int i = 0; i < primes.length; ++i) {
            int p = primes[i];
            int vcp = val;
            int ans = 0;
            while (vcp >= p) {
                ans += vcp / p;
                vcp /= p;
            }
            rv[i] = ans;
        }
        return rv;
    }

    public static void main(String[] args) throws IOException {
        int[][] f2 = new int[MAX_V + 1][];
        for (int f = 0; f < f2.length; ++f) {
            f2[f] = (f >= 2 ? factorize(f) : new int[primes.length]);
        }

        Scanner in = new Scanner(new File("factorial.in"));
        int n = in.nextInt();
        int m = in.nextInt();
        int[] count = new int[primes.length];
        for (int i = 0; i < n; ++i) {
            int x = in.nextInt();
            for (int j = 0; j < primes.length; ++j) {
                count[j] += f2[x][j];
            }
        }
        for (int i = 0; i < m; ++i) {
            int x = in.nextInt();
            for (int j = 0; j < primes.length; ++j) {
                count[j] -= f2[x][j];
            }
        }
        in.close();

        boolean isInteger = true;
        for (int i : count) {
            isInteger &= i >= 0;
        }
        List<int[]> ans = new ArrayList<int[]>();
        if (isInteger) {
            for (int fact = f2.length - 1; fact >= 2; --fact) {
                int max = Integer.MAX_VALUE;
                for (int i = 0; i < primes.length; ++i) {
                    if (f2[fact][i] > 0) {
                        max = Math.min(max, count[i] / f2[fact][i]);
                    }
                }
                if (max > 0) {
                    ans.add(new int[] { fact, max });
                    for (int i = 0; i < primes.length; ++i) {
                        count[i] -= f2[fact][i] * max;
                    }
                }
            }
        }
        PrintWriter out = new PrintWriter("factorial.out");
        if (isInteger) {
            out.println(ans.size());
            for (int[] aa : ans) {
                out.println(aa[0] + " " + aa[1]);
            }
        } else {
            out.println(-1);
        }
        out.close();
    }
}

import java.io.*;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Random;
import java.util.StringTokenizer;
import static java.lang.Math.*;

public class Tests {

    int testNo = 1;

    public void printTest(int[] a, int[] b) {
        PrintWriter out = null;
        try {
            out = new PrintWriter("tests/" + testNo / 10 + testNo % 10);
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            return;
        }

        out.println(a.length);
        for (int i = 0; i < a.length; i++) {
            out.print(a[i]);
            if (i < a.length - 1) {
                out.print(" ");
            }
        }
        out.println();
        out.println(b.length);
        for (int i = 0; i < b.length; i++) {
            out.print(b[i]);
            if (i < b.length - 1) {
                out.print(" ");
            }
        }
        out.println();

        out.close();
        testNo++;
    }

    Random rnd = new Random(23497240274L);

    int[] randomDifferentArray(int n, int maxc) {
        int[] r = new int[n];
        HashSet<Integer> h = new HashSet<Integer>();
        for (int i = 0; i < n; i++) {
            int a = rnd.nextInt(maxc) + 1;
            while (h.contains(a)) {
                a = rnd.nextInt(maxc) + 1;
            }
            h.add(a);
            r[i] = a;
        }
        return r;
    }

    int[] rleArray(String code) {
        StringTokenizer st = new StringTokenizer(code);
        int n = st.countTokens() / 2;
        int[] pos = new int[n];
        int[] size = new int[n];
        for (int i = 0; i < n; i++) {
            pos[i] = Integer.parseInt(st.nextToken());
            size[i] = Integer.parseInt(st.nextToken());
        }
        return rleArray(pos, size);
    }

    int[] rleArray(int[] pos, int[] size) {
        int n = 0;
        for (int i = 0; i < size.length; i++) {
            n += size[i];
        }
        int[] r = new int[n];
        int k = -1;
        int v = 0;
        for (int i = 0; i < pos.length; i++) {
            if (pos[i] + size[i] + 1 > MAXC) {
                pos[i] = MAXC - size[i] + 1;
            }
            for (int j = 0; j < size[i]; j++) {
                r[v++] = max(k, pos[i] + j);
                k++;
            }
        }
        randomShuffle(r);
        return r;
    }

    void randomShuffle(int[] v) {
        for (int i = 0; i < v.length; i++) {
            int j = rnd.nextInt(i + 1);
            int t = v[j]; v[j] = v[i]; v[i] = t;
        }
    }

    int[] randomRLEArray(int n, int p, int maxc) {
        int[] pos = new int[p];
        int[] size = new int[p];
        for (int i = 0; i < p; i++) {
            size[i]++;
            pos[i] = rnd.nextInt(maxc) + 1;
            n--;
        }
        for (int i = 0; i < n; i++) {
            size[rnd.nextInt(p)]++;
        }
        return rleArray(pos, size);
    }

    int[] randomRLENoisyArray(int n, int p, int maxc, int pchange) {
        int[] pos = new int[p];
        int[] size = new int[p];
        for (int i = 0; i < p; i++) {
            size[i]++;
            pos[i] = rnd.nextInt(maxc) + 1;
            n--;
        }
        for (int i = 0; i < n; i++) {
            size[rnd.nextInt(p)]++;
        }
        int[] r = rleArray(pos, size);
        HashSet<Integer> was = new HashSet<Integer>();
        for (int i = 0; i < r.length; i++) {
            while (was.contains(r[i]) || rnd.nextInt(100) < pchange) {
                r[i] = rnd.nextInt(maxc) + 1;
            }
            was.add(r[i]);
        }
        return r;
    }

    final static int MAXN = 4000;
    final static int MAXC = 1000000000;

    public void run() {
        new File("tests").mkdir();

        printTest(new int[]{1, 2, 3}, new int[]{2, 10});
        printTest(new int[]{1}, new int[]{1});
        printTest(new int[]{1}, new int[]{2});
        printTest(new int[]{2}, new int[]{1});
        printTest(new int[]{1}, new int[]{1000000000});
        printTest(new int[]{1000000000}, new int[]{1});
        printTest(new int[]{1, 2, 3, 4, 5}, new int[]{1, 5, 10});
        printTest(new int[]{6, 7, 8, 9, 10}, new int[]{1, 5, 10});
        printTest(new int[]{1, 2, 3, 20, 21, 22}, new int[]{1, 20});

        printTest(rleArray("1 3999 1000000 1"), rleArray("1 1 1000000 3999"));
        printTest(rleArray("1 4000"), rleArray("1000000000 4000"));
        printTest(rleArray("1 4000"), rleArray("1000000000 1"));
        printTest(rleArray("1 1000 10000 1000 20000 1000 30000 1000"), rleArray("1 100 10000 100 20000 100 30000 100"));
        printTest(rleArray("1 1000 10000 1000 20000 1000 30000 1000"), rleArray("1 100 100000 100 200000 100 300000 100"));
        printTest(rleArray("1 1000 10000 1000 20000 1000 30000 1000"), rleArray("1 1000 100000 1000 200000 1000 300000 1000"));

        for (int i = 10; i <= 4000; i *= 20) {
            for (long j = 1000; j <= 1000000000L; j *= 1000000) {
                for (int k = i; k <= 4000; k *= 20) {
                    for (long l = 1000; l <= 1000000000L; l *= 1000000) {
                        printTest(randomDifferentArray(k, max(k, (int) j)), randomDifferentArray(i, max(i, (int) l)));
                    }
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            printTest(randomDifferentArray(MAXN, MAXC), randomDifferentArray(MAXN, MAXC));
        }

        for (int i = 0; i < 5; i++) {
            printTest(randomRLEArray(4000, 10, 1000000000), randomRLEArray(4000, 10, 1000000000));
        }
        for (int i = 0; i < 5; i++) {
            printTest(randomRLEArray(4000, rnd.nextInt(100) + 1, 1000000000), randomRLEArray(4000, rnd.nextInt(100) + 1, 1000000000));
        }
        for (int i = 0; i < 5; i++) {
            printTest(randomRLEArray(4000 - rnd.nextInt(1000), rnd.nextInt(100) + 1, 1000000000), randomRLEArray(3000 - rnd.nextInt(1000), rnd.nextInt(100) + 1, 1000000000));
        }
        for (int i = 0; i < 5; i++) {
            printTest(randomRLENoisyArray(4000, 10, 1000000000, 10 * i), randomRLENoisyArray(4000, 10, 1000000000, 10 * i));
        }
    }

    public static void main(String[] args) {
        new Tests().run();
    }
}

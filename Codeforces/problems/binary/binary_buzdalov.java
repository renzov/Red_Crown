import java.io.*;
import java.util.*;

public class binary_buzdalov {
    static int[][][] d1;
    static int[][][] d10;

    static void init(int[][] m0) {
        d1 = new int[11][10][20];
        d10 = new int[11][20][20];

        //First fill d1 because d10 depends on it
        for (int init = 0; init <= 10; ++init) {
            for (int digit = 0; digit < 10; ++digit) {
                d1[init][digit][0] = m0[init][digit];
            }
        }
        for (int times = 1; times < 20; ++times) {
            for (int init = 0; init <= 10; ++init) {
                for (int digit = 0; digit < 10; ++digit) {
                    int t = init;
                    for (int i = 0; i < 10; ++i) {
                        t = d1[t][digit][times - 1];
                    }
                    d1[init][digit][times] = t;
                }
            }
        }

        //Then fill d10
        for (int init = 0; init <= 10; ++init) {
            for (int digitLength = 0; digitLength < 20; ++digitLength) {
                int t = init;
                for (int i = 0; i < 10; ++i) {
                    t = d1[t][i][digitLength];
                }
                d10[init][digitLength][0] = t;
            }
        }
        for (int groupLength = 1; groupLength < 20; ++groupLength) {
            for (int init = 0; init <= 10; ++init) {
                for (int digitLength = 0; digitLength < 20; ++digitLength) {
                    int t = init;
                    for (int i = 0; i < 10; ++i) {
                        t = d10[t][digitLength][groupLength - 1];
                    }
                    d10[init][digitLength][groupLength] = t;
                }
            }
        }
    }

    static void aggregate(int[] min, int cp, int[] ans) {
        for (int i = 0; i < cp; ++i) {
            ans[i] = d10[ans[i]][i][cp - i - 1];
        }
        for (int i = cp; i < min.length; ++i) {
            ans[i] = d1[ans[i]][min[i]][cp];
        }
    }

    static void split(int[] min, int[] max, int cp, int[] ans) {
        while (cp > 0 && min[cp - 1] == max[cp - 1]) {
            --cp;
        }
        if (cp == 0) {
            aggregate(min, cp, ans);
        } else {
            int[] mid = new int[min.length];
            for (int i = cp; i < min.length; ++i) {
                mid[i] = min[i];
            }

            boolean needLeftSplit = false;
            for (int i = 0; i < cp - 1; ++i) {
                mid[i] = 9;
                needLeftSplit |= min[i] != 0;
            }
            mid[cp - 1] = min[cp - 1];
            if (needLeftSplit) {
                split(min, mid, cp - 1, ans);
            } else {
                aggregate(min, cp - 1, ans);
            }

            for (int i = min[cp - 1] + 1; i < max[cp - 1]; ++i) {
                mid[cp - 1] = i;
                aggregate(mid, cp - 1, ans);
            }

            boolean needRightSplit = false;
            for (int i = 0; i < cp - 1; ++i) {
                mid[i] = 0;
                needRightSplit |= max[i] != 9;
            }
            mid[cp - 1] = max[cp - 1];
            if (needRightSplit) {
                split(mid, max, cp - 1, ans);
            } else {
                aggregate(max, cp - 1, ans);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("binary.in"));
        int[][] m0 = new int[11][11];
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                m0[i][j] = in.nextInt();
            }
            m0[i][10] = m0[10][i] = i;
        }
        m0[10][10] = 10;
        init(m0);
        long minV = in.nextLong(), maxV = in.nextLong();
        in.close();

        int length = String.valueOf(maxV).length();
        int[] min = new int[length];
        int[] max = new int[length];
        long minC = minV, maxC = maxV;
        for (int i = 0; i < length; ++i, minC /= 10, maxC /= 10) {
            min[i] = (int) (minC % 10);
            max[i] = (int) (maxC % 10);
        }
        int[] ans = new int[length];
        Arrays.fill(ans, 10);
        split(min, max, length, ans);

        PrintWriter out = new PrintWriter("binary.out");
        for (int i = length - 1, j = 0; i >= 0; --i) {
            j |= ans[i];
            if (j != 0 || i == 0) {
                out.print(ans[i]);
            }
        }
        out.println();
        out.close();
    }
}

import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

class ideal_as_slow_bug {
    FastScanner in;
    PrintWriter out;

    class Edge {
        int t;
        int c;

        Edge(int t, int c) {
            this.t = t;
            this.c = c;
        }
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        assertRange(n, 2, 200000, "n");
        int m = in.nextInt();
        assertRange(m, 1, 200000, "m");

        ArrayList<Edge>[] edges = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            edges[i] = new ArrayList<Edge>();
        }

        for (int i = 0; i < m; i++) {
            int a = in.nextInt();
            int b = in.nextInt();
            int c = in.nextInt();
            assertRange(a, 1, n, "a[" + (i + 1) + "]");
            assertRange(b, 1, n, "b[" + (i + 1) + "]");
            a--;
            b--;
            assertRange(c, 1, 1000000000, "c[" + (i + 1) + "]");
            Edge e = new Edge(b, c);
            edges[a].add(e);
            e = new Edge(a, c);
            edges[b].add(e);
        }

        ArrayDeque<Integer> q = new ArrayDeque<Integer>();
        q.add(n - 1);
        boolean[] vis = new boolean[n];
        vis[n - 1] = true;
        int[] d = new int[n];
        while (q.size() > 0) {
            int v = q.removeFirst();
            for (Edge e : edges[v]) {
                if (!vis[e.t]) {
                    vis[e.t] = true;
                    d[e.t] = d[v] + 1;
                    q.add(e.t);
                }
            }
        }

        doAssert(vis[0], "Room n is not reachable from room 1");

        ArrayList<Edge>[] goodEdges = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            goodEdges[i] = new ArrayList<Edge>();
            for (Edge e : edges[i]) {
                if (d[e.t] == d[i] - 1) {
                    goodEdges[i].add(e);
                }
            }
        }

        int[] cur = new int[n];
        int[] next = new int[n];
        int curSize = 1;
        cur[0] = 0;

        Arrays.fill(vis, false);
        vis[0] = true;

        int[] from = new int[n];
        int[] via = new int[n];
        while (!vis[n - 1]) {
            int min = Integer.MAX_VALUE;
            for (int i = 0; i < curSize; i++) {
                int x = cur[i];
                for (Edge e : goodEdges[x]) {
                    if (e.c < min) {
                        min = e.c;
                    }
                }
            }

            int nextSize = 0;
            for (int i = 0; i < curSize; i++) {
                int x = cur[i];
                for (Edge e : goodEdges[x]) {
                    if (e.c == min && !vis[e.t]) {
                        next[nextSize++] = e.t;
                        from[e.t] = x;
                        via[e.t] = min;
                    }
                }
            }

            int[] tmp = cur; cur = next; next = tmp;
            curSize = nextSize;
        }

        ArrayList<Integer> ans = new ArrayList<Integer>();
        int wh = n - 1;
        while (wh != 0) {
            ans.add(via[wh]);
            wh = from[wh];
        }
        out.println(ans.size());
        for (int i = ans.size() - 1; i >= 0; i--) {
            out.print(ans.get(i));
            if (i > 0) {
                out.print(" ");
            }
        }
        out.println();
    }

    public void run() {
        try {
            in = new FastScanner(new File("ideal.in"));
            out = new PrintWriter(new File("ideal.out"));

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) throws FileNotFoundException {
            br = new BufferedReader(new FileReader(f));
        }

        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        void close() throws IOException {
            br.close();
        }
    }

    public static void main(String[] arg) {
        new ideal_as_slow_bug().run();
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

}
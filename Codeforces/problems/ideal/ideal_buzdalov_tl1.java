import java.io.*;
import java.util.*;

public class ideal_buzdalov_tl1 {
    static class Edge {
        public final int target;
        public final int symbol;
        public Edge(int target, int symbol) {
            this.target = target;
            this.symbol = symbol;
        }
    }

    static int[] bfs(int start, List<List<Edge>> graph) {
        int[] dist = new int[graph.size()];
        final int INF = 1000000000;
        Arrays.fill(dist, INF);
        dist[start] = 0;
        int[] q = new int[graph.size()];
        int head = 0, tail = 0;
        q[head++] = start;
        while (head > tail) {
            int curr = q[tail++];
            for (Edge e : graph.get(curr)) {
                int next = e.target;
                if (dist[next] == INF) {
                    dist[next] = dist[curr] + 1;
                    q[head++] = next;
                }
            }
        }
        return dist;
    }

    static class Path {
        public final Path prev;
        public final int symbol;
        public final int length;
        public Path(Path prev, int symbol) {
            this.prev = prev;
            this.length = prev == null ? 1 : prev.length + 1;
            this.symbol = symbol;
        }
        public void print(PrintWriter out) {
            if (prev != null) {
                prev.print(out);
                out.print(" ");
            }
            out.print(symbol);
        }
    }
    static Comparator<Path> cmp = new Comparator<Path>() {
        public int compare(Path l, Path r) {
            if (l == r) return 0;
            if (l == null) return -1;
            if (r == null) return 1;
            if (l.length != r.length) return l.length - r.length;
            int c = compare(l.prev, r.prev);
            return c == 0 ? l.symbol - r.symbol : c;
        }
    };

    static List<List<Edge>> graph;

    static Path[] optimal;
    static boolean[] used;
    static Path theOptimal;
    static int dist;

    static Path go(int index, int depth, Path soFar) {
        if (index == used.length - 1) {
            if (theOptimal == null || cmp.compare(soFar, theOptimal) < 0) {
                theOptimal = soFar;
            }
            return theOptimal;
        } else {
            if (depth >= dist) {
                return optimal[depth].prev;
            }
            used[index] = true;
            for (Edge e : graph.get(index)) {
                if (!used[e.target] && optimal[depth].symbol >= e.symbol) {
                    optimal[depth] = go(e.target, depth + 1, new Path(soFar, e.symbol));
                }
            }
            used[index] = false;
            return optimal[depth].prev;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("ideal.in"));
        int n, m;
        {
            String s = in.readLine();
            int ws = s.indexOf(' ');
            n = Integer.parseInt(s.substring(0, ws));
            m = Integer.parseInt(s.substring(ws + 1));
        }
        graph = new ArrayList<List<Edge>>();
        for (int i = 0; i < n; ++i) {
            graph.add(new ArrayList<Edge>());
        }
        for (int i = 0; i < m; ++i) {
            String s = in.readLine();
            int fws = s.indexOf(' ');
            int lws = s.lastIndexOf(' ');
            int source = Integer.parseInt(s.substring(0, fws)) - 1;
            int target = Integer.parseInt(s.substring(fws + 1, lws)) - 1;
            int symbol = Integer.parseInt(s.substring(lws + 1));
            graph.get(source).add(new Edge(target, symbol));
            graph.get(target).add(new Edge(source, symbol));
        }
        in.close();
        int[] fdist = bfs(0, graph);
        dist = fdist[n - 1];

        optimal = new Path[n];
        Path prev = null;
        for (int i = 0; i < n; ++i) {
            prev = optimal[i] = new Path(prev, 1000000001);
        }
        used = new boolean[n];
        go(0, 0, null);

        PrintWriter out = new PrintWriter("ideal.out");
        out.println(theOptimal.length);
        theOptimal.print(out);
        out.println();
        out.close();
    }
}

import java.io.*;
import java.util.*;

public class ideal_buzdalov_wa1 {
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

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("ideal.in"));
        int n, m;
        {
            String s = in.readLine();
            int ws = s.indexOf(' ');
            n = Integer.parseInt(s.substring(0, ws));
            m = Integer.parseInt(s.substring(ws + 1));
        }
        List<List<Edge>> graph = new ArrayList<List<Edge>>();
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
        int[] bdist = bfs(n - 1, graph);
        int dist = fdist[n - 1];
        int[] path = new int[dist];
        Set<Integer> curr = new HashSet<Integer>();
        curr.add(0);
        for (int i = 0; i < dist; ++i) {
            Set<Integer> next = new HashSet<Integer>();
            int symbol = 999999999;
            for (int c : curr) {
                for (Edge e : graph.get(c)) {
                    if (fdist[e.target] == 1 + fdist[c] && fdist[e.target] + bdist[e.target] == dist) {
                        if (symbol > e.symbol) {
                            symbol = e.symbol;
                            next.clear();
                        }
                        if (symbol == e.symbol) {
                            next.add(e.target);
                        }
                    }
                }
            }
            path[i] = symbol;
            curr = next;
        }
        PrintWriter out = new PrintWriter("ideal.out");
        out.println(path.length);
        for (int i : path) {
            out.print(i);
            out.print(" ");
        }
        out.println();
        out.close();
    }
}

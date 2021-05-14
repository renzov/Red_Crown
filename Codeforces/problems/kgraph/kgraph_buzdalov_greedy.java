import java.io.*;
import java.util.*;

public class kgraph_buzdalov_greedy {
    static List<List<Integer>> graph = new ArrayList<List<Integer>>();
    static int[] colors;
    static int k;
    static Set<Integer> free = new HashSet<Integer>();
    static boolean color(int vertex) {
        colors[vertex] = -2;
        for (int next : graph.get(vertex)) {
            if (colors[next] == -1 && !color(next)) {
                return false;
            }
        }
        for (int next : graph.get(vertex)) {
            if (colors[next] >= 0) {
                free.remove(colors[next]);
            }
        }
        int myColor = free.isEmpty() ? -1 : free.iterator().next();
        for (int next : graph.get(vertex)) {
            if (colors[next] >= 0) {
                free.add(colors[next]);
            }
        }
        if (myColor == -1) {
            return false;
        } else {
            colors[vertex] = myColor;
            return true;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("kgraph.in"));
        int n = -1, m = 0;
        for (int i = 0; i <= m; ++i) {
            String ln = in.readLine();
            int ws = ln.indexOf(' ');
            int a = Integer.parseInt(ln.substring(0, ws));
            int b = Integer.parseInt(ln.substring(ws + 1));
            if (n == -1) {
                n = a;
                m = b;
                for (int j = 0; j < n; ++j) {
                    graph.add(new ArrayList<Integer>());
                }
            } else {
                graph.get(a - 1).add(b - 1);
                graph.get(b - 1).add(a - 1);
            }
        }
        Random random = new Random();
        for (int i = 0; i < n; ++i) {
            k = Math.max(k, graph.get(i).size());
        }
        if (k % 2 == 0) {
            ++k;
        }
        colors = new int[n];
        do {
            for (int i = 0; i < k; ++i) {
                free.add(i);
            }
            Arrays.fill(colors, -1);
        } while (!color(random.nextInt(n)));

        PrintWriter out = new PrintWriter("kgraph.out");
        out.println(k);
        for (int i : colors) {
            out.println(i + 1);
        }
        out.close();
    }
}

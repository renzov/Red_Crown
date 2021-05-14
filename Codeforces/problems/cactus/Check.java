import ru.ifmo.testlib.*;
import java.util.*;

/**
 * NEERC 2010
 * A checker for the problem Cactus Revolution.
 * @author Maxim Buzdalov
 */
public class Check implements Checker {
    static class Graph {
        public int[] vertexColors;
        public List<List<Integer>> edges = new ArrayList<List<Integer>>();

        public Graph(int nVertices) {
            vertexColors = new int[nVertices];
            Arrays.fill(vertexColors, -1);
            for (int i = 0; i < nVertices; ++i) {
                edges.add(new ArrayList<Integer>());
            }
        }

        public void addEdge(int source, int target) {
            edges.get(source).add(target);
            edges.get(target).add(source);
        }

        public int collectSameColored(int vertex) {
            int result = 1;
            int color = vertexColors[vertex];
            vertexColors[vertex] = -1;
            for (int next : edges.get(vertex)) {
                if (color == vertexColors[next]) {
                    result += collectSameColored(next);
                }
            }
            return result;
        }
    }

    @Override
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int n = inf.nextInt();
        int m = inf.nextInt();
        int k = inf.nextInt();
        int componentSize = n / k;
        Graph g = new Graph(n);
        for (int p = 0; p < m; ++p) {
            int size = inf.nextInt();
            int prev = inf.nextInt() - 1;
            for (int i = 1; i < size; ++i) {
                g.addEdge(prev, prev = inf.nextInt() - 1);
            }
        }
        boolean impossible = false;
        readLoop:
        for (int comp = 0; comp < k; ++comp) {
            int prev = -1;
            for (int i = 0; i < componentSize; ++i) {
                if (ouf.seekEoLn()) {
                    Outcome.quit(Outcome.Type.WA,
                                 "Expected %d vertices in the component %d, found only %d",
                                 componentSize, comp + 1, i);
                }
                int vertex = ouf.nextInt();
                if (vertex == -1 && comp == 0 && i == 0 && ouf.seekEoF()) {
                    impossible = true;
                    break readLoop;
                }
                if (vertex <= 0 || vertex > n) {
                    Outcome.quit(Outcome.Type.WA,
                                 "Vertex number is out of bounds: %d", vertex);
                }
                if (prev > vertex) {
                    Outcome.quit(Outcome.Type.WA,
                                 "The sequence is not sorted");
                }
                prev = vertex;
                if (g.vertexColors[vertex - 1] != -1) {
                    Outcome.quit(Outcome.Type.WA,
                                 "Vertex %d is listed in lines (at least) %d, %d ",
                                 vertex, g.vertexColors[vertex - 1] + 1, comp + 1);
                }
                g.vertexColors[vertex - 1] = comp;
            }
            if (!ouf.seekEoLn()) {
                Outcome.quit(Outcome.Type.WA, "The component %d contains too many vertices", comp + 1);
            }
            ouf.skipLine();
        }
        if (!ouf.seekEoF()) {
            Outcome.quit(Outcome.Type.WA, "Extra information in the output file");
        }
        if (!impossible) {
            for (int v = 0; v < n; ++v) {
                if (g.vertexColors[v] >= 0) {
                    int size = g.collectSameColored(v);
                    if (size != componentSize) {
                        Outcome.quit(Outcome.Type.WA,
                                     "The size of the component of number %d " +
                                     "starting in vertex %d is wrong: " +
                                     "expected %d, found %d",
                                     g.vertexColors[v] + 1, v + 1,
                                     componentSize, size);
                    }
                }
            }
            if (ans.nextInt() != -1) {
                return new Outcome(Outcome.Type.OK, String.format("N = %d, K = %d", n, k));
            } else {
                return new Outcome(Outcome.Type.FAIL, "Jury says Impossible while contestant found an answer");
            }
        } else {
            if (ans.nextInt() == -1) {
                return new Outcome(Outcome.Type.OK, "Impossible");
            } else {
                return new Outcome(Outcome.Type.WA, "Contestant says Impossible while the answer exists");
            }
        }
    }
}

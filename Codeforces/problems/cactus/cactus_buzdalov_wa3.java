import java.io.*;
import java.util.*;

public class cactus_buzdalov_wa3 {
    static class IntReader implements Closeable {
        private final BufferedReader in;

        public IntReader(String filename) throws IOException {
            in = new BufferedReader(new FileReader(filename));
        }

        public int nextInt() throws IOException {
            int ch, rv = 0;
            while ((ch = in.read()) <= ' ');
            rv = ch - '0';
            while ((ch = in.read()) >= '0' && ch <= '9') {
                rv = 10 * rv + ch - '0';
            }
            return rv;
        }

        @Override
        public void close() throws IOException {
            in.close();
        }
    }

    static class Vertex {
        public final int index;
        public List<Vertex> children = new ArrayList<Vertex>(4);
        public List<Cycle> cycles = new ArrayList<Cycle>(2);
        public int subtreeSize;
        public boolean entered = false;
        public boolean exited = false;
        public Vertex(int index) {
            this.index = index;
        }
    }

    static class Cycle {
        public final Vertex parent;
        public final List<Vertex> children = new ArrayList<Vertex>();
        public int childrenSize;
        public Cycle(Vertex parent) {
            this.parent = parent;
        }
    }

    static class DSDS {
        int[] p;
        int[] r;
        public DSDS(int n) {
            p = new int[n];
            r = new int[n];
            for (int i = 0; i < n; ++i) {
                p[i] = i;
            }
        }
        public int get(int t) {
            return p[t] == t ? t : (p[t] = get(p[t]));
        }
        public void unite(int a, int b) {
            a = get(a);
            b = get(b);
            if (a != b) {
                if (r[a] == r[b]) {
                    ++r[a];
                }
                if (r[a] > r[b]) {
                    p[b] = a;
                } else {
                    p[a] = b;
                }
            }
        }
    }

    static Vertex[] vertices;
    static int n, k, compSize;

    static Cycle buildCactus(int index, int parent, List<List<Integer>> edges) {
        Vertex v = vertices[index];
        v.entered = true;
        Cycle toReturn = null;
        for (int next : edges.get(index)) {
            if (next != parent) {
                if (!vertices[next].entered) {
                    Cycle rec = buildCactus(next, index, edges);
                    if (rec == null) {
                        v.children.add(vertices[next]);
                    } else {
                        if (rec.parent != v) {
                            toReturn = rec;
                            rec.children.add(v);
                        } else {
                            v.cycles.add(rec);
                        }
                    }
                } else if (!vertices[next].exited) {
                    toReturn = new Cycle(vertices[next]);
                    toReturn.children.add(v);
                }
            }
        }
        v.exited = true;
        return toReturn;
    }

    static class BlockEvent implements Comparable<BlockEvent> {
        public int index;
        public int action;
        public int compareTo(BlockEvent that) {
            return index - that.index;
        }
    }

    static BlockEvent[] events;

    static boolean colorCycle(Cycle c, DSDS ds) {
        c.childrenSize = 0;

        for (Vertex v : c.children) {
            if (!colorGraph(v, ds)) {
                return false;
            }
        }

        int eventCount = 2;
        events[0].index = -1;
        events[0].action = 0;
        events[1].index = compSize;
        events[1].action = 0;

        for (Vertex v : c.children) {
            int om = c.childrenSize;
            c.childrenSize = (c.childrenSize + v.subtreeSize) % compSize;
            int nm = c.childrenSize;
            /** BUG IS HERE **/
            if (v.subtreeSize > 1 && compSize != 1) {
                om = (om + 1) % compSize;
                nm = (nm + compSize - 1) % compSize;
                events[eventCount].index = om;
                events[eventCount++].action = 1;
                events[eventCount].index = nm;
                events[eventCount++].action = -1;
                if (om > nm) {
                    events[0].action += 1;
                    events[1].action -= 1;
                }
            }
        }
        {
            int om = c.childrenSize;
            int nm = 0;
            if (c.childrenSize + 1 != compSize && compSize != 1) {
                om = (om + 1) % compSize;
                nm = (nm + compSize - 1) % compSize;
                events[eventCount].index = om;
                events[eventCount++].action = 1;
                events[eventCount].index = nm;
                events[eventCount++].action = -1;
                if (om > nm) {
                    events[0].action += 1;
                    events[1].action -= 1;
                }
            }
        }

        Arrays.sort(events, 0, eventCount);
        int cutPoint = -1;
        for (int e = 0, b = 0; e < eventCount; ++e) {
            b += events[e].action;
            if (b == 0 && e + 1 < eventCount && events[e].index + 1 < events[e + 1].index) {
                cutPoint = events[e].index + 1;
                break;
            }
        }
        if (cutPoint == -1) {
            return false;
        } else {
            int mod = 0;
            for (int i = 0, s = c.children.size(); i <= s; ++i) {
                Vertex prev = i == 0 ? c.parent : c.children.get(i - 1);
                Vertex next = i == s ? c.parent : c.children.get(i);
                if (cutPoint != mod) {
                    ds.unite(prev.index, next.index);
                }
                if (i < s) {
                    mod = (mod + next.subtreeSize) % compSize;
                }
            }
            return true;
        }
    }

    static boolean colorGraph(Vertex curr, DSDS ds) {
        curr.subtreeSize = 1;
        for (Cycle c : curr.cycles) {
            if (!colorCycle(c, ds)) {
                return false;
            }
            curr.subtreeSize += c.childrenSize;
        }
        for (Vertex v : curr.children) {
            if (!colorGraph(v, ds)) {
                return false;
            }
            if (v.subtreeSize != 0) {
                curr.subtreeSize += v.subtreeSize;
                ds.unite(curr.index, v.index);
            }
        }
        if (curr.subtreeSize > compSize) {
            return false;
        }
        curr.subtreeSize %= compSize;
        return true;
    }

    public static void main(String[] args) throws IOException {
        IntReader in = new IntReader("cactus.in");
        n = in.nextInt();
        int m = in.nextInt();
        k = in.nextInt();
        compSize = n / k;
        List<List<Integer>> edges = new ArrayList<List<Integer>>();
        for (int i = 0; i < n; ++i) {
            edges.add(new ArrayList<Integer>());
        }
        for (int path = 0; path < m; ++path) {
            int len = in.nextInt();
            int prev = in.nextInt() - 1;
            for (int i = 1; i < len; ++i) {
                int curr = in.nextInt() - 1;
                edges.get(curr).add(prev);
                edges.get(prev).add(curr);
                prev = curr;
            }
        }
        in.close();

        events = new BlockEvent[2 * n + 2];
        for (int i = 0; i < events.length; ++i) {
            events[i] = new BlockEvent();
        }
        vertices = new Vertex[n];
        for (int i = 0; i < n; ++i) {
            vertices[i] = new Vertex(i);
        }

        buildCactus(0, -1, edges);
        DSDS ds = new DSDS(n);

        PrintWriter out = new PrintWriter("cactus.out");
        if (colorGraph(vertices[0], ds) && vertices[0].subtreeSize == 0) {
            Map<Integer, List<Integer>> answer = new HashMap<Integer, List<Integer>>();
            for (int i = 0; i < n; ++i) {
                int id = ds.get(i);
                List<Integer> comp = answer.get(id);
                if (comp == null) {
                    answer.put(id, comp = new ArrayList<Integer>());
                }
                comp.add(i + 1);
            }
            for (List<Integer> comp : answer.values()) {
                Collections.sort(comp);
                for (int i = 0; i < comp.size(); ++i) {
                    out.print(comp.get(i));
                    if (i == comp.size() - 1) {
                        out.println();
                    } else {
                        out.print(" ");
                    }
                }
            }
        } else {
            out.println(-1);
        }
        out.close();
    }
}

import java.io.*;
import java.util.*;

/**
 * NEERC 2010
 * Test generator for problem Cactus Revolution.
 *
 * @author Maxim Buzdalov
 */
public class Tests {
	static int nTests = 0;
	static int MAX_N = 50000;
	static int MAX_PATH_LENGTH = 1000;
	static int MAX_PATH_COUNT = 10000;
	static Random random = new Random(45345654);
	static final File LST_FILE = new File("tests/tests.lst");

	static class VertexWithDegree implements Comparable<VertexWithDegree> {
		final int index;
		int degree;

		public VertexWithDegree(int index, int degree) {
			this.index = index;
			this.degree = degree;
		}

		public int compareTo(VertexWithDegree vwd) {
			if (degree != vwd.degree) return degree - vwd.degree;
			return index - vwd.index;
		}
	}

	static class Graph {
		public int nVertices = 1;
		public List<Set<Integer>> edges = new ArrayList<Set<Integer>>();

		{
			edges.add(new HashSet<Integer>());
		}

		public Graph() {
		}

		public Graph(int[]... paths) {
			for (int[] p : paths) {
				for (int i = 1; i < p.length; ++i) {
					addEdge(p[i - 1], p[i]);
				}
			}
		}

		public void addEdge(int a, int b) {
			while (edges.size() <= Math.max(a, b)) {
				edges.add(new HashSet<Integer>());
			}
			if (edges.get(a).contains(b))
				throw new AssertionError("The edge (" + a + "--" + b + ") is alreay contained");
			if (edges.get(b).contains(a))
				throw new AssertionError("The edge (" + a + "--" + b + ") is alreay contained");
			edges.get(a).add(b);
			edges.get(b).add(a);
			nVertices = Math.max(nVertices, 1 + Math.max(a, b));
		}

		public void dfs(int vertex, boolean[] used) {
			used[vertex] = true;
			for (int next : edges.get(vertex)) {
				if (!used[next]) {
					dfs(next, used);
				}
			}
		}

		public boolean checkConnectivity() {
			boolean[] used = new boolean[nVertices];
			dfs(0, used);
			for (boolean t : used) {
				if (!t) return false;
			}
			return true;
		}

		public List<List<Integer>> extractPaths(int maxPathLength) {
			List<Set<Integer>> edgeCopy = new ArrayList<Set<Integer>>(edges.size());
			for (Set<Integer> e : edges) {
				edgeCopy.add(new HashSet<Integer>(e));
			}
			VertexWithDegree[] vs = new VertexWithDegree[nVertices];
			TreeSet<VertexWithDegree> vertices = new TreeSet<VertexWithDegree>();
			for (int i = 0; i < nVertices; ++i) {
				vs[i] = new VertexWithDegree(i, edgeCopy.get(i).size());
				if (vs[i].degree > 0) {
					vertices.add(vs[i]);
				}
			}
			List<List<Integer>> paths = new ArrayList<List<Integer>>();
			while (!vertices.isEmpty()) {
				List<Integer> curr = new ArrayList<Integer>();
				paths.add(curr);
				int v = vertices.first().index;
				curr.add(v);
				while (curr.size() < maxPathLength && vs[v].degree > 0) {
					int next = edgeCopy.get(v).iterator().next();
					edgeCopy.get(v).remove(next);
					edgeCopy.get(next).remove(v);
					vertices.remove(vs[v]);
					vertices.remove(vs[next]);
					if (--vs[v].degree > 0) {
						vertices.add(vs[v]);
					}
					if (--vs[next].degree > 0) {
						vertices.add(vs[next]);
					}
					v = next;
					curr.add(v);
				}
			}
			return paths;
		}
	}

	static void writeDesc(String desc) throws IOException {
		PrintWriter out = new PrintWriter(new FileWriter(LST_FILE, true));
		out.printf("%02d %s%n", nTests, desc);
		out.close();
	}

	static void writeGraph(String desc, Graph g, int k, boolean checkOnly) {
		if (g.nVertices > MAX_N) throw new AssertionError("nVertices = " + g.nVertices + " > " + MAX_N);
		if (g.nVertices % k != 0) throw new AssertionError("Divisibility does not hold: N = " + g.nVertices + " k = " + k);
		if (!g.checkConnectivity()) throw new AssertionError("The graph is not connected");
		List<List<Integer>> paths = g.extractPaths(MAX_PATH_LENGTH);
		if (paths.size() > MAX_PATH_COUNT) throw new AssertionError("Path count exceeded: " + paths.size());

		if (checkOnly) return;

		try {
			new File("tests").mkdir();
			PrintWriter out = new PrintWriter(String.format("tests/%02d", ++nTests));
			writeDesc(desc);
			out.println(g.nVertices + " " + paths.size() + " " + k);
			for (List<Integer> p : paths) {
				out.print(p.size());
				for (int i : p) {
					out.print(" ");
					out.print(i + 1);
				}
				out.println();
			}
			out.close();
			System.out.printf("Test %02d written: %s%n", nTests, desc);
		} catch (IOException ex) {
			ex.printStackTrace();
			System.exit(1);
		}
	}

	static void writeExactPaths(String desc, int k, int[]... paths) {
		Graph g = new Graph(paths);
		writeGraph("", g, k, true);
		try {
			new File("tests").mkdir();
			PrintWriter out = new PrintWriter(String.format("tests/%02d", ++nTests));
			writeDesc(desc);
			out.println(g.nVertices + " " + paths.length + " " + k);
			for (int[] p : paths) {
				out.print(p.length);
				for (int i : p) {
					out.print(" ");
					out.print(i + 1);
				}
				out.println();
			}
			out.close();
			System.out.printf("Test %02d written (exact paths): %s%n", nTests, desc);
		} catch (IOException ex) {
			ex.printStackTrace();
			System.exit(1);
		}
	}

	static void writePaths(String desc, int k, int[]... paths) {
		Graph g = new Graph();
		for (int[] p : paths) {
			for (int i = 1; i < p.length; ++i) {
				g.addEdge(p[i - 1], p[i]);
			}
		}
		writeGraph(desc, g, k, false);
	}

	static int[] p(int... path) {
		return path;
	}

	static int[] randomPermutation(int n) {
		Integer[] t = new Integer[n];
		for (int i = 0; i < n; ++i) {
			t[i] = i;
		}
		Collections.shuffle(Arrays.asList(t), random);
		int[] rv = new int[n];
		for (int i = 0; i < n; ++i) {
			rv[i] = t[i];
		}
		return rv;
	}

	static void writeOneCycle(int n, int k) {
		Graph g = new Graph();
		int[] rp = randomPermutation(n);
		for (int i = 0; i < n; ++i) {
			g.addEdge(rp[i], rp[(i + 1) % n]);
		}
		writeGraph(String.format("OneCycle n=%d, k=%d", n, k), g, k, false);
	}

	static void writeTriangleChain(int len1, int len2, int k) {
		Graph g = new Graph();
		for (int i = 1; i < len1; ++i) {
			g.addEdge(i - 1, i);
		}
		for (int i = 0; i < len2; ++i) {
			g.addEdge(i, len1 + i);
			g.addEdge(len1 + i, i + 1);
		}
		writeGraph(String.format("TriangleChain len1=%d, len2=%d, k=%d", len1, len2, k), g, k, false);
	}

	static void writeChain(int n, int k) {
		Graph g = new Graph();
		for (int i = 1; i < n; ++i) {
			g.addEdge(i - 1, i);
		}
		writeGraph(String.format("Chain n=%d, k=%d", n, k), g, k, false);
	}

	static void writeAntiWA4(int n, int k) {
		int[] rp = randomPermutation(n + n / k);
		Graph g = new Graph();
		for (int i = 1; i < n; ++i) {
			g.addEdge(rp[i - 1], rp[i]);
		}
		g.addEdge(rp[n - 1], rp[n - n / k - 1]);
		g.addEdge(rp[n - 1], rp[rp.length - 1]);
		g.addEdge(rp[n - 2], rp[rp.length - 2]);
		for (int i = 2; i < n / k; ++i) {
			g.addEdge(rp[rp.length - i - 1], rp[rp.length - i]);
		}
		writeGraph(String.format("AnitWA4 n=%d, k=%d", n, k), g, k + 1, false);
	}

	static void randomTriangleTest(int n, int k) {
		int x = (n - 4) / 2;
		n = 4 + 2 * x;
		Graph g = new Graph(new int[]{0, 1, 2, 0});
		for (int i = 1; i <= x; ++i) {
			int rnd = random.nextInt(2 * i + 1);
			g.addEdge(rnd, 2 * i + 1);
			g.addEdge(rnd, 2 * i + 2);
			g.addEdge(2 * i + 1, 2 * i + 2);
		}
		g.addEdge(random.nextInt(n - 1), n - 1);
		writeGraph(String.format("Triangle n=%d, k=%d", n, k), g, k, false);
	}

	static void simplePenicillum(int cycleLength, int nPenicillum, int k) {
		int[] p = randomPermutation(cycleLength + nPenicillum);
		Graph g = new Graph();
		for (int i = 0; i < cycleLength; ++i) {
			g.addEdge(p[i], p[(i + 1) % cycleLength]);
		}
		for (int i = 0; i < nPenicillum; i += 2) {
			int x = random.nextInt(cycleLength);
			g.addEdge(p[x], p[cycleLength + i]);
			g.addEdge(p[x], p[cycleLength + i + 1]);
			g.addEdge(p[cycleLength + i], p[cycleLength + i + 1]);
		}
		writeGraph(String.format("SimplePenicillum cycleLength=%d, nPencillum=%d, k=%d", cycleLength, nPenicillum, k),
				g, k, false);
	}

	static void writeBigCycleAndPenicillum(int cycleLength, int nPenicillum, int k) {
		int[] p = randomPermutation(cycleLength + nPenicillum);
		Graph g = new Graph();
		for (int i = 0; i < cycleLength; ++i) {
			g.addEdge(p[i], p[(i + 1) % cycleLength]);
		}
		int idx = cycleLength;
		while (nPenicillum > 0) {
			int cnt = random.nextInt(nPenicillum) + 1;
			if (cnt == 1) {
				g.addEdge(p[random.nextInt(cycleLength)], p[idx]);
			} else {
				for (int i = 1; i < cnt; ++i) {
					g.addEdge(p[idx + i - 1], p[idx + i]);
				}
				int pnt = random.nextInt(cycleLength);
				g.addEdge(p[idx], p[pnt]);
				if (random.nextBoolean()) {
					g.addEdge(p[idx + cnt - 1], p[pnt]);
				}
			}
			idx += cnt;
			nPenicillum -= cnt;
		}
		writeGraph(String.format("BigCycleAndPenicillum cycleLength=%d, nPencillum=%d, k=%d", cycleLength, nPenicillum, k),
				g, k, false);
	}

    static void generateTrickyIntervals1(int cs) {
        Graph g = new Graph();
        int prevVertex = 1;
        int xmod = random.nextInt(cs - 1) + 1;
        g.addEdge(0, 1);
        do {
            int size = random.nextInt(cs);
            int lim = size == 0 ? cs : size;
            int nextVertex = prevVertex + 1;
            for (int i = 0; i < lim - 1; ++i) {
                if (nextVertex % cs == xmod) {
                    break;
                }
                g.addEdge(nextVertex - 1, nextVertex);
                ++nextVertex;
            }
            if (nextVertex % cs == 0) {
                g.addEdge(prevVertex, 0);
            } else {
                g.addEdge(prevVertex, nextVertex);
            }
            prevVertex = nextVertex;
        } while (prevVertex % cs != 0);
        writeGraph(String.format("TrickyIntervals (lines) n = %d compSize = %d", g.nVertices, cs), g, g.nVertices / cs, false);
    }

    static void generateTrickyIntervals2(int cs) {
        Graph g = new Graph();
        int prevVertex = 1;
        int xmod = random.nextInt(cs - 1) + 1;
        g.addEdge(0, 1);
        do {
            int size = random.nextInt(cs);
            int lim = size == 0 ? cs : size;
            int nextVertex = prevVertex + 1;
            for (int i = 0; i < lim - 1; ++i) {
                if (nextVertex % cs == xmod) {
                    break;
                }
                g.addEdge(nextVertex - 1, nextVertex);
                ++nextVertex;
            }
            if (prevVertex + 2 < nextVertex) {
                g.addEdge(nextVertex - 1, prevVertex);
            }
            if (nextVertex % cs == 0) {
                g.addEdge(prevVertex, 0);
            } else {
                g.addEdge(prevVertex, nextVertex);
            }
            prevVertex = nextVertex;
        } while (prevVertex % cs != 0);
        writeGraph(String.format("TrickyIntervals (cycles) n = %d compSize = %d", g.nVertices, cs), g, g.nVertices / cs, false);
    }

    static void writeDegreeExceeded(int n, int k) {
        int[] perm = randomPermutation(n);
        Graph g = new Graph();
        for (int i = 1; i < 2 * k; ++i) {
            g.addEdge(perm[0], perm[i]);
        }
        for (int i = 2 * k, j = 0; i < n; ++i) {
            g.addEdge(perm[j], perm[i]);
            j = i;
        }
        writeGraph(String.format("DegreeExceeded n = %d, k = %d", n, k), g, k, false);
    }

	static int randomDivisor(int x) {
		while (true) {
			int d = random.nextInt(x - 1) + 2;
			if (x % d == 0) return d;
		}
	}

	public static void main(String[] args) throws IOException {
		LST_FILE.delete();
		//01
		writeExactPaths("first sample", 3,
				p(0, 1, 2, 3, 4, 5, 6, 7, 2),
				p(1, 8, 9, 10, 11, 12, 9),
				p(1, 13, 8, 14, 9));
		//02
		writeExactPaths("second sample", 2, p(0, 1, 2), p(1, 3));
		//03
		writePaths("one vertex", 1);
		//04
		writePaths("two vertices 0-1", 1, p(0, 1));
		//05
		writePaths("two vertices 1-0", 2, p(1, 0));
		//06
		writePaths("triangle 0-1-2-0", 1, p(0, 1, 2, 0));
		//07
		writePaths("triangle 0-2-1-0", 3, p(0, 2, 1, 0));
		//08
		writePaths("hand-made", 3,
				p(0, 1, 2, 3, 4),
				p(5, 6, 7, 8),
				p(3, 6), p(1, 7));
		//09
		writePaths("hand-made", 7, p(0, 1, 2, 3, 8, 9, 10, 11, 12, 13, 4, 5), p(6, 5, 7));
		//10
		writePaths("hand-made", 4, p(0, 1, 2, 3, 4, 5), p(5, 6, 7));
		//11
		writePaths("hand-made", 3, p(0, 1, 2, 3, 4, 2, 7, 5, 6, 7, 8, 0));
		//12
		writePaths("hand-made anti-RE", 3, p(2, 1, 0, 8, 3, 1), p(3, 4, 5, 6, 7, 4));
		//13..20
		for (int times = 13, cso = 0; times <= 20; ++times, ++cso) {
		    generateTrickyIntervals1(random.nextInt(10 * (3 * cso + 1)) + 1);
		}
		//21..25
		for (int times = 21, cso = 0; times <= 25; ++times, ++cso) {
		    generateTrickyIntervals2(random.nextInt(10 * (5 * cso + 1)) + 1);
		}
		//26..30
		for (int test = 56; test <= 60; ++test) {
		    writeDegreeExceeded((test - 10) * 1000, (test - 10) * 10);
		}
		//31..36
		writeChain(100, 1);
		writeChain(21 * 21, 21);
		writeChain(113, 113);
		writeChain(MAX_N, MAX_N);
		writeChain(MAX_N, randomDivisor(MAX_N));
		writeChain(MAX_N, 1);
		//37..42
		writeOneCycle(100, 1);
		writeOneCycle(41 * 17, 41);
		writeOneCycle(239, 239);
		writeOneCycle(MAX_N, MAX_N);
		writeOneCycle(MAX_N, randomDivisor(MAX_N));
		writeOneCycle(MAX_N, 1);
		//43..47
		writeTriangleChain(100, 98, 2);
		writeTriangleChain(101, 100, 3);
		writeTriangleChain(MAX_N / 2 + 1, MAX_N / 2 - 1, 2);
		writeTriangleChain(MAX_N / 2, MAX_N / 2 - 1, MAX_N - 1);
		writeTriangleChain(MAX_N / 2 - 1, MAX_N / 2 - 3, randomDivisor(MAX_N - 4));
		//48..53
		for (int test = 48; test <= 50; ++test) {
    		writeAntiWA4(8921 * (test - 45), 8921);
		}
		for (int test = 51; test <= 53; ++test) {
    		writeAntiWA4(6172 * (test - 45), 6172);
		}
		//54..56
		randomTriangleTest(MAX_N, 2);
		randomTriangleTest(MAX_N, randomDivisor(MAX_N));
		randomTriangleTest(MAX_N, MAX_N / 2);
		//57..60
		int mn = (MAX_N / 3) * 3;
		writeBigCycleAndPenicillum(3 * MAX_N / 4, MAX_N / 4, randomDivisor(MAX_N));
		writeBigCycleAndPenicillum(2 * mn / 3, mn / 3, 3);
		writeBigCycleAndPenicillum(3 * MAX_N / 4, MAX_N / 4, 2);
		simplePenicillum(3 * MAX_N / 4, MAX_N / 4, MAX_N / 2);
		//61..70
		long[] seeds = {
             2226861971064629152L,
            -2832785353362038500L,
            -6876602688646264131L,
             3964041828427475130L,
             7611464926608697184L,
            -7139336543207181995L,
             -624544712540808086L,
              514579434522028778L,
            -3615143344253293305L,
            -2930983803661830815L,
        };
        for (long seed : seeds) {
            random = new Random(seed);
            generateTrickyIntervals2(random.nextInt(250) + 5);
        }
	}
}

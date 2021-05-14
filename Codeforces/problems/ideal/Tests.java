import java.io.*;
import java.util.*;

public class Tests {
	private static final File TESTS_LST = new File("tests/tests.lst");

	int testNo = 1;

	public void printTest(String description, int n, Edge[] e) {
		System.err.printf("Creating test %02d: %s%n", testNo, description);
		appendDescription(description);

		PrintWriter out = null;
		try {
			out = new PrintWriter("tests/" + testNo / 10 + testNo % 10);
		} catch (FileNotFoundException ex) {
			ex.printStackTrace();
			return;
		}

		out.println(n + " " + e.length);
		for (int i = 0; i < e.length; i++) {
			out.println(e[i].a + " " + e[i].b + " " + e[i].c);
		}

		out.close();
		testNo++;
	}

	private void appendDescription(String description) {
		try {
			PrintWriter lst = new PrintWriter(new OutputStreamWriter(new FileOutputStream(TESTS_LST, true)));
			lst.printf("%02d %s%n", testNo, description);
			lst.close();
		} catch (FileNotFoundException ex) {
			ex.printStackTrace();
		}
	}

	class Edge {
		int a;
		int b;
		int c;

		Edge(int a, int b, int c) {
			this.a = a;
			this.b = b;
			this.c = c;
		}
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

	Edge[] createEdges(String s) {
		StringTokenizer st = new StringTokenizer(s, " ,\n");
		Edge[] r = new Edge[st.countTokens() / 3];
		for (int i = 0; i < r.length; i++) {
			r[i] = new Edge(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
		}
		return r;
	}

	Edge[] createRandomTest(int n, int l, int m, int maxc) {
		int[] level = new int[n];
		Arrays.fill(level, -1);
		int[] vertex = new int[l];
		for (int i = 0; i < l; i++) {
			int x;
			do {
				if (i == 0) {
					x = 0;
				} else if (i == l - 1) {
					x = n - 1;
				} else {
					x = rnd.nextInt(n - 2) + 1;
				}
			} while (level[x] != -1);
			level[x] = i;
			vertex[i] = x;
		}
		for (int i = 0; i < n; i++) {
			if (level[i] == -1) {
				level[i] = rnd.nextInt(l);
			}
		}

		ArrayList<Integer>[] a = new ArrayList[l];
		for (int i = 0; i < l; i++) {
			a[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < n; i++) {
			a[level[i]].add(i);
		}

		ArrayList<Edge> edges = new ArrayList<Edge>();
		for (int i = 0; i < l - 1; i++) {
			edges.add(new Edge(vertex[i], vertex[i + 1], rnd.nextInt(maxc) + 1));
			m--;
		}
		while (m > 0) {
			if (rnd.nextBoolean()) {
				int j = rnd.nextInt(l - 1);
				int u = a[j].get(rnd.nextInt(a[j].size()));
				int v = a[j + 1].get(rnd.nextInt(a[j + 1].size()));
				edges.add(new Edge(u, v, rnd.nextInt(maxc) + 1));
			} else {
				int j = rnd.nextInt(l);
				int u = a[j].get(rnd.nextInt(a[j].size()));
				int v = a[j].get(rnd.nextInt(a[j].size()));
				edges.add(new Edge(u, v, rnd.nextInt(maxc) + 1));
			}
			m--;
		}

		for (Edge e : edges) {
			e.a++;
			e.b++;
		}

		Collections.shuffle(edges, rnd);

		return edges.toArray(new Edge[edges.size()]);
	}

	Edge[] createLongTailTest(int n, int l) {
		ArrayList<Edge> edges = new ArrayList<Edge>();
		for (int i = 1; i <= n - l - 2; i++) {
			edges.add(new Edge(0, i, 1));
			edges.add(new Edge(i, n - l - 2 + 1, 1));
		}
		for (int i = n - l - 2 + 1; i < n - 1; i++) {
			edges.add(new Edge(i, i + 1, rnd.nextInt(10) + 1));
		}

		int[] p = new int[n];
		p[0] = 0;
		p[n - 1] = n - 1;
		for (int i = 1; i < n - 1; i++) {
			int j = rnd.nextInt(i) + 1;
			p[i] = p[j];
			p[j] = i;
		}

		for (Edge e : edges) {
			e.a = p[e.a] + 1;
			e.b = p[e.b] + 1;
		}

		Collections.shuffle(edges, rnd);

		return edges.toArray(new Edge[edges.size()]);
	}

	Edge[] createDiagonalSquareTest(int l, int m) {
		int n = l * m + 2;
		ArrayList<Edge> edges = new ArrayList<Edge>();
		for (int i = 1; i <= l; i++) {
			edges.add(new Edge(0, i, 1));
		}
		for (int i = 0; i < m - 1; i++) {
			for (int j = 1; j <= l; j++) {
				edges.add(new Edge(i * l + j, (i + 1) * l + j, 1));
				edges.add(new Edge(i * l + j, (i + 1) * l + j % l + 1, 1));
			}
		}
		for (int i = 1; i <= l; i++) {
			edges.add(new Edge(l * (m - 1) + i, n - 1, rnd.nextInt(m) + 1));
		}

		int[] p = new int[n];
		p[0] = 0;
		p[n - 1] = n - 1;
		for (int i = 1; i < n - 1; i++) {
			int j = rnd.nextInt(i) + 1;
			p[i] = p[j];
			p[j] = i;
		}

		for (Edge e : edges) {
			e.a = p[e.a] + 1;
			e.b = p[e.b] + 1;
			if (rnd.nextBoolean()) {
				int t = e.a;
				e.a = e.b;
				e.b = t;
			}
		}

		Collections.shuffle(edges, rnd);

		return edges.toArray(new Edge[edges.size()]);
	}

	Edge[] createRandomizedSquareTest(int l, int m) {
		int n = l * m + 2;
		ArrayList<Edge> edges = new ArrayList<Edge>();
		for (int i = 1; i <= l; i++) {
			edges.add(new Edge(0, i, 1));
		}
		for (int i = 0; i < m - 1; i++) {
			for (int j = 1; j <= l; j++) {
				edges.add(new Edge(i * l + j, (i + 1) * l + j, 1));
				edges.add(new Edge(i * l + j, (i + 1) * l + rnd.nextInt(l) + 1 + 1, 1));
			}
		}
		for (int i = 1; i <= l; i++) {
			edges.add(new Edge(l * (m - 1) + i, n - 1, rnd.nextInt(m) + 1));
		}

		int[] p = new int[n];
		p[0] = 0;
		p[n - 1] = n - 1;
		for (int i = 1; i < n - 1; i++) {
			int j = rnd.nextInt(i) + 1;
			p[i] = p[j];
			p[j] = i;
		}

		for (Edge e : edges) {
			e.a = p[e.a] + 1;
			e.b = p[e.b] + 1;
			if (rnd.nextBoolean()) {
				int t = e.a;
				e.a = e.b;
				e.b = t;
			}
		}

		Collections.shuffle(edges, rnd);

		return edges.toArray(new Edge[edges.size()]);
	}

	Edge[] createRandomizedWideSquareTest(int l, int m, int r) {
		int n = l * m + 2;
		ArrayList<Edge> edges = new ArrayList<Edge>();
		for (int i = 1; i <= l; i++) {
			edges.add(new Edge(0, i, 1));
		}
		for (int i = 0; i < m - 1; i++) {
			for (int j = 1; j <= l; j++) {
				edges.add(new Edge(i * l + j, (i + 1) * l + j, 1));
				for (int k = 0; k < r - 1; k++) {
					edges.add(new Edge(i * l + j, (i + 1) * l + rnd.nextInt(l) + 1 + 1, 1));
				}
			}
		}
		for (int i = 1; i <= l; i++) {
			edges.add(new Edge(l * (m - 1) + i, n - 1, rnd.nextInt(m) + 1));
		}

		int[] p = new int[n];
		p[0] = 0;
		p[n - 1] = n - 1;
		for (int i = 1; i < n - 1; i++) {
			int j = rnd.nextInt(i) + 1;
			p[i] = p[j];
			p[j] = i;
		}

		for (Edge e : edges) {
			e.a = p[e.a] + 1;
			e.b = p[e.b] + 1;
			if (rnd.nextBoolean()) {
				int t = e.a;
				e.a = e.b;
				e.b = t;
			}
		}

		Collections.shuffle(edges, rnd);

		return edges.toArray(new Edge[edges.size()]);
	}


	final static int MAXN = 100000;
	final static int MAXM = 100000;
	final static int MAXC = 1000000000;

	public void run() {
		new File("tests").mkdir();
		TESTS_LST.delete();

		printTest("first sample", 4, createEdges(
				"1 2 1\n" +
						"1 3 2\n" +
						"3 4 3\n" +
						"2 3 1\n" +
						"2 4 4\n" +
						"3 1 1"));

		printTest("smallest", 2, createEdges(
				"1 2 1\n"
		));

		printTest("smallest in rev", 2, createEdges(
				"2 1 1\n"
		));

		printTest("two edges", 3, createEdges(
				"1 2 1\n" +
						"2 3 1"
		));

		printTest("four edges", 4, createEdges(
				"1 2 1 1 3 1 2 4 3 3 4 2"
		));

		printTest("LongTailTest(20, 10)", 20, createLongTailTest(20, 10));
		printTest("createDiagonalSquareTest(6, 5)", 6 * 5 + 2, createDiagonalSquareTest(6, 5));

		for (int i = 0; i < 20; i++) {
			int n = 20 + rnd.nextInt(81);
			int m = n + rnd.nextInt(100);
			printRandomTest(n, rnd.nextInt(n - 2) + 2, m, rnd.nextInt(10) + 1);
		}

		printTest("LongTailTest(100000, 50000)", 100000, createLongTailTest(100000, 50000));
		printTest("DiagonalSquareTest(316, 316)", 316 * 316 + 2, createDiagonalSquareTest(316, 316));
		printTest("RandomizedSquareTest(316, 316)", 316 * 316 + 2, createRandomizedSquareTest(316, 316));
		printTest("RandomizedWideSquareTest(100, 100, 5)", 100 * 100 + 2, createRandomizedWideSquareTest(100, 100, 5));
		printTest("RandomizedWideSquareTest(100, 100, 20)", 100 * 100 + 2, createRandomizedWideSquareTest(100, 100, 20));

		printRandomTest(100000, 1000, 100000, 50);
		printRandomTest(100000, 1000, 100000, 2);
		printRandomTest(100000, 100000, 99999, 2);
		printRandomTest(100000, 100000, 99999, 1000000000);
		printRandomTest(100000, 2, 200000, 1000000000);
		printRandomTest(100000, 2, 200000, 100000);
		printRandomTest(100000, 2, 200000, 1000000);
		printRandomTest(100000, 2, 200000, 2);
		for (int i = 0; i < 7; i++) {
			int n = 50000 + rnd.nextInt(50001);
			int m = n + rnd.nextInt(100001);
			printRandomTest(n, rnd.nextInt(10) + 2, m, rnd.nextInt(10) + 1);
			printRandomTest(n, rnd.nextInt(100) + 2, m, rnd.nextInt(10) + 1);
			printRandomTest(n, rnd.nextInt(10000) + 2, m, rnd.nextInt(10) + 1);
			printRandomTest(n, rnd.nextInt(10) + 2, m, rnd.nextInt(1000) + 1);
			printRandomTest(n, rnd.nextInt(100) + 2, m, rnd.nextInt(1000) + 1);
			printRandomTest(n, rnd.nextInt(10000) + 2, m, rnd.nextInt(1000) + 1);
		}
		printTest("one edge with max color", 2, createEdges(
				"1 2 1000000000\n"
		));
		printRandomTest(2, 2, 200000, 1000000000);
	}

	private void printRandomTest(int n, int l, int m, int maxc) {
		printTest(String.format("RandomTest(%d, %d ,%d, %d)", n, l, m, maxc),
				n, createRandomTest(n, l, m, maxc));
	}

	public static void main(String[] args) {
		new Tests().run();
	}
}

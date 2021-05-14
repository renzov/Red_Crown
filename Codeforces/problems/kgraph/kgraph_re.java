import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem K: K-Graph Oddity.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class kgraph_re {
	private static final int MAX_N = 9999;
	private static final int MAX_M = 100000;

	public static void main(String[] args) throws Exception {
		new kgraph_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;
	int m;
	HashMap<Integer, Set<Integer>> edges = new HashMap<Integer, Set<Integer>>();

	void read() throws Exception {
		Scanner in = new Scanner(new File("kgraph.in"));
		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();
		assert n >= 3 && n <= MAX_N && n % 2 != 0;
		assert m >= 2 && m <= MAX_M;
		for (int i = 0; i < m; i++) {
			int a = in.nextInt();
			int b = in.nextInt();
			in.nextLine();
			assert a >= 1 && a <= n;
			assert b >= 1 && b <= n;
			assert a != b;
			add(a, b);
			add(b, a);
		}
		in.close();
	}

	private void add(int a, int b) {
		Set<Integer> set = edges.get(a);
		if (set == null)
			edges.put(a, set = new HashSet<Integer>());
		boolean ok = set.add(b);
		assert ok;
	}

	private final class DE implements Comparable<DE> {
		final int d;
		final int e;

		private DE(int d, int e) {
			this.d = d;
			this.e = e;
		}

		public int compareTo(DE o) {
			return o.d - d;
		}
	}

	int k;
	DE[] dist;
	Queue<Integer> queue;
	int[] c;
	boolean[] s;

	void solve() {
		// vertex with minimum degree & max degree
		int dmin = Integer.MAX_VALUE;
		int dmax = 0;
		int e0 = -1;
		for (Map.Entry<Integer, Set<Integer>> entry : edges.entrySet()) {
			int d = entry.getValue().size();
			if (d < dmin) {
				dmin = d;
				e0 = entry.getKey();
			}
			dmax = Math.max(dmax, d);
		}
		k = dmax / 2 * 2 + 1;
		assert dmin < k;
		// determine distance to e0 
		dist = new DE[n + 1];
		queue = new ArrayDeque<Integer>(n);
		queue.add(e0);
		dist[e0] = new DE(0, e0);
		while (!queue.isEmpty()) {
			int e = queue.remove();
			int de = dist[e].d;
			assert edges.containsKey(e);
			for (Integer f : edges.get(e)) {
				if (dist[f] == null) {
					dist[f] = new DE(de + 1, f);
					queue.add(f);
				}
			}
		}
		// make sure graph is connected
		for (int i = 1; i <= n; i++)
			assert dist[i] != null;
		// sort by distance (max distance first)
		Arrays.sort(dist, 1, n + 1);
		assert dist[n].e == e0; // sanity check that the first node is last
		// greedy coloring by decreasing distance
		c = new int[n + 1];
		s = new boolean[k + 1];
		for (int i = 1; i <= n; i++) {
			int e = dist[i].e;
			for (Integer f : edges.get(e)) {
				s[c[f]] = true;				
			}
			int cc = 1;
			while (s[cc])
				cc++;
			c[e] = cc;
			for (Integer f : edges.get(e)) {
				s[c[f]] = false;
			}
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("kgraph.out");
		out.println(k);
		for (int i = 1; i <= n; i++)
			out.println(c[i]);
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a soulution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}

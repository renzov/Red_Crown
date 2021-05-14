import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem C: Cactus Revolution.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class cactus_re implements Runnable {
	private static final int MAX_N = 50000;
	private static final int MAX_M = 10000;
	private static final int MAX_S = 1000;

	public static void main(String[] args) throws Exception {
		new Thread(new cactus_re()).start();
	}

	public void run() {
		try {
			read();
			solve();
			write();
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}

	int n;
	int m;
	int k;
	Map<Integer, Set<Integer>> g = new HashMap<Integer, Set<Integer>>();
	
	void read() throws IOException {
		Scanner in = new Scanner(new File("cactus.in"));
		n = in.nextInt();
		m = in.nextInt();
		k = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= MAX_N;
		assert m >= 0 && m <= MAX_M;
		assert k >= 1 && k <= n;
		assert n % k == 0;
		for (int i = 0; i < m; i++) {
			int s = in.nextInt();
			assert s >= 2 && s <= MAX_S;
			int p = 0;
			for (int j = 0; j < s; j++) {
				int q = in.nextInt();
				assert q >= 1 && q <= n;
				if (p != 0) {
					assert q != p;
					add(p, q);
					add(q, p);
				}
				p = q;
			}
			in.nextLine();
		}
		in.close();
	}

	private void add(int p, int q) {
		Set<Integer> set = g.get(p);
		if (set == null)
			g.put(p, set = new HashSet<Integer>());
		boolean ok = set.add(q);
		assert ok;
	}

	static class Edge {
		final int p;
		final int q;

		Edge(int p, int q) {
			if (p > q) {
				int t = p;
				p = q;
				q = t;
			}
			this.p = p;
			this.q = q;
		}

		@Override
		public boolean equals(Object o) {
			if (this == o) return true;
			if (o == null || getClass() != o.getClass()) return false;
			Edge edge = (Edge)o;
			return p == edge.p && q == edge.q;

		}

		@Override
		public int hashCode() {
			return 31 * p + q;
		}
	}

	interface NodeVisitor {
		void visit(int node);
	}
	
	static class NodeSet {
		boolean isEmpty() { return size() == 0; }
		int size() { return 0; }
		void forAll(NodeVisitor v) { }
		CompositeSet toCompositeSet() { return new CompositeSet(); }
		NodeSet join(NodeSet other) { return other; }
	}

	static class SingletonSet extends NodeSet {
		final int node;
		SingletonSet(int node) { this.node = node; }
		int size() { return 1; }
		void forAll(NodeVisitor v) { v.visit(node); }
		CompositeSet toCompositeSet() { return new CompositeSet().addAll(this); }
		NodeSet join(NodeSet other) { return other.toCompositeSet().addAll(this); }
	}

	static class CompositeSet extends NodeSet {
		int size;
		final List<NodeSet> sets = new ArrayList<NodeSet>();
		void add(int node) { sets.add(new SingletonSet(node)); size++; }
		CompositeSet addAll(NodeSet other) { if (!other.isEmpty()) { sets.add(other); size += other.size(); } return this; }
		int size() { return size; }
		void forAll(NodeVisitor v) { for (NodeSet other : sets) other.forAll(v); }
		CompositeSet toCompositeSet() { return this; }
		NodeSet join(NodeSet other) { addAll(other); return this; }
	}

	private static final NodeSet EMPTY = new NodeSet();

	int[] stack;
	boolean[] v;
	int cc;
	int[][] cycle;
	Map<Integer, Map<Integer, Integer>> cm = new HashMap<Integer, Map<Integer, Integer>>();
	Set<Edge> cycleEdges = new HashSet<Edge>();

	int target;
	Map<Integer, Integer> rcnt = new HashMap<Integer, Integer>();
	List<List<Integer>> districts = new ArrayList<List<Integer>>(k);
	boolean found;

	void solve() {
		stack = new int[n];
		v = new boolean[n + 1];
		cycle = new int[n + 1][];
		cycles(0, 1, 0);
		for (int i = 1; i <= n; i++)
			assert v[i] : "not connected";
		target = n / k;
		NodeSet rem = split(0, 0, 1);
		found = rem != null;
		if (found)
			assert rem.isEmpty() && districts.size() == k;
	}

	private void cycles(int parent, int node, int sp) {
		if (v[node]) {
			for (int j = sp; --j >= 0;)
				if (stack[j] == node) {
					cc++;
					int n = sp - j;
					assert n >= 2;
					int[] c = cycle[cc] = new int[n];
					System.arraycopy(stack, j, c, 0, n);
					for (int k = 0; k < n; k++) {
						int q = c[k];
						Map<Integer, Integer> cim = cm.get(q); // cycle->index map
						if (cim == null)
							cm.put(q, cim = new HashMap<Integer, Integer>());
						boolean ok = cim.put(cc, k) == null;
						assert ok;
						ok = cycleEdges.add(new Edge(q, c[(k + 1) % n]));
						assert ok : "edge on two loops - not a cactus";
					}
					return;
				}
			throw new AssertionError("horizontal edge - not a cactus");
		}
		v[node] = true;
		stack[sp] = node;
		Set<Integer> children = g.get(node);
		if (children != null)
			for (Integer child : children)
				if (child != parent && !cycleEdges.contains(new Edge(node, child)))
					cycles(node, child, sp + 1);
	}

	private void makeDistrict(NodeSet res) {
		assert res.size() == target;
		final List<Integer> d = new ArrayList<Integer>(target);
		res.forAll(new NodeVisitor() {
			public void visit(int node) {
				d.add(node);
			}
		});
		Collections.sort(d);
		districts.add(d);
	}

	private NodeSet split(int parentNode, int parentCycle, int node) {
		Set<Integer> skipNodes = new HashSet<Integer>();
		if (parentNode > 0)
			skipNodes.add(parentNode);
		Map<Integer, Integer> cim = cm.get(node); // cycle->index map
		NodeSet res = EMPTY;
		if (cim != null)
			for (Map.Entry<Integer, Integer> entry : cim.entrySet()) {
				Integer cn = entry.getKey();
				Integer cp = entry.getValue();
				int cl = cycle[cn].length;
				skipNodes.add(cycle[cn][(cp + 1) % cl]);
				skipNodes.add(cycle[cn][(cp + cl - 1) % cl]);
				if (cn == parentCycle)
					continue;
				NodeSet rem = splitCycle(cn, cp);
				if (rem == null)
					return null;
				res = res.join(rem);
			}
		Set<Integer> children = g.get(node);
		if (children != null)
			for (Integer child : children) {
				if (skipNodes.contains(child))
					continue;
				NodeSet rem = split(node, 0, child);
				if (rem == null)
					return null;
				res = res.join(rem);
			}
		res = res.join(new SingletonSet(node));
		if (res.size() > target)
			return null;
		if (res.size() < target)
			return res;
		makeDistrict(res);
		return EMPTY;
	}

	private NodeSet splitCycle(int cn, int cp) {
		int[] c = cycle[cn];
		int cl = c.length;

		// recursively process all nodes in a cycle and remember results 
		List<NodeSet> parts = new ArrayList<NodeSet>(cl);
		parts.add(EMPTY);
		int[] sum = new int[cl + 1];
		for (int i = 1; i < cl; i++) {
			NodeSet rem = split(0, cn, c[(cp + i) % cl]);
			if (rem == null)
				return null;
			parts.add(rem);
			sum[i] = sum[i - 1] + rem.size();
		}

		// figure out what starting points are allowed/forbidden
		int a0 = -1;
		rcnt.clear();
		for (int i = 1; i < cl; i++) {
			NodeSet rem = parts.get(i);
			int a = sum[i] % target;
			if (rem.isEmpty()) {
				if (a0 >= 0 && a0 != a)
					return null;
				a0 = a;
			}
			Integer cnt = rcnt.get(a);
			rcnt.put(a, cnt == null ? 1 : cnt + 1);
		}

		// figure out maximally occurring remainder
		if (a0 < 0) {
			int maxcnt = 0;
			for (Map.Entry<Integer, Integer> entry : rcnt.entrySet()) {
				int a = entry.getKey();
				int cnt = entry.getValue();
				if (cnt > maxcnt) {
					maxcnt = cnt;
					a0 = a;
				}
			}
		}

		// build result
		NodeSet start = null;
		NodeSet cur = EMPTY;
		sum[cl] = sum[cl - 1] + target - 1; // sentinel
		for (int i = 0; i < cl; i++) {
			cur = cur.join(parts.get(i));
			if (cur.size() > target)
				return null;
			if (start == null && sum[i] <= a0 && a0 < sum[i + 1]) {
				start = cur;
				cur = EMPTY;
			}
			if (start != null && cur.size() == target) {
				makeDistrict(cur);
				cur = EMPTY;
			}
		}
		boolean split = start != null && !start.isEmpty() && !cur.isEmpty(); 
		if (start != null)
			cur = cur.join(start);
		if (split && cur.size() == target)
			return null;
		return cur.size() > target ? null : cur;
	}

	void write() throws IOException {
		PrintWriter out = new PrintWriter("cactus.out");
		if (found) {
			for (List<Integer> b : districts) {
				for (int i = 0; i < target; i++) {
					if (i > 0)
						out.print(' ');
					out.print(b.get(i));
				}
				out.println();
			}
		} else {
			out.println(-1);
		}
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to verify 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
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

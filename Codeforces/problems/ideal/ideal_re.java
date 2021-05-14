import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem I: Ideal Path.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class ideal_re {
	private static final int MAX_N = 100000;
	private static final int MAX_M = 200000;
	private static final int MAX_C = 1000000000;

	public static void main(String[] args) throws Exception {
		new ideal_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static class Pass {
		final int b;
		final int c;

		Pass(int b, int c) {
			this.b = b;
			this.c = c;
		}
	}

	int n;
	int m;

	Map<Integer, List<Pass>> g = new HashMap<Integer, List<Pass>>();

	void read() throws Exception {
		Scanner in = new Scanner(new File("ideal.in"));
		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();
		assert 2 <= n && n <= MAX_N;
		assert 1 <= m && m <= MAX_M;
		for (int i = 0; i < m; i++) {
			int a = in.nextInt();
			int b = in.nextInt();
			int c = in.nextInt();
			in.nextLine();
			assert 1 <= a && a <= n;
			assert 1 <= b && b <= n;
			assert 1 <= c && c <= MAX_C;
			add(a, b, c);
			add(b, a, c);
		}
		in.close();
	}

	private void add(int a, int b, int c) {
		List<Pass> list = g.get(a);
		if (list == null)
			g.put(a, list = new ArrayList<Pass>());
		list.add(new Pass(b, c));
	}

	static class ListSet {
		int size;
		int[] list;
		boolean[] v;

		ListSet(int n) {
			list = new int[n];
			v = new boolean[n + 1];
		}

		void add(int a) {
			if (v[a])
				return;
			v[a] = true;
			list[size++] = a;
		}

		void clear() {
			for (int i = 0; i < size; i++)
				v[list[i]] = false;
			size = 0;
		}
	}

	int head;
	ListSet cur;
	ListSet next;
	int[] dist;

	int k;
	int[] path;

	void solve() {
		// find distances to the room number n
		dist = new int[n + 1];
		dist[n] = 1;
		cur = new ListSet(n);
		cur.add(n);
		while (head < cur.size && dist[1] == 0) {
			int a = cur.list[head++];
			int d = dist[a];
			List<Pass> list = g.get(a);
			if (list != null)
				for (Pass p : list)
					if (dist[p.b] == 0) {
						dist[p.b] = d + 1;
						cur.add(p.b);
					}
		}

		// assert there's a path
		k = dist[1] - 1;
		assert k >= 0;

		// find lexicographically shortest
		path = new int[k];
		cur.clear();
		cur.add(1);
		next = new ListSet(n);
		int d = dist[1];
		for (int i = 0; i < k; i++) {
			d--;
			int c = Integer.MAX_VALUE;
			for (int j = 0; j < cur.size; j++) {
				int a = cur.list[j];
				for (Pass p : g.get(a))
					if (dist[p.b] == d && p.c < c) 
						c = p.c;
			}
			path[i] = c;
			for (int j = 0; j < cur.size; j++) {
				int a = cur.list[j];
				for (Pass p : g.get(a))
					if (dist[p.b] == d && p.c == c)
						next.add(p.b);
			}
			ListSet t = cur;
			cur = next;
			next = t;
			next.clear();
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("ideal.out");
		out.println(k);
		for (int i = 0; i < k; i++) {
			if (i > 0)
				out.print(' ');
			out.print(path[i]);
		}
		out.println();
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

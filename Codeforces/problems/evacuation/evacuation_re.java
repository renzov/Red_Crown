import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem E: Evacuation Plan.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class evacuation_re {
	private static final int MAX_N = 4000;
	private static final int MAX_LOC = 1000000000;

	public static void main(String[] args) throws Exception {
		new evacuation_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;
	int[] tl;
	int m;
	int[] sl;

	void read() throws Exception {
		Scanner in = new Scanner(new File("evacuation.in"));
		n = in.nextInt();
		in.nextLine();
		assert 1 <= n && n <= MAX_N;
		tl = new int[n];
		for (int i = 0; i < n; i++) {
			tl[i] = in.nextInt();
			assert 1 <= tl[i] && tl[i] <= MAX_LOC;
		}
		in.nextLine();
		m = in.nextInt();
		in.nextLine();
		assert 1 <= m && m <= n;
		sl = new int[m];
		for (int i = 0; i < m; i++) {
			sl[i] = in.nextInt();
			assert 1 <= sl[i] && sl[i] <= MAX_LOC;
		}
		in.nextLine();
		in.close();
	}

	int[] to2i;
	int[] ti2o;
	int[] so2i;
	int[] si2o;

	long[][] cost;
	int[] t2s;
	long sumcost;

	void solve() {
		// sort locations while keeping old -> index and index -> old mapping
		to2i = new int[n];
		ti2o = new int[n];
		sort(tl, to2i, ti2o);

		so2i = new int[m];
		si2o = new int[m];
		sort(sl, so2i, si2o);

		// assert all different
		for (int i = 1; i < n; i++)
			assert tl[i] != tl[i - 1];
		for (int i = 1; i < m; i++)
			assert sl[i] != sl[i - 1];
		// find best-fuel assignment of teams to shelters
		cost = new long[m + 1][n + 1]; // cost[i][j] == cost of assigning i shelters using j teams
		for (int i = 1; i < n; i++)
			cost[0][i] = Long.MAX_VALUE;
		for (int i = 0; i < m; i++) { // assign team to i-th shelter
			long prev = Long.MAX_VALUE;
			for (int j = i; j < n; j++) { // using j+1 teams (from 0 to j inclusive)
				long best = Math.abs(tl[j] - sl[i]) + Math.min(cost[i][j], prev); // best fuel use
				cost[i + 1][j + 1] = best;
				prev = best;
			}
		}
		// construct the best assignment itself: shelter -> team
		t2s = new int[n];
		int j = n - 1; // current team
		long curcost = sumcost = cost[m][n];
		for (int i = m; --i >= 0;) { // assign team to i-th shelter
			boolean done;
			do {
				t2s[j] = i;
				curcost -= Math.abs(tl[j] - sl[i]);
				done = curcost == cost[i][j];
				j--;
			} while (!done);
		}
		assert curcost == 0;
	}

	private void sort(int[] l, int[] o2i, int[] i2o) {
		int n = l.length;
		for (int i = 0; i < n; i++)
			i2o[i] = i;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (l[i] > l[j]) {
					int t = l[i];
					l[i] = l[j];
					l[j] = t;
					int r = i2o[i];
					i2o[i] = i2o[j];
					i2o[j] = r;
				}
		for (int i = 0; i < n; i++)
			o2i[i2o[i]] = i;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("evacuation.out");
		out.println(sumcost);
		for (int k = 0; k < n; k++) {
			if (k > 0)
				out.print(' ');
			out.print(si2o[t2s[to2i[k]]] + 1);
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

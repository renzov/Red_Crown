import java.io.*;
import java.util.Arrays;

/**
 * Solution for NEERC'2010 Problem E: Evacuation Plan.
 * This is a wrong solution that first assigns a "closing" team to each shleter optimally,
 * then assigns the rest of the teams to their closest shelter.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class evacuation_re_wrong {
	private static final int MAX_N = 4000;
	private static final int MAX_LOC = 1000000000;

	public static void main(String[] args) throws Exception {
		new evacuation_re_wrong().go();
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
	int[] s2t;
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
		// find best-fuel assignment of teams to shelters they are closing
		cost = new long[m + 1][n + 1]; // cost[i][j] == cost of assigning i shelters using j teams
		for (int i = 0; i < m; i++) { // assign team to i-th shelter
			long prev = Long.MAX_VALUE;
			for (int j = i; j < n; j++) { // using j+1 teams (from 0 to j inclusive)
				long best = Math.min(Math.abs(tl[j] - sl[i]) + cost[i][j], prev); // best fuel use
				cost[i + 1][j + 1] = best;
				prev = best;
			}
		}
		// construct the best assignment itself: shelter -> team
		s2t = new int[m];
		int cj = n; // initially we can use all teams
		for (int i = m; --i >= 0;) { // assign team to i-th shelter
			s2t[i] = -1; // not found yet
			long best = cost[i + 1][cj]; // best fuel use
			for (int k = i; k < cj; k++) { // assign k-th team to i-th shelter
				long d = Math.abs(tl[k] - sl[i]) + cost[i][k];
				if (d == best) {
					s2t[i] = k;
					cj = k; // use only remaining teams
					break;
				}
			}
			assert s2t[i] >= 0; // should have been found
		}
		// find what teams are not yet assigned
		t2s = new int[n];
		Arrays.fill(t2s, -1);
		for (int i = 0; i < m; i++)
			t2s[s2t[i]] = i;
		// assign the rest of teams to their closest shelters
		sumcost = cost[m][n];
		for (int k = 0; k < n; k++) {
			if (t2s[k] >= 0)
				continue;
			int best = Integer.MAX_VALUE;
			for (int i = 0; i < m; i++) {
				int d = Math.abs(tl[k] - sl[i]);
				if (d < best) {
					best = d;
					t2s[k] = i;
				}
			}
			sumcost += best;
		}
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

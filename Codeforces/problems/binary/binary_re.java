import java.io.*;
import java.util.Arrays;

/**
 * Solution for NEERC'2010 Problem B: Binary Operation.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class binary_re {

	public static void main(String[] args) throws Exception {
		new binary_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static final int N = 10;
	static final int M = 19;
	static final long MAX = 1000000000000000000L;

	int[][] o = new int[N][N];
	long a;
	long b;

	void read() throws Exception {
		Scanner in = new Scanner(new File("binary.in"));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				o[i][j] = in.nextInt();
				assert o[i][j] >= 0 && o[i][j] < N;
			}
			in.nextLine();
		}
		assert o[0][0] == 0;
		a = in.nextLong();
		b = in.nextLong();
		in.nextLine();
		assert 0 <= a && a <= b && b <= MAX;
		in.close();
	}

	int[] d = new int[M];
			
	void solve() {
		long power = 1;
		for (int i = 0; i < M; i++) {
			int da = (int)((a / power) % 10);
			int db = (int)((b / power) % 10);
			long ra = (a / power / 10) * power * 10 + (da + 1) * power;
			long rb = (b / power / 10) * power * 10 + db * power;
			int d;
			if (ra <= rb) {
				d = solveDigit0(da, da, ra - a - 1);
				d = solveDigit(d, (da + 1) % N, power, (rb - ra) / power);
				d = solveDigit0(d, db, b - rb + 1);
			} else {
				assert da == db;
				d = solveDigit0(da, da, b - a);
			}
			this.d[i] = d;
			power *= 10;
		}
	}

	// compute a0 * a * a * ... * a
	//            \---------------/ c times
	private int solveDigit0(int a0, int a, long c) {
		int[] dig = new int[N];
		int[] pos = new int[N];
		Arrays.fill(pos, -1);
		int i = a0;
		int n = 0;
		do {
			if (n == c)
				return i;
			dig[n] = i;
			pos[i] = n;
			n++;
			i = o[i][a];
		} while (pos[i] < 0);
		int s = pos[i];
		int p = n - s;
		int rem = (int)((c - s) % p);
		return dig[s + rem];
	}

	// compute a0 * a' * (a + 1)' * ... * b'
	//            \-----------------------/ d times, where +1 operation wraps around
	// where each i' is a * a * ... * a
	//                  \-------------/ c times
	// so that is a total of c*d operations
	private int solveDigit(int a0, int a, long c, long d) {
		int[] dig = new int[N * N];
		int[][] pos = new int[N][N];
		for (int[] p : pos)
			Arrays.fill(p, -1);
		int i = a0;
		int n = 0;
		do {
			if (n == d)
				return i;
			dig[n] = i;
			pos[a][i] = n;
			n++;
			i = solveDigit0(i, a, c);
			a = (a + 1) % N;
		} while (pos[a][i] < 0);
		int s = pos[a][i];
		int p = n - s;
		int rem = (int)((d - s) % p);
		return dig[s + rem];
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("binary.out");
		int j = M - 1;
		while (j > 0 && d[j] == 0)
			j--;
		for (int i = j; i >= 0; i--)
			out.print(d[i]);
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

		public long nextLong() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Long.parseLong(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}

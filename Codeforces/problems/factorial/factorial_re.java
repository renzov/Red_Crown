import java.io.*;
import java.util.Arrays;

/**
 * Solution for NEERC'2010 Problem F: Factorial Simplification.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class factorial_re {
	private static final int MAX_NM = 1000;
	private static final int MAX_PQ = 10000;
	private static final int MAX_PRIMES = 2000;

	public static void main(String[] args) throws Exception {
		new factorial_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;
	int m;
	int[] p;
	int[] q;

	void read() throws Exception {
		Scanner in = new Scanner(new File("factorial.in"));
		n = in.nextInt();
		m = in.nextInt();
		in.nextLine();
		assert 1 <= n && n <= MAX_NM;
		assert 1 <= m && m <= MAX_NM;
		p = readArray(in, n);
		q = readArray(in, m);
		in.close();
	}

	private int[] readArray(Scanner in, int n) {
		int[] p = new int[n];
		for (int i = 0; i < n; i++) {
			p[i] = in.nextInt();
			assert 1 <= p[i] && p[i] <= MAX_PQ;
		}
		in.nextLine();
		return p;
	}

	static class FF implements Comparable<FF> {
		final int f;
		final int m;

		FF(int f, int m) {
			this.f = f;
			this.m = m;
		}

		public int compareTo(FF o) {
			return f - o.f;
		}
	}


	int np;
	int lastPrime;
	int[] primes;

	int currentFactorial;
	int[] factors;
	int[] fp;
	int[] rp;

	int k;
	int[] r;
	int[] s;


	void solve() {
		// sort all
		FF[] ffs = new FF[n + m];
		for (int i = 0; i < n; i++)
			ffs[i] = new FF(p[i], 1);
		for (int i = 0; i < m; i++)
			ffs[n + i] = new FF(q[i], -1);
		Arrays.sort(ffs);

		// compute primes in result
		np = 2;
		primes = new int[MAX_PRIMES];
		primes[0] = 2;
		primes[1] = lastPrime = 3;
		primes[2] = Integer.MAX_VALUE; // sentinel
		
		factors = new int[2 * MAX_PRIMES];
		fp = new int[MAX_PRIMES];
		rp = new int[MAX_PRIMES];
		currentFactorial = 1;
		for (FF ff : ffs) {
			while (currentFactorial < ff.f)
				nextFactorial();
			for (int i = 0; i < np; i++)
				rp[i] += fp[i] * ff.m;
		}

		// check integer
		for (int i = 0; i < np; i++)
			if (rp[i] < 0) {
				k = -1;
				return;
			}

		// increase factorials up to the before next prime
		if (currentFactorial == lastPrime)
			nextPrime();
		while (currentFactorial < lastPrime - 1)
			nextFactorial();

		// find factorial multipliers
		r = new int[MAX_PQ];
		s = new int[MAX_PQ]; 
		while (currentFactorial > 1) {
			if (divides()) {
				r[k] = currentFactorial;
				s[k] = 0;
				do {
					divide();
					s[k]++;
				} while (divides());
				k++;	
			}
			prevFactorial();
		}
	}

	private void nextFactorial() {
		currentFactorial++;
		if (lastPrime < currentFactorial)
			nextPrime();
		factor();
		for (int i = 0; factors[i] >= 0; i += 2)
			fp[factors[i]] += factors[i + 1];
	}

	private void prevFactorial() {
		for (int i = 0; factors[i] >= 0; i += 2)
			fp[factors[i]] -= factors[i + 1];
		currentFactorial--;
		factor();
	}

	private boolean divides() {
		for (int i = 0; i < np; i++)
			if (fp[i] > rp[i])
				return false;
		return true;
	}

	private void divide() {
		for (int i = 0; i < np; i++)
			rp[i] -= fp[i];
	}

	private void nextPrime() {
	search:
		while (true) {
			lastPrime += 2;
			for (int i = 0; primes[i] * primes[i] <= lastPrime; i++)
				if (lastPrime % primes[i] == 0)
					continue search;
			primes[np++] = lastPrime;
			break;
		}
		primes[np] = Integer.MAX_VALUE; // sentinel
	}

	private void factor() {
		int rem = currentFactorial;
		int ptr = 0;
		for (int i = 0; primes[i] <= rem; i++)
			if (rem % primes[i] == 0) {
				factors[ptr] = i;
				factors[ptr + 1] = 0;
				do {
					rem /= primes[i];
					factors[ptr + 1]++;
				} while (rem % primes[i] == 0);
				ptr += 2;
			}
		factors[ptr] = -1;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("factorial.out");
		out.println(k);
		for (int i = 0; i < k; i++)
			out.printf("%d %d%n", r[i], s[i]);
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

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem D: Dome of Circus
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class dome_re {
	private static final int MAX_N = 10000;
	private static final double MAX_ABS = 1000;
	private static final double EPS = 1e-6;

	public static void main(String[] args) throws Exception {
		new dome_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static class P3D {
		double x;
		double y;
		double z;

		P3D(double x, double y, double z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
	}

	int n;
	P3D[] points;

	void read() throws Exception {
		Scanner in = new Scanner(new File("dome.in"));
		in.useLocale(Locale.US);
		n = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= MAX_N;
		points = new P3D[n];
		boolean ok = false;
		for (int i = 0; i < n; i++) {
			P3D p = points[i] = new P3D(in.nextDouble(), in.nextDouble(), in.nextDouble());
			in.nextLine();
			assert Math.abs(p.x) <= MAX_ABS;
			assert Math.abs(p.y) <= MAX_ABS;
			assert Math.abs(p.z) <= MAX_ABS && p.z > 0;
			ok |= p.x != 0 || p.y != 0;
		}
		assert ok;
		in.close();
	}

	double h;
	double r;

	void solve() {
		double h0 = 0;
		for (int i = 0; i < n; i++)
			h0 = Math.max(h0, points[i].z);
		double h1 = 3 * MAX_ABS;
		while (h1 - h0 > EPS) {
			double h2 = h0 + (h1 - h0) / 3;
			double h3 = h0 + (h1 - h0) / 3 * 2;
			double v2 = volume(h2);
			double v3 = volume(h3);
			if (v2 < v3)
				h1 = h3;
			else
				h0 = h2;
		}
		h = (h0 + h1) / 2;
		double v = volume(h);
		r = Math.sqrt(v / h); 
	}

	private double volume(double h) {
		double v = 0;
		for (int i = 0; i < n; i++) {
			double di = Math.sqrt(sqr(points[i].x) + sqr(points[i].y));
			double hi = points[i].z;
			double r = di * h / (h - hi);
			v = Math.max(v, sqr(r) * h);
		}
		return v;
	}

	private double sqr(double c) {
		return c * c;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("dome.out");
		out.printf(Locale.US, "%.3f %.3f%n", h, r);
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
		private boolean localeset;

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

		public double nextDouble() {
			assert localeset : "Locale must be set with useLocale(Locale.US)";
			String s = next();
			assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			// at most two digits
			assert s.indexOf('.') < 0 || s.indexOf('.') >= s.length() - 3;
			try {
				return Double.parseDouble(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public void useLocale(Locale locale) {
			assert locale == Locale.US;
			localeset = true;
		}
	}
}

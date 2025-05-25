import java.awt.Point;
import java.io.*;
import java.math.BigInteger;
import java.util.*;
import static java.lang.Math.*;

public class Solution implements Runnable {

	BufferedReader in;
	PrintWriter out;
	StringTokenizer tok = new StringTokenizer("");
	int [][] G;
	int P, M;

	public static void main(String[] args) {
		new Thread(null, new Solution(), "", 64 * (1L << 20)).start();
	}

	public void run() {
		try {
			long t1 = System.currentTimeMillis();
			if (System.getProperty("ONLINE_JUDGE") != null) {
				in = new BufferedReader(new FileReader("china.in"));
				out = new PrintWriter("china.out");
			} else {
				in = new BufferedReader(new FileReader("china.in"));
				out = new PrintWriter("china.out");
			}
			Locale.setDefault(Locale.US);
			solve();
			in.close();
			out.close();
			long t2 = System.currentTimeMillis();
			System.err.println("Time = " + (t2 - t1));
		} catch (Throwable t) {
			t.printStackTrace(System.err);
			System.exit(-1);
		}
	}

	String readString() throws IOException {
		while (!tok.hasMoreTokens()) {
			tok = new StringTokenizer(in.readLine());
		}
		return tok.nextToken();
	}

	int readInt() throws IOException {
		return Integer.parseInt(readString());
	}

	long readLong() throws IOException {
		return Long.parseLong(readString());
	}

	double readDouble() throws IOException {
		return Double.parseDouble(readString());
	}

	BigInteger readBigInteger() throws IOException {
		return new BigInteger(readString());
	}

	// solution

	void solve() throws IOException {
		// read the input
		BigInteger N = readBigInteger();
		BigInteger two = new BigInteger("2");
		if ( N.testBit(0) ){	// N is odd
			out.println( N.shiftRight(1) );
		}
		else {	// N is even
			N = N.shiftRight(1);	// N' = N/2
			if ( N.testBit(0) )	// N is not divisible by 4
				out.println( N.subtract(two) );
			else				// N is divisible by 4
				out.println( N.subtract(BigInteger.ONE) );
		}
	}
}

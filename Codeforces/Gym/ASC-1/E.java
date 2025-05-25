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
				in = new BufferedReader(new FileReader("nice.in"));
				out = new PrintWriter("nice.out");
			} else {
				in = new BufferedReader(new FileReader("nice.in"));
				out = new PrintWriter("nice.out");
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

	void copy( int[][] A, int[][] B ){
		for ( int i=0; i < (1 << M); ++i )
			for ( int j=0; j < (1 << M); ++j )
				B[i][j] = A[i][j] % P;
	}

	void multiply( int[][] A, int[][] B, int[][] C ){
		for ( int i=0; i < (1 << M); ++i )
			for ( int j=0; j < (1 << M); ++j ){
				C[i][j] = 0;
				for ( int k=0; k < (1 << M); ++k ){
					C[i][j] += A[i][k] * B[k][j];
					C[i][j] %= P;
				}
			}
	}

	void fastExp( BigInteger N, int [][] ans ){
		if ( N.compareTo( BigInteger.ONE ) == 0 ){
			copy( G, ans );
			return;
		}
		int[][] T = new int [1 << M][1 << M];
		if ( N.testBit(0) ){	// M is odd
			fastExp( N.subtract( BigInteger.ONE ), T );
			multiply( T, G, ans );
		}
		else {	// M is even
			fastExp( N.shiftRight(1), T );
			multiply( T, T, ans );
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
		M = readInt();
		P = readInt();	
		// generate all 2^N bit strings
		int[][] B = new int[1 << M][M];
		G = new int[1 << M][1 << M];
		for ( int mask = 0; mask < (1 << M); ++mask ){
			for ( int i=0; i < M; ++i ){
				B[mask][i] = (mask >> i) & 1; 
			}
		}
		// construct adjacency matrix
		for ( int i = 0; i < (1 << M); ++i )
			for ( int j = i; j < (1 << M); ++j ){
				boolean ok = true;
				for ( int k=1; k < M && ok; ++k )
					if ( B[i][k - 1] == B[i][k] && B[j][k - 1] == B[j][k] && B[i][k] == B[j][k] )
						ok = false;
				if ( ok )
					G[i][j] = G[j][i] = 1;
			}
		// find the answer	
		int res = 0;
		if ( N.compareTo( BigInteger.ONE ) == 0 ){	// every bit string is possible
			res = (1 << M) % P;
		}
		else {	
			N = N.subtract( BigInteger.ONE );
			// matrix exponentiation
			int[][] ans = new int[1 << M][1 << M];
			fastExp( N, ans );
			res = 0;
			// sum every entry of the matrix
			for ( int i=0; i < (1 << M); ++i )
				for ( int j=0; j < (1 << M); ++j ){
					res += ans[i][j];
					res %= P;
				}
		}
		// print the solution		
		out.println(res);
	}
}

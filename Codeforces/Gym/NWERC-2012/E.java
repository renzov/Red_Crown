import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main {
	static int MAXN = 10001;
	public static void main( String [] args ){
		PrintWriter out = new PrintWriter( new BufferedOutputStream( System.out ) );
		BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );

		// Precompute answer
		BigInteger [] f = new BigInteger[ MAXN ];
		BigInteger [] g = new BigInteger[ MAXN ];
		f[0] = BigInteger.ONE;
		f[1] = new BigInteger("2");
		g[0] = BigInteger.ZERO;
		g[1] = BigInteger.ONE;

		for ( int i=2; i < MAXN; ++i ){
			f[i] = f[i - 1].add( f[i - 2] );
			g[i] = g[i - 1].add( g[i - 2] );
		}
	
		int N;
		try {
			while ( true ){
				N = Integer.parseInt( in.readLine() );
				out.println( g[N - 1].add(g[N - 1]).add(f[N - 2]) );
			}
		}
		catch (Exception e) {

		}
		finally {
			out.close();
		}
	}

}

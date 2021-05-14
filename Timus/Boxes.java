import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Boxes {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in) );
	static PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		StringTokenizer parser;
		BigInteger [][] C;
		C = new BigInteger [50][25];
		int N, A, B, M;

		try {
			parser = new StringTokenizer(in.readLine());
			
			N = Integer.parseInt(parser.nextToken());
			A = Integer.parseInt(parser.nextToken());
			B = Integer.parseInt(parser.nextToken());

			if ( A <= B ) M = B;
			else M = A;
			
			for ( int i=0; i <= (M + N); ++i )
				for ( int j=i + 1; j <= N; ++j )
					C[i][j] = BigInteger.ZERO;

			for ( int i=0; i <= (M + N); ++i )
				C[i][0] = BigInteger.ONE;
			
			
			for ( int n=1; n <= (N + M); ++n )
				for ( int k=1; k <= N; ++k )
					C[n][k] = C[n - 1][k].add( C[n - 1][k - 1] );
				
			out.println( C[N + A][N].multiply( C[N + B][N] ) );
		}
		catch (Exception ex){
			out.println(ex.toString());
		}
		finally {
			out.close();
		}
	}

}

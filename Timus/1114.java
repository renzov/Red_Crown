import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Boxes {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in) );
	static PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		StringTokenizer parser;
		BigInteger [][] dp;
		dp = new BigInteger [25][25];
		int N, A, B, M;

		try {
			parser = new StringTokenizer(in.readLine());
			
			N = Integer.parseInt(parser.nextToken());
			A = Integer.parseInt(parser.nextToken());
			B = Integer.parseInt(parser.nextToken());

			if ( A <= B ) M = B;
			else M = A;

			for ( int i=0; i <= M; ++i ){
				dp[1][i] = BigInteger.ONE;
			}
			
			for ( int i=2; i <= N; ++i )
				for ( int j=0; j <= M; ++j ){
					dp[i][j] = BigInteger.ZERO;
					for ( int k=0; k <= j; ++k )
						dp[i][j] = dp[i][j].add( dp[i - 1][k] );

				}

			BigInteger cntA = BigInteger.ZERO;
			BigInteger cntB = BigInteger.ZERO;

			for ( int j=0; j <= M; ++j ){
				if ( j <= A ) cntA = cntA.add( dp[N][j] );
				if ( j <= B ) cntB = cntB.add( dp[N][j] ); 
			}
			out.println( cntA.multiply( cntB ) );
		}
		catch (Exception ex){
			out.println(ex.toString());
		}
		finally {
			out.close();
		}
	}

}

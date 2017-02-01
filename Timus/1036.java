import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Lucky {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in) );
	static PrintWriter out = new PrintWriter(System.out);
	
	public static void main(String[] args) {
		StringTokenizer parser;
		BigInteger [][] dp;
		dp = new BigInteger [55][555];
		int s,n;
		try {
			parser = new StringTokenizer(in.readLine());
			n = Integer.parseInt(parser.nextToken());
			s = Integer.parseInt(parser.nextToken());
			if ( s % 2 == 1 ) out.println("0");
			else {
				s >>= 1;
				for ( int i=0; i < 10; ++i )
					dp[0][i] = BigInteger.ONE;
				for ( int i=10; i <= s; ++i )
					dp[0][i] = BigInteger.ZERO;
				for ( int i=1; i < n; ++i ){
					for ( int j=0; j <= s; ++j ){
						dp[i][j] = BigInteger.ZERO;
						for ( int k=0; k < 10; ++k )
							if ( k <= j )
								dp[i][j] = dp[i][j].add(dp[i-1][j-k]);
					}
				}
				out.println( dp[n-1][s].multiply(dp[n-1][s]) );
			}
		}
		catch (Exception ex){
			out.println(ex.toString());
		}
		finally {
			out.close();
		}
	}

}

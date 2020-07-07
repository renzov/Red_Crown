import java.io.*;
import java.util.*;
import java.math.BigInteger;
public class Main {
	public static int N;
	public static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	public static PrintWriter out = new PrintWriter(System.out);
	final static int MAXN = 10001;
	public static BigInteger [] dp = new BigInteger[MAXN];
	
	public static void precalc(){
		BigInteger [] pow2 = new BigInteger[MAXN];
		BigInteger two = new BigInteger("2");

		pow2[0] = BigInteger.ONE;
		for ( int i=1; i < MAXN; ++i )
			pow2[i] = pow2[i - 1].multiply( two );
		
		dp[0] = BigInteger.ZERO;
		dp[1] = BigInteger.ONE;
		for ( int i=2; i < MAXN; ++i ){
			dp[i] = pow2[i];
			for ( int j=1; j < i; ++j )
				dp[i] = dp[i].min( dp[j].multiply( two ).add( pow2[i - j].subtract(BigInteger.ONE)   ) ); 	
		}
	}
	
	public static void main(String[] args) {
		try {
			precalc();
			while ( true ){
				N = Integer.parseInt(in.readLine());
				out.println(dp[N]);
			}
		}
		catch (Exception ex){}
		finally {
			out.close();
		}
	}

}



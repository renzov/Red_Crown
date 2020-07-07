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
		BigInteger two = new BigInteger("2");
		BigInteger bestHanoi = new BigInteger("2");

		dp[0] = BigInteger.ZERO;
		dp[1] = BigInteger.ONE;
		int cnt = 2;
		for ( int i=2; i < MAXN;  ){
			for ( int j=0; i < MAXN && j < cnt; ++j, i++ )
				dp[i] = dp[i - 1].add( bestHanoi );
			cnt++;
			bestHanoi = bestHanoi.multiply( two );
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



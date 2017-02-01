import java.io.*;
import java.util.*;
import java.math.BigInteger;
public class Main {
	public static int N;
	public static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	public static PrintWriter out = new PrintWriter(System.out);
	
	public static BigInteger solve(){
		BigInteger [][][] dp = new BigInteger[(N<<1)+2][N+2][N+2];
		for (int i=0; i <= (N<<1); ++i){
			for (int j=0; j <= N; ++j){
				Arrays.fill(dp[i][j], BigInteger.ZERO);
			}
		}
		dp[0][N][0] = BigInteger.ONE;
		for (int i=0; i < (N<<1); ++i){
			for (int j=0; j <= N; ++j){
				for (int k=0; k <= N; ++k){
					if ( dp[i][j][k].compareTo(BigInteger.ZERO) != 0 ){
						if ( j > 0 ){
							dp[i+1][j-1][k+1] = dp[i+1][j-1][k+1].add(dp[i][j][k]); 
						}
						if ( k > 0 ){
							dp[i+1][j][k-1] = dp[i+1][j][k-1].add( dp[i][j][k] ); 
						}
					}
				}
			}
		}
		return dp[N<<1][0][0];
	}
	
	public static void main(String[] args) {
		try {
			while (true){
				N = Integer.parseInt(in.readLine());
				if ( N == 0 ) break;
				out.println(solve());
			}
		}
		catch (Exception ex){}
		finally {
			out.close();
		}
	}

}


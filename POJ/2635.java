import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {
	public static int M;
	public static int N = 1000000;
	public static int [] d = new int [78499];
	public static int [] prime = new int[ N / 64];
	public static BufferedReader in = new BufferedReader( new InputStreamReader(System.in));
	public static PrintWriter out = new PrintWriter(System.out);
	
	public static int gP(int n) {
		return prime[n>>6] & (1<<((n>>1)&31));
	}
	
	public static void rP(int n){
		prime[n>>6]&=~(1<<((n>>1)&31));
	} 
	
	public static void sieve(){
		Arrays.fill(prime, ~0);
		int i;
		int i2;
		int sq = 1001;
		for ( i=3; i < sq;  i+=2 ){
			if (gP(i) != 0){
				i2 = i << 1;
				for ( int j=i*i; j < N ; j+= i2 ){
					rP(j);
				}
			}
		}
		
		int cnt = 0;
		d[cnt++] = 2;
		for ( i=3; i <= N ; i+=2 ){
			if (gP(i) != 0){
				d[cnt++] = i;
			}
		}
		M = cnt;
	}
	
	public static void main(String[] args) {
		StringTokenizer parser;
		BigInteger K;
		int L;
		boolean ok;
		sieve();
		try {
			while ( true ){
				parser = new StringTokenizer(in.readLine());
				K = new BigInteger( parser.nextToken() );
				L = Integer.parseInt(parser.nextToken());
				if (L==0) break;
				ok = true;
				for ( int i=0; ok && i < M && d[i] < L ; ++i ){
					if ( K.mod( new BigInteger( new Integer(d[i]).toString() ) ).equals(BigInteger.ZERO) ){
						ok = false;
						out.println("BAD " + d[i]);
					}
				}
				if ( ok ){
					out.println("GOOD");
				}
			}
			
		}
		catch (Exception ex){
			
		}
		finally {
			out.close();
		}

	}

}


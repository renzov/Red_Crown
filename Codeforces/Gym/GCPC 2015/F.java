import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class F {
	public static void main(String[] args)throws Exception {
        new F().run();
    }
	
	private void run() throws Exception{
		  BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		  long N=Long.parseLong( reader.readLine() );
		  System.out.println( solve(N) );	  
		  reader.close();
	}

	long solve( long N ){
		long res = 1;
		long cnt = 1;
	
		while ( N % 2 == 0 ){ 
			cnt++;
			N /= 2;	
		}
		res *= cnt;

		// 1000000 ^ 3 = 10 ^ 18
		for ( int i=3; i < 1000000; i += 2 ){
			cnt = 1;
			while ( N % i == 0 ){
				cnt++;
				N /= i;
			}
			res *= cnt;
		}
		if ( N == 1 ) return res;
		if ( isprime( N ) ) return 2L * res;
		if ( square( N ) ) return 3L * res;
		return 4L * res;
	}

	boolean isprime( long N ){
		BigInteger X = BigInteger.valueOf(N);
		return X.isProbablePrime(100);
	}

	boolean square(long N){
    	double d=Math.sqrt(N);
    	long start=(long)Math.ceil(d-2);
    	long end=(long)Math.ceil(d+2);
    	for(long i=start;i<=end;i++)
    		if(i*i==N)
    			return true;
    	return false;
    }

}

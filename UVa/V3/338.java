import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {
	public static void printNumber(String a,int m,int pad,PrintWriter out){
		int d = m - a.length() - pad;
		for (int i=0; i < d; ++i) out.print(' ');
		out.println(a);
	}
	public static void printLine(int n,int m,PrintWriter out){
		for (int i=0; i < (m - n); ++i)
			out.print(' ');
		for (int i=0; i < n; ++i) out.print('-');
		out.println();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );
		PrintWriter out = new PrintWriter( System.out );
		StringTokenizer parser;
		try {
			String line;
			BigInteger a,b;
			BigInteger result;
			while (true){
				line = in.readLine();
				parser = new StringTokenizer(line," ");
				a = new BigInteger( parser.nextToken() );
				if (!parser.hasMoreTokens()) break;
				b = new BigInteger( parser.nextToken() );
				result = a.multiply(b);
				int n = b.toString().length();
				int k = Math.max(a.toString().length(), b.toString().length());
				int m = Math.max(result.toString().length(),k);
				printNumber(a.toString(),m,0,out);
				printNumber(b.toString(),m,0,out);
				printLine(k,m,out);
				BigInteger c;
				if (result.compareTo(BigInteger.ZERO) == 0){
					printNumber(result.toString(), m , 0 , out);
				}
				else {
					ArrayList<String> res = new ArrayList<String>();
					int cnt = 0;
					for (int i=0; i < n; ++i){
						c = new BigInteger( "" + b.toString().charAt(n-1-i) );
						c = c.multiply(a);
						res.add(c.toString());
						if (c.compareTo(BigInteger.ZERO) == 0) continue;
						cnt++;
					}
					if (cnt > 1){
						for (int i=0; i<n; ++i){
							if (res.get(i).compareTo("0") != 0)
								printNumber(res.get(i),m,i,out);
						}
						printLine(m,m,out);
						printNumber(result.toString(), m , 0 , out);
					}
					else {
						printNumber(result.toString(), m, 0, out);
					}
				}
				out.println();
			}
		}
		catch (Exception ex){
			
		}
		finally{
			out.close();
		}
	}

}

import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	
	static PrintWriter out = new PrintWriter(System.out);
	static BigInteger Limit = BigInteger.TEN.pow(60);
	static BigInteger [] row = new BigInteger[10000];
	static int rowl;
	public static void main(String[] args){
		out.println(1);
		out.println(1 + " " + 1);
		row[0] = BigInteger.ONE;
		row[1] = BigInteger.ONE;
		rowl = 2;
		boolean nend = true;
		while ( nend ){
			for ( int i=rowl - 1; i > 0 ; i-- ){
				row[i] = row[i].add(row[i-1]);
			}
			row[rowl] = BigInteger.ONE;
			rowl++;
			for ( int i=0; i < rowl; ++i ){
				if ( row[i].compareTo(Limit) >= 0 ){ nend = false; }
				if ( i > 0 ) out.print(' ');
 				out.print(row[i]);
			}
			out.println();
		}
		out.close();
	}
}


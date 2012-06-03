import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {

	/**
	 * Problema Factorial Frequencies Uva 324
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BufferedReader in = new BufferedReader( new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);	
		BigInteger act = BigInteger.ONE;
		int [][] frec = new int [367][10];
		String ref;
		for (int i=1; i <= 366; ++i){
			act = act.multiply( new BigInteger(new Integer(i).toString()) );
			ref = act.toString();
			for (int j=0; j < 10; ++j) frec[i][j] = 0;
			for (int j=0; j < ref.length(); ++j){
				switch (ref.charAt(j)){
					case '0' : frec[i][0]++; break;
					case '1' : frec[i][1]++; break;
					case '2' : frec[i][2]++; break;
					case '3':  frec[i][3]++; break;
					case '4' : frec[i][4]++; break;
					case '5' : frec[i][5]++; break;
					case '6' : frec[i][6]++; break;
					case '7' : frec[i][7]++; break;
					case '8' : frec[i][8]++; break;
					case '9' : frec[i][9]++; break;
				}
			}	
		}
		int n;
		
		try {
			while ( true ){
				n = Integer.parseInt(in.readLine());
				if (n==0) break;
				out.println(n + "! --");
				for (int i=0; i < 10; ++i){
					if (i == 5) out.println();
					if (i==0 || i == 5) out.print("   ");
					else out.print("    ");
					out.print("(" + i + ")");
					if (frec[n][i] < 10) out.print("    ");
					else if (frec[n][i] < 100) out.print("   ");
					else out.print("  ");
					out.print(frec[n][i]);
				}
				out.println();
			}
		}
		catch (Exception ex){
			
		}
		finally {
			out.close();
		}
	}
}
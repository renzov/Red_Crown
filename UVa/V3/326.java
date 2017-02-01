import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;


public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int [] lastRow = new int[15];
		BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );
		PrintWriter out = new PrintWriter( System.out );
		StringTokenizer parser;
		try {
			String line;
			int n;
			int k;
			while (true){
				line = in.readLine();
				parser = new StringTokenizer(line," ");
				n =  Integer.parseInt( parser.nextToken() );
				if (n==0) break;
				for (int i=0; i<n; ++i)
					lastRow[i] = Integer.parseInt( parser.nextToken() );
				for (int j=n-1; j > 0; --j){
					for (int i=0; i < j; ++i)
						lastRow[i] = lastRow[i+1] - lastRow[i];
				}
				k = Integer.parseInt(parser.nextToken());
				for (int i=0; i < k; ++i){
					for (int j=1; j < n; ++j)
						lastRow[j] += lastRow[j-1];
				}
				out.println("Term " + (n + k) + " of the sequence is " + lastRow[n-1]);
			}
		}
		catch (Exception ex){
				
		}
		finally {
			out.close();
		}
	} 

}

import java.util.*;
import java.io.*;

public class Main {
	static BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );
	static PrintWriter out = new PrintWriter(System.out);
	public static void main(String[] args) {
		String line;
		StringTokenizer parser;
		int a , b , c;
		try {
			line = in.readLine();
			int runs = Integer.parseInt(line);
			while (runs-- > 0){
				line = in.readLine(); //Read Blank Line
				parser = new StringTokenizer(in.readLine());
				try {
					a = Integer.parseInt(parser.nextToken());
				}
				catch (Exception ex){
					a = -1;
				}
				parser.nextToken();
				try {
					b = Integer.parseInt(parser.nextToken());
				}
				catch (Exception ex){
					b = -1;
				}
				parser.nextToken();
				try {
					c = Integer.parseInt(parser.nextToken());
				}
				catch (Exception ex){
					c = -1;
				}
				if (c == -1){
					c = a + b;
				}
				else if (a == -1){
					a = c - b;
				}
				else if (b == -1){
					b = c - a;
				}
				out.println(a + " + " + b + " = " + c);
			}
		}
		catch (Exception ex){
			
		}
		finally {
			out.close();
		}
	}

}

import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {
	public static void main(String [] args){
		try {
			BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );
			String line;
			while (in.ready()){
				line = in.readLine();
				line = line.trim();
				int size = 0;
				boolean bad = false;
				
				int [] s1 = new int[ line.length() + 5 ];
				int [] s2 = new int[ line.length() + 5 ];
				s1[0] = s2[0] = 0;
 				for (int i=0; i < line.length() && !bad; ++i){
					if ( line.charAt(i) == '-' )
						continue;
					size++;
					if ( Character.isDigit(line.charAt(i)) ){
						s1[ size ] = s1[size - 1] + Integer.parseInt("" + line.charAt(i));
						s2[ size ] = s1[size] + s2[size - 1];
					}
					else if ( line.charAt(i) == 'X' ){
						if (size != 10) bad = true;
						else {
							s1[ size ] = s1[ size - 1 ] + 10;
							s2[ size ] = s1[size] + s2[size - 1];
						}
					}
					else {
						bad = true;
					}
				}
 				if (bad || size != 10 || (s2[10]%11 != 0)){
 					System.out.println(line + " is incorrect.");
 				}
 				else {
 					System.out.println(line + " is correct.");
 				}
			}
			
		}
		catch (Exception ex){
				
		}
	}
}
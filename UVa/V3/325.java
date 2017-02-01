import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;


public class Main {

	/**
	 * Problema Identifying Legal Pascal Real Constants - Uva 325
	 */
	
	public static boolean isSigned(String s){
		if (s.length() == 0) return false;
		int begin;
		if (s.charAt(0) == '+' || s.charAt(0)=='-') begin = 1;
		else begin = 0;
		for (int i=begin; i < s.length(); ++i){
			if ( !Character.isDigit( s.charAt(i) ) ) return false;
		}
		return true;
	}
	public static boolean isNumber(String s){
		if (s.length() == 0) return false;
		for (int i=0; i < s.length(); ++i){
			if ( !Character.isDigit( s.charAt(i) ) ) return false;
		}
		return true;
	}
	public static boolean isok(String l){
		int p = l.indexOf('.');
		int e = l.indexOf('E');
		if (p==-1 && e==-1) return false;
		if (p==-1){
			//..E..
			if (isSigned( l.substring(0, e) )  && isSigned( l.substring(e+1) ) )
				return true;
			else
				return false;
		}
		else if (e == -1){ /* **.** */
			return isSigned(l.substring(0,p)) && isNumber(l.substring(p+1));
		}
		else { /* **.**E** */
			if (e < p) return false;
			return isSigned( l.substring(0,p) ) && isNumber( l.substring(p+1,e) ) && isSigned(l.substring(e+1));
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BufferedReader in = new BufferedReader( new InputStreamReader( System.in ));
		PrintWriter out = new PrintWriter( System.out );
		String line;
		try{
			while (true){
				line = in.readLine();
				if (line.charAt(0) == '*') break;
				line = line.trim();
				String rep = line.replace('e', 'E');
				if (isok(rep)){
					out.println(line + " is legal.");
				}
				else {
					out.println(line + " is illegal.");	
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

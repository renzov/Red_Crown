import java.io.*;

/**
    Interaction for NEERC'2010 Problem X: Xtrapolation.
    @author Roman Elizarov
*/
public class Interact {
	public static void main(String[] args) throws IOException {
		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
		BufferedReader fin = new BufferedReader(new FileReader("xtra.in"));
		PrintWriter fout = new PrintWriter(new FileWriter("xtra.out"), true);
		for (;;) {
			String x = fin.readLine();
			System.out.println(x); // will autoflush
			if (x.equals("0"))
				break;
			String s = stdin.readLine();
			fout.println(s); // will autoflush
		}
		fin.close();
		fout.close();
		System.exit(0); // must terminate with zero exit code
	}
}

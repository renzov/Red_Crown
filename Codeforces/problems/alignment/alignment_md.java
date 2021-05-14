import java.io.*;
import java.util.*;

public class alignment_md {
	private static String fileName = alignment_md.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static BufferedReader in;
	private static PrintWriter out;
	
	public void run() throws IOException {
		ArrayList<String[]> list = new ArrayList<String[]>();
		int m = 0;
		while (true) {
			String s = in.readLine();
			if (s == null) {
				break;
			}
			String[] ss = s.trim().split("\\s+");
			m = Math.max(m, ss.length);
			list.add(ss);
		}
		int[] w = new int[m];
		for (String[] ss : list) {
			for (int i = 0; i < ss.length; i++) {
				w[i] = Math.max(w[i], ss[i].length());
			}
		}
		for (String[] ss : list) {
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < ss.length; i++) {
				sb.append(ss[i]);
				for (int j = ss[i].length(); j <= w[i]; j++) {
					sb.append(' ');
				}
			}
			out.println(sb.toString().trim());
		}
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new BufferedReader(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new alignment_md().run();
		in.close();
		out.close();
	}
}

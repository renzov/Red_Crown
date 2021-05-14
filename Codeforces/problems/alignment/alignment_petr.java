import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class alignment_petr {
	public static void main(String[] args) throws FileNotFoundException {
		new alignment_petr().run();
	}

	public void run() throws FileNotFoundException {
		BufferedReader reader = new BufferedReader(new FileReader("alignment.in"));
		List<String[]> lines = new ArrayList<String[]>();
		while (true) {
			String line;
			try {
				line = reader.readLine().trim();
				if (line.length() == 0)
					break;
			} catch (Exception e) {
				break;
			}
			StringTokenizer tokenizer = new StringTokenizer(line);
			List<String> tokens = new ArrayList<String>();
			while (tokenizer.hasMoreTokens()) tokens.add(tokenizer.nextToken());
			lines.add(tokens.toArray(new String[0]));
		}
		List<Integer> p = new ArrayList<Integer>();
		p.add(0);
		for (int id = 1;; ++id) {
			int cp = -1;
			for (String[] line : lines)
				if (line.length >= id)
					cp = Math.max(cp, p.get(id - 1) + line[id - 1].length() + 1);
			if (cp < 0)
				break;
			p.add(cp);
		}
		PrintWriter out = new PrintWriter("alignment.out");
		for (String[] line : lines) {
			int at = 0;
			for (int id = 0; id < line.length; ++id) {
				while (at < p.get(id)) {
					++at;
					out.print(" ");
				}
				out.print(line[id]);
				at += line[id].length();
			}
			out.println();
		}
		out.close();
	}

}

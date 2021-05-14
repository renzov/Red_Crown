import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Solution for NEERC'2010 Problem A: Alignment of Code. 
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class alignment_re {
	private static final int MAX_WORD_LENGTH = 80;
	private static final int MAX_LINE_LENGTH = 180;
	private static final int MAX_LINE_COUNT = 1000;

	public static void main(String[] args) throws Exception {
		new alignment_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	private final List<List<String>> lines = new ArrayList<List<String>>();
	private final List<Integer> widths = new ArrayList<Integer>();

	void read() throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("alignment.in"), "UTF-8"));
		String line;
		int lc = 0;
		while ((line = in.readLine()) != null) {
			assert line.length() > 0 && line.length() <= MAX_LINE_LENGTH;
			lc++;
			assert lc <= MAX_LINE_COUNT;
			int j = 0;
			while (j < line.length() && line.charAt(j) == ' ')
				j++; // skip leading spaces
			String[] words = line.substring(j).split(" +"); // split will skip trailing spaces
			assert words.length > 0;
			for (String s : words) {
				assert s.length() > 0 && s.length() <= MAX_WORD_LENGTH;
				for (int i = 0; i < s.length(); i++)
					assert s.charAt(i) >= 33 && s.charAt(i) <= 126;
			}
			lines.add(Arrays.asList(words));
		}
		in.close();
	}

	void solve() {
		for (List<String> words : lines) {
			for (int i = 0; i < words.size(); i++) {
				if (i >= widths.size())
					widths.add(0);
				widths.set(i, Math.max(widths.get(i), words.get(i).length()));
			}
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("alignment.out", "UTF-8");
		for (List<String> words : lines) {
			for (int i = 0; i < words.size(); i++) {
				String s = words.get(i);
				out.print(s);
				if (i < words.size() - 1) // if not the last
					for (int j = s.length(); j <= widths.get(i); j++)
						out.print(' ');
			}
			out.println();
		}
		out.close();
	}
}

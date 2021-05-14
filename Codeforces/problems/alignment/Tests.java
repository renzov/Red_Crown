import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Tests generator for NEERC'2010 Problem A: Alignment of Code.
 * @author Roman Elizarov
 */
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

	private static final int MAX_WORD_LENGTH = 80;
	private static final int MAX_LINE_LENGTH = 180;
	private static final int MAX_LINE_COUNT = 1000;
	
	private static final Random RND = new Random(20101113);

	private final PrintWriter out;

	private Tests(String description) throws IOException {
		String tn = String.format("%02d", ++TEST_COUNTER);
		File tests = new File("tests");
		tests.mkdir();
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + description);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(tests, tn)));
	}

	private final List<String> lines = new ArrayList<String>();

	private Tests line(String line) {
		lines.add(line);
		return this;
	}

	private void write() {
		for (String line : lines)
			out.println(line);
		out.close();
	}

	private void randomLine(int wc, int wl, int sc) {
		StringBuilder sb = new StringBuilder();
		addSpace(sb, RND.nextInt(sc + 1)); // leading space
		int n = RND.nextInt(wc) + 1;
		for (int i = 0; i < n; i++) {
			int m = RND.nextInt(wl) + 1;
			for (int j = 0; j < m && sb.length() < MAX_LINE_LENGTH; j++)
				sb.append(randomChar());
			if (i < n - 1)
				addSpace(sb, sc == 0 ? 1 : (RND.nextInt(sc) + 1)); // intra word space
			else
				addSpace(sb, RND.nextInt(sc + 1)); // trailing space
		}
		line(sb.toString());
	}

	private static char randomChar() {
		return (char)(33 + RND.nextInt(126 - 33 + 1));
	}

	private static void addSpace(StringBuilder sb, int sc) {
		while (sb.length() < MAX_LINE_LENGTH && sc > 0) {
			sb.append(' ');
			sc--;
		}
	}

	private static void randomTest(int lc, int wc, int wl, int sc) throws IOException {
		Tests t = new Tests(String.format("Random %d lines, %d words on a line, %d max len, %d max spaces", lc, wc, wl, sc));
		for (int i = 0; i < lc; i++)
			t.randomLine(wc, wl, sc);
		t.write();
	}

	private static void maxTest(int wl) throws IOException {
		Tests t = new Tests(String.format("Max test with %d max len words", wl));
		for (int i = 0; i < MAX_LINE_COUNT; i++) {
			StringBuilder sb = new StringBuilder();
			if (RND.nextBoolean()) // one trailing or leading space
				sb.append(' ');
			int longWordIndex = i % (MAX_LINE_LENGTH / 2);
			int wi = 0;
			while (sb.length() < MAX_LINE_LENGTH) {
				if (wi == longWordIndex) {
					for (int j = 0; j < wl && sb.length() < MAX_LINE_LENGTH; j++)
						sb.append(randomChar());
				} else
					sb.append(randomChar());
				wi++;
				if (sb.length() < MAX_LINE_LENGTH)
					sb.append(' ');
			}
			t.line(sb.toString());
		}
		t.write();
	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		new Tests("First sample")
				.line("  start:  integer;    // begins here")
				.line("stop: integer; //  ends here  ")
				.line(" s:  string;   ")
				.line("c:   char; // temp ")
				.write();
		new Tests("Shortest one line of word")
				.line("a")
				.write();
		new Tests("Small triangle")
				.line("1111")
				.line("1 2222")
				.line("1 2 3333")
				.line("1 2 3 4444")
				.write();
		// few small random tests
		randomTest(13, 15, 10, 0); // no spaces
		randomTest(15, 11, 10, 5); // few spaces
		// a set of quite large random tests
		randomTest(MAX_LINE_COUNT, 60, MAX_WORD_LENGTH, 0); // long words, no space
		randomTest(MAX_LINE_COUNT, 60, MAX_WORD_LENGTH, 3); // long words, a little bit of space
		randomTest(MAX_LINE_COUNT, 60, MAX_WORD_LENGTH, MAX_LINE_LENGTH / 2); // long words, lots of space
		randomTest(MAX_LINE_COUNT, 60, MAX_WORD_LENGTH, MAX_LINE_LENGTH - 1); // long words, even more space
		randomTest(MAX_LINE_COUNT, 60, 1, 0); // one letter words, no space
		randomTest(MAX_LINE_COUNT, 60, 6, 0); // short words, no space
		randomTest(MAX_LINE_COUNT, 60, 6, 5); // short words, a little bit of space
		randomTest(MAX_LINE_COUNT, 60, 2, MAX_LINE_LENGTH - 1); // very short words, lots of space
		// max tests
		maxTest(1); // short words
		maxTest(MAX_WORD_LENGTH); // long words
	}
}

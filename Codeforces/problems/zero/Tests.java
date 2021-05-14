import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
    Tests generator for NEERC'2010 Problem Z: Zero-complexity Transposition.
    @author Roman Elizarov
*/
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");
	private static final Random RND = new Random(20101107);

	private static final long MAX = 1000000000000000L;

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

	private void write(long[] data) {
		int n = data.length;
		out.println(n);
		for (int i = 0; i < n; i++) {
			if (i > 0)
				out.print(' ');
			out.print(data[i]);
		}
		out.println();
		out.close();
	}

	private long nextLong(long n) {
		if (n <= 1)
			return 0;
		long mask = (Long.highestOneBit(n) << 1) - 1;
		long result;
		do {
			result = RND.nextLong() & mask;
		} while (result >= n);
		return result;
	}

	private long nextLong(long from, long to) {
		return from + nextLong(to - from + 1);
	}

	private void rndRange(int n, long from, long to, boolean binary) {
		long[] data = new long[n];
		for (int i = 0; i < n; i++)
			data[i] = binary ? RND.nextBoolean() ? from : to : nextLong(from, to);
		write(data);
	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		new Tests("First sample").write(new long[] {1, 2, 3});
		new Tests("Second sample").write(new long[] {-3, 4, 6, -8, 9});
		new Tests("Just one number").write(new long[] {13});
		new Tests("1234 small numbers (-1000 1000)").rndRange(1234, -1000, 1000, false);
		new Tests("9999 min or max number (randomly)").rndRange(9999, -MAX, +MAX, true);
		new Tests("10000 random numbers from the full range").rndRange(10000, -MAX, +MAX, false);
		new Tests("10000 min values").rndRange(10000, -MAX, -MAX, false);
		new Tests("10000 max values").rndRange(10000, +MAX, +MAX, false);
	}
}
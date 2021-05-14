import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
    Tests generator for NEERC'2010 Problem X: Xtrapolation.
    @author Roman Elizarov
*/
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");
	private static final Random RND = new Random(20101108);

	private static final int MAX = 1000000000;

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

	private void write(int[] data) {
		for (int i : data)
			out.println(i);
		out.println(0);
		out.close();
	}

	private void rndRange(int n, int from, int to) {
		int[] data = new int[n];
		for (int i = 0; i < n; i++)
			data[i] = from + RND.nextInt(to - from + 1);
		write(data);
	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		new Tests("First sample").write(new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
		new Tests("Just one number").write(new int[] {1});
		new Tests("3 times 10^9").rndRange(3, MAX, MAX);
		new Tests("1000 random numbers from 1 to 2000").rndRange(1000, 1, 2000);
		new Tests("1000 times 10^9").rndRange(1000, MAX, MAX);
		new Tests("1000 random numbers from 1 to 10^9").rndRange(1000, 1, MAX);
		new Tests("1000 random numbers from 1 to 10^9").rndRange(1000, 1, MAX);
		new Tests("999 random numbers from 10^8 to 10^9").rndRange(999, MAX / 10, MAX);
	}
}
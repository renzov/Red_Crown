import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

/**
    Tests generator for NEERC'2010 Problem Y: Yield.
    @author Roman Elizarov
*/
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

	private final PrintWriter out;

	private final int a;
	private final int b;

	private Tests(int a, int b) throws IOException {
		this.a = a;
		this.b = b;
		String tn = String.format("%02d", ++TEST_COUNTER);
		File tests = new File("tests");
		tests.mkdir();
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + a + " " + b);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(tests, tn)));
	}

	private void write() {
		out.println(a + " " + b);
		out.close();
	}
	
	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		new Tests(1, 2).write();
		new Tests(1, -1).write();
		new Tests(2, 3).write();
		new Tests(17, -18).write();
		new Tests(1000, 1000).write();
		new Tests(-1000, -1000).write();
		new Tests(1000, -1000).write();
		new Tests(-1000, 1000).write();
		new Tests(-999, 876).write();
		new Tests(543, -210).write();
	}
}
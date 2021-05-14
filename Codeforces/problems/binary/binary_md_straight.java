import java.io.*;
import java.util.*;

public class binary_md_straight {
	private static String fileName = binary_md_straight.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	private static final int BASE = 10;
	
	
	public void run() {
		int[][] op = new int[BASE][BASE];
		for (int i = 0; i < BASE; i++) {
			for (int j = 0; j < BASE; j++) {
				op[i][j] = in.nextInt();
			}
		}
		long a = in.nextLong();
		long b = in.nextLong();
		for (long i = a + 1; i <= b; i++) {
			a = digitwise(a, i, op);
		}
		out.println(a);
	}

	private long digitwise(long a, long b, int[][] op) {
		if (a == 0 && b == 0) {
			return 0;
		}
		return digitwise(a / BASE, b / BASE, op) * BASE + op[(int) (a % BASE)][(int) (b % BASE)];
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new binary_md_straight().run();
		in.close();
		out.close();
	}
}

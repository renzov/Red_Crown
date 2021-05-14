import java.io.*;
import java.util.*;

public class Tests {
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(5516681322906813814L);

	private static final long MAX = 1000000000000000000L;
	private static final int MAX2 = (int) Math.sqrt(MAX);
	private static final int BASE = 10;

	public void run() {
		int[][] plus = linear(1, 1, 0);
		int[][] mult = mult();
		t(plus, 0, 10);
		t(linear(0, 0, 0), 42, 566);
		t(mult, 613, 987);
		t(plus, 97, 103);
		t(plus, 6, 2040);
		t(mult, 498, 502);
		t(linear(2, 3, 4), 25088, 80252);
		for (int t = 0; t < 12; t++) {
			t(rnd(), r.nextInt(1000), (long) Math.pow(10, t));
		}
		t(linear(0, 0, 0), 3, MAX / 13);
		t(linear(1, 0, 0), 42, MAX - 42);
		t(linear(0, 1, 0), 7, nextLong());
		t(linear(0, 0, 7), nextLong(), nextLong());
		for (int t = 10; t < 18; t++) {
			t(rnd(), nextLong() % (long) Math.pow(10, t), nextLong() % (long) Math.pow(10, t));
			t(linear(1 + r.nextInt(9), 1 + r.nextInt(9), r.nextInt(10)), nextLong() % (long) Math.pow(10, t), nextLong() % (long) Math.pow(10, t));
		}
		t(plus, nextLong(), nextLong());
		for (int t = 0; t < 10; t++) {
			t(rnd(), r.nextInt(1000), MAX - r.nextInt(1000));
		}
		{
			int[][] op = new int[BASE][BASE];
			for (int i = 0; i < BASE; i++) {
				for (int j = 0; j < BASE; j++) {
					op[i][j] = (j == 0 || j >= 7) ? 0 : j;
				}
			}
			t(op, 654321, 98764321098764321L);
			for (int i = 0; i < BASE; i++) {
				for (int j = 0; j < BASE; j++) {
					op[i][j] = (j == 0 || j >= 5) ? 0 : 1 + r.nextInt(9);
				}
			}
			t(op, MAX / 10, 998877665544332211L);
		}
		t(linear(7, 5, 5), MAX / 7, MAX);
		t(linear(1, 5, 4), MAX / 17, MAX);
		t(linear(0, 0, 9), 0, MAX);
	}
	
	private long nextLong() {
		return r.nextInt(MAX2) * (long) MAX2 + r.nextInt(MAX2);
	}

	int[][] linear(int a, int b, int c) {
		int[][] op = new int[BASE][BASE];
		for (int i = 0; i < BASE; i++) {
			for (int j = 0; j < BASE; j++) {
				op[i][j] = (a * i + b * j + c) % BASE;
			}
		}
		op[0][0] = 0;
		return op;
	}
	
	private int[][] mult() {
		int[][] op = new int[BASE][BASE];
		for (int i = 0; i < BASE; i++) {
			for (int j = 0; j < BASE; j++) {
				op[i][j] = (i * j) % BASE;
			}
		}
		op[0][0] = 0;
		return op;
	}

	int[][] rnd() {
		int[][] op = new int[BASE][BASE];
		for (int i = 0; i < BASE; i++) {
			for (int j = 0; j < BASE; j++) {
				op[i][j] = (i == 0 && j == 0) ? 0 : r.nextInt(10);
			}
		}
		return op;
	}
	
	private void t(int[][] op, long a, long b) {
		open();
		for (int[] line : op) {
			for (int i = 0; i < line.length; i++) {
				if (i > 0) {
					out.print(" ");
				}
				out.print(line[i]);
			}
			out.println();
		}
		out.println(Math.min(a, b) + " " + Math.max(a, b));
		close();
	}

	private void open() {
		try {
			testName = "" + curTest / 10 + curTest % 10;
			out = new PrintWriter(new File(dir, testName));
			if (verbose) { 
				System.out.print("Generating " + testName + "... ");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		if (verbose) {
			System.out.println("done.");
		}
		curTest++;
	}

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		dir.mkdirs();
		new Tests().run();
	}
}

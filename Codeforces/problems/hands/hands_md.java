import java.io.*;
import java.util.*;

public class hands_md {
	private static String fileName = hands_md.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;
	final static String ranks = "23456789TJQKA";
	final static int m = ranks.length();
	final static int n = 5;

	public void run() {
		TreeSet<Integer> values = new TreeSet<Integer>();
		int[] a = new int[n];
		for (int f = 0; f < 2; f++) {
			for (a[0] = 0; a[0] < m; a[0]++) {
				for (a[1] = a[0] + f; a[1] < m; a[1]++) {
					for (a[2] = a[1] + f; a[2] < m; a[2]++) {
						for (a[3] = a[2] + f; a[3] < m; a[3]++) {
							for (a[4] = a[3] + f; a[4] < m; a[4]++) {
								if (a[0] == a[4]) {
									continue;
								}
								values.add(eval(a, f > 0));
							}
						}
					}
				}
			}
		}

		int[] rank = new int[n];
		char suit0 = 0;
		boolean flush = true;
		for (int i = 0; i < n; i++) {
			String s = in.next();
			rank[i] = ranks.indexOf(s.charAt(0));
			if (i == 0) {
				suit0 = s.charAt(1);
			} else if (s.charAt(1) != suit0) {
				flush = false;
			}
		}
		int v = eval(rank, flush);
		out.println(values.headSet(v).size() + 1);
	}

	final static int r = 1000000;
	
	public static int eval(int[] rank, boolean flush) {
		Map<Integer, Integer> count = new HashMap<Integer, Integer>();
		for (int x : rank) {
			count.put(x, count.containsKey(x) ? count.get(x) + 1 : 1);
		}
		@SuppressWarnings("unchecked")
		ArrayList<Integer>[] a = new ArrayList[n + 1];
		for (int y = 0; y <= n; y++) {
			a[y] = new ArrayList<Integer>();
		}
		for (int x : count.keySet()) {
			a[count.get(x)].add(x);
		}
		boolean straight = false;
		int straightHi = 0;
		if (a[1].size() == 5) {
			if (a[1].get(0) + 4 == a[1].get(4)) {
				straight = true;
				straightHi = a[1].get(4);
			}
			if (a[1].get(3) == 3 && a[1].get(4) == m - 1) {
				straight = true;
				straightHi = 3;
			}
		}
		int v = 10 * r;
		if (straight && flush) {
			return v + straightHi;
		}
		v -= r;
		if (a[4].size() == 1) {
			return v + m * a[4].get(0) + a[1].get(0);
		}
		v -= r;
		if (a[3].size() == 1 && a[2].size() == 1) {
			return v + m * a[3].get(0) + a[2].get(0);
		}
		v -= r;
		if (flush) {
			return v + m * m * m * m * a[1].get(4) + m * m * m * a[1].get(3) + m * m * a[1].get(2) + m * a[1].get(1) + a[1].get(0);
		}
		v -= r;
		if (straight) {
			return v + straightHi;
		}
		v -= r;
		if (a[3].size() == 1) {
			return v + m * m * a[3].get(0) + m * a[1].get(1) + a[1].get(0);
		}
		v -= r;
		if (a[2].size() == 2) {
			return v + m * m * a[2].get(1) + m * a[2].get(0) + a[1].get(0);
		}
		v -= r;
		if (a[2].size() == 1) {
			return v + m * m * m * a[2].get(0) + m * m * a[1].get(2) + m * a[1].get(1) + a[1].get(0);
		}
		v -= r;
		return v + m * m * m * m * a[1].get(4) + m * m * m * a[1].get(3) + m * m * a[1].get(2) + m * a[1].get(1) + a[1].get(0);
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new hands_md().run();
		in.close();
		out.close();
	}
}

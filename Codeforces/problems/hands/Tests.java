import java.io.*;
import java.util.*;

public class Tests {
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(5572445238158L);

	final static String ranks = hands_md.ranks;
	final static String suits = "HDCS";
	final static int n = hands_md.n;
	final static int m = hands_md.m;
	
	class Hand {
		int[] rank;
		boolean flush;

		public Hand(boolean flush, int... rank) {
			this.rank = rank;
			this.flush = flush;
		}
	}

	public void run() {
		TreeMap<Integer, Hand> values = new TreeMap<Integer, Hand>();
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
								values.put(hands_md.eval(a, f > 0), new Hand(f > 0, a.clone()));
							}
						}
					}
				}
			}
		}
		Integer vs[] = values.keySet().toArray(new Integer[0]);
		Hand[] hands = values.values().toArray(new Hand[0]);
		int h = hands.length;
		t(hands[0]);
		t(hands[h - 1]);
		for (int t = 11, i = 1; i < t; i++) {
			t(hands[h * i / t]);
		}
		for (boolean f : new boolean[]{false, true}) {
			t(new Hand(f, 12, 11, 2, 1, 0));
			t(new Hand(f, 12, 11, 10, 9, 0));
		}
		ArrayList<Integer> rs = new ArrayList<Integer>();
		for (int i = 0; i < h; i++) {
			if (i == 0 || vs[i] - vs[i - 1] > hands_md.r / 2) {
				rs.add(i);
			}
		}
		for (int i = 0; i < rs.size(); i++) {
			int lo = rs.get(i);
			int hi = (i + 1 == rs.size()) ? h : rs.get(i + 1);
			if (lo > 0) t(hands[lo]);
			t(hands[r.nextBoolean() ? lo + 1 : hi - 2]);
			t(hands[lo + 2 + r.nextInt(hi - lo - 4)]);
			if (hi < h) t(hands[hi - 1]);
		}
	}

	private void t(Hand h) {
		t(h, true, r.nextBoolean());
	}
	
	private void t(Hand h, boolean shuffle, boolean anySuits) {
		String[] s = new String[n];
		if (h.flush) {
			char s1 = suits.charAt(r.nextInt(suits.length()));
			for (int i = 0; i < n; i++) {
				s[i] = "" + ranks.charAt(h.rank[i]) + s1;
			}
		} else if (anySuits) {
			for (int i = 0; i < n; i++) {
				while (true) {
					s[i] = "" + ranks.charAt(h.rank[i]) + suits.charAt(r.nextInt(suits.length()));
					boolean repeat = false;
					for (int j = 0; j < i; j++) {
						if (s[j].equals(s[i])) {
							repeat = true;
						}
					}
					if (!repeat) {
						break;
					}
				}
			}
		} else {
			char s1 = suits.charAt(r.nextInt(suits.length()));
			boolean flush = true;
			for (int i = 0; i < n; i++) {
				for (char c = s1;; c = suits.charAt(r.nextInt(suits.length())), flush = false) {
					s[i] = "" + ranks.charAt(h.rank[i]) + c;
					boolean repeat = false;
					for (int j = 0; j < i; j++) {
						if (s[j].equals(s[i])) {
							repeat = true;
						}
					}
					if (!repeat) {
						break;
					}
				}
			}
			if (flush) {
				int i = r.nextInt(n);
				char s2;
				do {
					s2 = suits.charAt(r.nextInt(suits.length()));
				} while (s2 == s1);
				s[i] = "" + ranks.charAt(h.rank[i]) + s2;
			}
		}
		if (shuffle) {
			Collections.shuffle(Arrays.asList(s), r);
		}
		t(s);
	}
	
	private void t(String... s) {
		open();
		out.println(s[0] + " " + s[1] + " " + s[2] + " " + s[3] + " " + s[4]);
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

import java.io.*;
import java.util.*;

public class ideal_md {
	private static String fileName = ideal_md.class.getSimpleName().replaceFirst("_.*", "");
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;

	public void run() {
		int n = in.nextInt();
		int m = in.nextInt();
		ArrayList<Integer>[] nei = new ArrayList[n];
		ArrayList<Integer>[] col = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			nei[i] = new ArrayList<Integer>();
			col[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < m; i++) {
			int a = in.nextInt() - 1;
			int b = in.nextInt() - 1;
			int c = in.nextInt();
			nei[a].add(b);
			nei[b].add(a);
			col[a].add(c);
			col[b].add(c);
		}
		int[] dist = new int[n];
		Arrays.fill(dist, Integer.MAX_VALUE / 2);
		dist[n - 1] = 0;
		int[] queue = new int[n];
		int low = 0;
		int high = 1;
		queue[0] = n - 1;
		while (low < high) {
			int a = queue[low++];
			for (int b : nei[a]) {
				if (dist[b] > dist[a] + 1) {
					dist[b] = dist[a] + 1;
					queue[high++] = b;
				}
			}
		}
		out.println(dist[0]);
		Collection<Integer> cur = new ArrayList<Integer>();
		cur.add(0);
		for (int d = dist[0]; d > 0; d--) {
			Collection<Integer> next = new HashSet<Integer>();
			int best = Integer.MAX_VALUE;
			for (int a : cur) {
				for (int i = 0; i < nei[a].size(); i++) {
					int b = nei[a].get(i);
					int c = col[a].get(i);
					if (dist[b] != d - 1) {
						continue;
					}
					if (c < best) {
						best = c;
						next.clear();
						next.add(b);
					} else if (c == best) {
						next.add(b);
					}
				}
			}
			out.print(best + " ");
			cur = next;
		}
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new ideal_md().run();
		in.close();
		out.close();
	}
}

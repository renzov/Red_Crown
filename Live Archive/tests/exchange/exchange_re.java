/*
    Solution for NEERC'2006 Problem E: Exchange
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;
import java.util.*;

public class exchange_re {
	public static void main(String[] args) throws Exception {
		new exchange_re().go();
	}

	enum Side {
		BUY(1), SELL(-1);

		int mul;

		Side(int mul) {
			this.mul = mul;
		}
	}

	static class Order implements Comparable<Order> {
		int id;
		Side side;
		int q;
		int p;

		Order(int id, Side side, int q, int p) {
			this.id = id;
			this.side = side;
			this.q = q;
			this.p = p;
		}

		public int compareTo(Order o) {
			int i = side.compareTo(o.side);
			if (i != 0)
				return i;
			i = (o.p - p) * side.mul;
			if (i != 0)
				return i;
			i = id - o.id;
			return i;
		}
	}

	List<Order> oid = new ArrayList<Order>();
	Queue<Order> pqb = new PriorityQueue<Order>();
	Queue<Order> pqs = new PriorityQueue<Order>();
	Map<Integer, Integer> ss = new HashMap<Integer, Integer>();


	void go() throws Exception {
		Scanner in = new Scanner(new File("exchange.in"));
		PrintStream out = new PrintStream(new File("exchange.out"));

		int n = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= 10000;
		oid.add(null);

		for (int i = 1; i <= n; i++) {
			String act = in.next();
			if (act.equals("CANCEL")) {
				int id = in.nextInt();
				assert id >= 1 && id < i;
				Order o = oid.get(id);
				assert o != null;
				adjust(o.p, -o.q);
				o.q = 0;
				oid.add(null);
			} else {
				int q = in.nextInt();
				int p = in.nextInt();
				assert q >= 1 && q <= 99999;
				assert p >= 1 && p <= 99999;
				Order o = new Order(i, Side.valueOf(act), q, p);
				oid.add(o);
				trade(out, o);
				if (o.q > 0) {
					switch (o.side) {
						case BUY:
							pqb.add(o);
							break;
						case SELL:
							pqs.add(o);
							break;
					}
					adjust(o.p, o.q);
				}

			}
			in.nextLine();
			quote(out);
		}
		in.close();
		out.close();
	}

	void adjust(int p, int q) {
		if (q == 0)
			return;
		Integer sq = ss.get(p);
		if (sq == null)
			ss.put(p, q);
		else
			ss.put(p, q + sq);
	}

	void trade(PrintStream out, Order o) {
		Queue<Order> pq;
		switch (o.side) {
			case BUY:
				pq = pqs;
				break;
			case SELL:
				pq = pqb;
				break;
			default:
				return;
		}
		while (o.q > 0) {
			Order m = getTop(pq);
			if (m == null || o.side.mul * (m.p - o.p) > 0)
				break;
			int q = Math.min(o.q, m.q);
			// out.printf("TRADE %d %d%n", q, m.p);
			out.print("TRADE ");
			out.print(q);
			out.print(" ");
			out.println(m.p);
			m.q -= q;
			o.q -= q;
			adjust(m.p, -q);
		}
	}

	void quote(PrintStream out) {
		// out.printf(" %d %d", q, p);
		out.print("QUOTE");
		priceSize(out, pqb, 0);
		out.print(" -");
		priceSize(out, pqs, 99999);
		out.println();
	}

	Order getTop(Queue<Order> pq) {
		while (true) {
			Order o = pq.peek();
			if (o == null || o.q > 0)
				return o;
			pq.poll();
		}
	}

	void priceSize(PrintStream out, Queue<Order> pq, int defp) {
		Order o = getTop(pq);
		int q;
		int p;
		if (o == null) {
			q = 0;
			p = defp;
		} else {
			q = ss.get(o.p);
			p = o.p;
		}
		out.print(" ");
		out.print(q);
		out.print(" ");
		out.print(p);
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could added to a soulution source
	 * without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public static class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}


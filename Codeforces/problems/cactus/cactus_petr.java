import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.List;

/**
 * @author Egor Kulikov (egor@egork.net)
 *         Created on 14.03.2010
 */
public class cactus_petr {
	static int colorToUse = 0;

	static class Vertex {
		List<Edge> outgo = new ArrayList<Edge>();
		List<Cycle> onCycle = new ArrayList<Cycle>();
		int stackPos = -1;
		boolean visited = false;
		int color = -1;
		int id;

		Vertex(int id) {
			this.id = id;
		}

		public void dfs(Vertex parent) {
			if (visited)
				return;
			if (stackPos >= 0) {
				Cycle found = new Cycle();
				for (int i = stackPos; i < globalDfsStack.size(); ++i) {
					found.items.add(globalDfsStack.get(i));
					Edge e = globalDfsEdgeStack.get(i);
					e.isOnCycle = true;
					e.rev.isOnCycle = true;
				}
				found.notifyVertices();
				return;
			}
			stackPos = globalDfsStack.size();
			globalDfsStack.add(this);
			for (Edge e : outgo) {
				if (e.dst == parent)
					continue;
				globalDfsEdgeStack.add(e);
				e.dst.dfs(this);
				globalDfsEdgeStack.remove(globalDfsEdgeStack.size() - 1);
			}
			globalDfsStack.remove(stackPos);
			stackPos = -1;
			visited = true;
		}

		public void colorIt(int color, Vertex parent, Cycle parentCycle) {
			if (this.color != -1) {
				return;
			}
			this.color = color;
			for (Edge e : outgo)
				if (!e.isOnCycle) {
					if (e.dst == parent)
						continue;
					e.dst.colorIt(color, this, null);
				}
			for (Cycle cycle : onCycle) {
				if (cycle == parentCycle)
					continue;
				cycle.colorIt(this, color);
			}
		}

		public int solve(int partSize, Vertex parent, Cycle parentCycle) {
			int totalExtra = 0;
			for (Edge e : outgo)
				if (!e.isOnCycle) {
					if (e.dst == parent)
						continue;
					int extra = e.dst.solve(partSize, this, null);
					if (extra < 0)
						return -1;
					totalExtra += extra;
				}
			for (Cycle cycle : onCycle) {
				if (cycle == parentCycle)
					continue;
				int extra = cycle.solve(this, partSize);
				if (extra < 0)
					return -1;
				totalExtra += extra;
			}
			if (totalExtra >= partSize)
				return -1;
			if (totalExtra + 1 == partSize) {
				colorIt(colorToUse++, parent, parentCycle);
				return 0;
			}
			return totalExtra + 1;
		}
	}

	static List<Vertex> globalDfsStack = new ArrayList<Vertex>();
	static List<Edge> globalDfsEdgeStack = new ArrayList<Edge>();

	static class Edge {
		Vertex src;
		Vertex dst;
		Edge rev;
		boolean isOnCycle = false;

		Edge(Vertex src, Vertex dst) {
			this.src = src;
			this.dst = dst;
		}
	}

	static class Cycle {
		List<Vertex> items = new ArrayList<Vertex>();

		public void notifyVertices() {
			for (Vertex v : items)
				v.onCycle.add(this);
		}

		public void colorIt(Vertex root, int color) {
			for (Vertex v : items)
				if (v.color == -1) {
					v.colorIt(color, null, this);
				}
		}

		static class NumberWithRem implements Comparable<NumberWithRem> {
			int number;
			int rem;

			NumberWithRem(int number, int rem) {
				this.number = number;
				this.rem = rem;
			}

			public int compareTo(NumberWithRem o) {
				int z = rem - o.rem;
				if (z == 0) z = number - o.number;
				return z;
			}
		}

		public int solve(Vertex root, int partSize) {
			List<Vertex> items = new ArrayList<Vertex>();
			int rootIndex = this.items.indexOf(root);
			for (int i = 0; i < this.items.size() - 1; ++i) {
				items.add(this.items.get((rootIndex + 1 + i) % this.items.size()));
			}
			int n = items.size();
			int[] extra = new int[n];
			for (int i = 0; i < n; ++i) {
				extra[i] = items.get(i).solve(partSize, null, this);
				if (extra[i] < 0)
					return -1;
			}
			int[] extraSum = new int[n + 1];
			int rem = -1;
			for (int i = 0; i < n; ++i) {
				if (extra[i] == 0) {
					int newRem = extraSum[i] % partSize;
					if (rem >= 0 && newRem != rem) {
						return -1;
					}
					rem = newRem;
				}
				extraSum[i + 1] = extraSum[i] + extra[i];
			}
			NumberWithRem[] numbers = new NumberWithRem[n + 1];
			for (int i = 0; i <= n; ++i)
				numbers[i] = new NumberWithRem(extraSum[i], extraSum[i] % partSize);
			Arrays.sort(numbers);
			int pos = 0;
			while (pos < numbers.length) {
				int last = pos;
				while (last < n && numbers[last + 1].rem == numbers[last].rem && numbers[last + 1].number <= numbers[last].number + partSize)
					++last;
				if (rem != -1 && numbers[pos].rem != rem) {
					pos = last + 1;
					continue;
				}
				int totalExtra = numbers[pos].number + extraSum[n] - numbers[last].number;
				if (totalExtra < partSize) {
					for (int i = 0; i <= n; ++i)
						if (extraSum[i] == numbers[pos].number) {
							int color = -1;
							for (int j = i; j <= n; ++j) {
								if (extraSum[j] == numbers[last].number)
									break;
								if (extra[j] == 0)
									continue;
								if (extraSum[j] % partSize == numbers[pos].rem)
									color = colorToUse++;
								items.get(j).colorIt(color, null, this);
							}
                            break;
						}
					return totalExtra;
				}
				pos = last + 1;
			}
			return -1;
		}
	}

	public void run() {
		int n = in.readInt();
		Vertex[] v = new Vertex[n];
		for (int i = 0; i < n; ++i) {
			v[i] = new Vertex(i + 1);
		}
		int m = in.readInt();
		int k = in.readInt();
		for (int i = 0; i < m; ++i) {
			int s = in.readInt();
			int cur = in.readInt() - 1;
			for (int j = 0; j < s - 1; ++j) {
				int a = cur;
				int b = in.readInt() - 1;
				Edge ab = new Edge(v[a], v[b]);
				v[a].outgo.add(ab);
				Edge ba = new Edge(v[b], v[a]);
				v[b].outgo.add(ba);
				ab.rev = ba;
				ba.rev = ab;
				cur = b;
			}
		}
		if (n % k != 0)
			throw new RuntimeException();
		solve(v, n / k);
	}

	private void solve(Vertex[] v, int partSize) {
		buildCycles(v);
		int extra = v[0].solve(partSize, null, null);
		if (extra < 0) {
			out.println(-1);
		} else {
			if (extra != 0)
				throw new RuntimeException();
			List<List<Vertex>> parts = new ArrayList<List<Vertex>>();
			for (int i = 0; i < colorToUse; ++i) {
				parts.add(new ArrayList<Vertex>());
			}
			for (Vertex vertex : v)
				parts.get(vertex.color).add(vertex);
			for (List<Vertex> part : parts) {
				boolean first = true;
				for (Vertex vertex : part) {
					if (first) first = false; else out.print(" ");
					out.print(vertex.id);
				}
				out.println();
			}
		}
	}

	private void buildCycles(Vertex[] v) {
		for (Vertex x : v) {
			if (!x.visited) x.dfs(null);
		}
	}

	private InputReader in;
	private PrintWriter out;

	public static void main(String[] args) {
		cactus_petr solver = new cactus_petr();
		solver.run();
		solver.out.close();
	}

	public cactus_petr() {
		String id = getClass().getName().substring(0, getClass().getName().indexOf('_')).toLowerCase();
		try {
			System.setIn(new FileInputStream(id + ".in"));
			System.setOut(new PrintStream(new FileOutputStream(id + ".out")));
//			System.setIn(new FileInputStream("input.txt"));
//			System.setOut(new PrintStream(new FileOutputStream("output.txt")));
		} catch (FileNotFoundException e) {
			throw new RuntimeException();
		}
		in = new InputReader(System.in);
		out = new PrintWriter(System.out);
	}

	private static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar, numChars;

		public InputReader(InputStream stream) {
			this.stream = stream;
		}

		private int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public int readInt() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public long readLong() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			long res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public String readString() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuffer res = new StringBuffer();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		private String readLine0() {
			StringBuffer buf = new StringBuffer();
			int c = read();
			while (c != '\n' && c != -1) {
				buf.appendCodePoint(c);
				c = read();
			}
			return buf.toString();
		}

		public String readLine() {
			String s = readLine0();
			while (s.trim().length() == 0)
				s = readLine0();
			return s;
		}

		public String readLine(boolean ignoreEmptyLines) {
			if (ignoreEmptyLines)
				return readLine();
			else
				return readLine0();
		}

		public BigInteger readBigInteger() {
			try {
				return new BigInteger(readString());
			} catch (NumberFormatException e) {
				throw new InputMismatchException();
			}
		}

		public char readCharacter() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			return (char) c;
		}

		public double readDouble() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			double res = 0;
			while (!isSpaceChar(c) && c != '.') {
				if (c < '0' || c > '9') {
					if (c == 'e' || c == 'E') {
						int e = readInt();
						return res * Math.pow(10, e);
					}
					throw new InputMismatchException();
				}
				res *= 10;
				res += c - '0';
				c = read();
			}
			if (c == '.') {
				c = read();
				double m = 1;
				while (!isSpaceChar(c)) {
					if (c == 'e' || c == 'E') {
						int e = readInt();
						return res * Math.pow(10, e);
					}
					if (c < '0' || c > '9')
						throw new InputMismatchException();
					m /= 10;
					res += (c - '0') * m;
					c = read();
				}
			}
			return res * sgn;
		}
	}
}

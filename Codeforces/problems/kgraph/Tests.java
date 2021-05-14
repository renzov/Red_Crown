import java.io.*;
import java.util.*;

/**
    Tests generator for NEERC'2010 Problem K: K-Graph Oddity.
    @author Maxim Babenko
*/
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");
	private static final Random RND = new Random(112742398);

	private final PrintWriter out;
	private final int nodeCount;
	
	private static class Edge {
		public int a;
		public int b;

		@Override
		public boolean equals(Object obj) {
			if (!(obj instanceof Edge)) {
				return false;
			}
			Edge other = (Edge) obj;
			return a == other.a && b == other.b || a == other.b && b == other.a;
		}

		@Override
		public int hashCode() {
			return Math.min(a, b) + 173 * Math.max(a, b);
		}
	}

	private List<Edge> edges = new ArrayList<Edge>();
	private Set<Edge> edgeSet = new HashSet<Edge>();
	private int[] degrees;

	private Tests(String description, int nodeCount) throws IOException {
		assert nodeCount % 2 == 1;
		this.nodeCount = nodeCount;
		degrees = new int[nodeCount];
		String tn = String.format("%02d", ++TEST_COUNTER);
		File tests = new File("tests");
		tests.mkdir();
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + description);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(tests, tn)));
	}

	private void write() {
		out.print(nodeCount);
		out.print(" ");
		out.print(edges.size());
		out.println();

		for (int i = 0; i < edges.size(); i++) {
			out.print(edges.get(i).a + 1);
			out.print(" ");
			out.print(edges.get(i).b + 1);
			out.println();
		}
		out.close();
	}

	private Tests shuffleNodes() {
		ArrayList<Integer> perm = new ArrayList<Integer>();
		for (int i = 0; i < nodeCount; i++) {
			perm.add(i);
		}
		Collections.shuffle(perm, RND);
		for (int i = 0; i < edges.size(); i++) {
			Edge edge = edges.get(i);
			edge.a = perm.get(edge.a);
			edge.b = perm.get(edge.b);
		}
		return this;
	}

	private Tests shuffleEdges() {
		Collections.shuffle(edges, RND);
		return this;
	}

	private Tests addRandomEdges1(int minDegree, int maxDegree) {
		for (int i = 0; i < nodeCount; i++) {
			int degree = minDegree + RND.nextInt(maxDegree - minDegree + 1);
			for (int j = 0; j < degree; j++) {
				Edge e = new Edge();
				e.a = i;
				do {
					e.b = RND.nextInt(nodeCount);
				} while (!isValidEdge(e));
				addEdge(e);
			}
		}
		return this;
	}

	private Tests addRandomEdges2(int k) {
		ArrayList<Integer> avail = new ArrayList<Integer>();
		for (int i = 0; i < nodeCount; i++) {
			avail.add(i);
		}

		while (avail.size() >= 2) {
			Collections.shuffle(avail, RND);

			int i = 0;
			while (i < avail.size() - 1) {
				Edge e = new Edge();
				e.a = avail.get(i);
				e.b = avail.get(i + 1);
				if (isValidEdge(e)) {
					addEdge(e);
					i += 2;
				} else {
					i++;
				}
			}

			ArrayList<Integer> newAvail = new ArrayList<Integer>();
			for (int j : avail) {
				if (degrees[j] < k) {
					newAvail.add(j);
				}
			}

			avail = newAvail;
		}

		return this;
	}

	private Tests generateComplete() {
		for (int i = 0; i < nodeCount; i++) {
			for (int j = i + 1; j < nodeCount; j++) {
				addEdge(i, j);
			}
		}
		return this;
	}

	private Tests generateNearlyComplete() {
		for (int i = 0; i < nodeCount - 1; i++) {
			for (int j = i + 1; j < nodeCount - 1; j++) {
				if (i != 0 || j != 1) {
					addEdge(i, j);
				}
			}
		}
		addEdge(0, nodeCount - 1);
		return this;
	}

	private Tests generateCycleWithRods() {
		int n = nodeCount / 2;
		for (int i = 0; i < n; i++) {
			addEdge(i, (i + 1) % n);
			addEdge(i, i + n);
		}
		addEdge(2 * n - 1, 2 * n);
		return this;
	}

	private Tests generateCycleWithForks() {
		assert nodeCount % 4 == 1;
		int n = nodeCount / 4;
		for (int i = 0; i < n; i++) {
			addEdge(i, (i + 1) % n);
			addEdge(i, i + n);
			addEdge(i + n, i + 2 * n);
			addEdge(i + n, i + 3 * n);
		}
		addEdge(4 * n - 1, 4 * n);
		return this;
	}

	private Tests generateLayered(int layerSize, int layerCount, int degree) {
	    for (int i = 1; i < layerCount; i++) {
	    	ArrayList<Integer> avail1 = new ArrayList<Integer>();
	    	ArrayList<Integer> avail2 = new ArrayList<Integer>();
	    	for (int j = 0; j < layerSize; j++) {
	   			avail1.add(layerSize * (i - 1) + j);
	   			avail2.add(layerSize * i + j);
	    	}

	    	int passCount = i % 2 == 0 ? degree / 2 : (degree + 1) / 2;
	    	for (int j = 0; j < passCount; j++) {
	    		Collections.shuffle(avail1, RND);
	    		Collections.shuffle(avail2, RND);
	    		for (int k = 0; k < layerSize; k++) {
	    			Edge e = new Edge();
	    			e.a = avail1.get(k);
	    			e.b = avail2.get(k);
	    			if (isValidEdge(e)) {
	    				addEdge(e);
	    			}
	    		}
	    	}
	    }

	    for (int i = 0; i < degree; i++) {
	    	addEdge(layerSize * layerCount, i);
	    }
		return this;
	}

	private Tests generateNearlyRegular(int degree) {
	    for (int i = 0; i < nodeCount - 1; i++) {
	    	for (int j = 1; j <= degree / 2; j++) {                   
	    		addEdge(i, (i + j) % (nodeCount - 1));
	    	}
	    }
	    for (int i = 1; i < (nodeCount - 1) / 2; i++) {
	    	addEdge(i, (i + (nodeCount - 1) / 2) % (nodeCount - 1));
	    }
	    addEdge(0, nodeCount - 1);
		return this;
	}

	private Tests generateHoneycomb(int numRows, int numCols) {
		assert numRows % 2 == 0;
		for (int row = 0; row < numRows; row += 2) {
			for (int col = 0; col < numCols; col++) {
				int current = row * numCols + col;
				int up = ((row + 1) % numRows) * numCols + col;
				int upRight = ((row + 1) % numRows) * numCols + (col + 1) % numCols;
				int up2 = ((row + 2) % numRows) * numCols + col;
				addEdge(current, up);
				if (up2 != 0) {
					addEdge(up, up2);
				}
				addEdge(current, upRight);
			}
		}
		addEdge(0, numRows * numCols);
		return this;
	}

	private Tests addEdge(int a, int b) {
		Edge e = new Edge();
		e.a = a;
		e.b = b;
		addEdge(e);                            
		return this;
	}

	private Tests addEdge(Edge e) {
		assert isValidEdge(e);
		edges.add(e);
		edgeSet.add(e);
		degrees[e.a]++;
		degrees[e.b]++;
		return this;
	}

	public boolean isValidEdge(Edge e) {
		return e.a != e.b && !edgeSet.contains(e);
	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();

		new Tests("First sample", 3)
			.addEdge(0, 2)
			.addEdge(2, 1)
			.write();
		new Tests("Second sample", 7)
			.addEdge(0, 3)
			.addEdge(3, 1)
			.addEdge(1, 5)
			.addEdge(5, 2)
			.addEdge(2, 6)
			.addEdge(3, 4)
			.addEdge(4, 5)
			.addEdge(4, 1)
			.write();

	   new Tests("Complete graph with 3 nodes", 3)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 5 nodes", 5)
	   		.generateComplete()
	   		.write();

	   new Tests("Complete graph with 11 nodes", 11)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 51 nodes", 51)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 101 nodes", 101)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 201 nodes", 201)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 301 nodes", 301)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 315 nodes", 315)
	   		.generateComplete()
	   		.write();
	   new Tests("Complete graph with 315 nodes", 315)
	   		.generateComplete()
	   		.write();

	   new Tests("Nearly complete graph with 11 nodes", 11)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly complete graph with 51 nodes", 51)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly complete graph with 101 nodes", 101)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly complete graph with 201 nodes", 201)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly complete graph with 301 nodes", 301)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly complete graph with 315 nodes", 315)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly complete graph with 315 nodes", 315)
	   		.generateNearlyComplete()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();

	   new Tests("Cycle with rods, 11 nodes", 11)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with rods, 101 nodes", 101)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with rods, 501 nodes", 501)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with rods, 1001 nodes", 1001)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with rods, 5001 nodes", 5001)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with rods, 9997 nodes", 9997)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with rods, 9999 nodes", 9999)
	   		.generateCycleWithRods()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();

	   new Tests("Cycle with forks, 17 nodes", 17)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with forks, 101 nodes", 101)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with forks, 501 nodes", 501)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with forks, 1001 nodes", 1001)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with forks, 5001 nodes", 5001)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with forks, 8001 nodes", 8001)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Cycle with forks, 9997 nodes", 9997)
	   		.generateCycleWithForks()
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();

	   new Tests("Random graph, method 1, 11 nodes", 11)
	   		.addRandomEdges1(3, 4)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 1001 nodes", 1001)
	   		.addRandomEdges1(98, 99)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 3001 nodes", 3001)
	   		.addRandomEdges1(32, 33)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 4001 nodes", 4001)
	   		.addRandomEdges1(10, 12)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 5001 nodes", 5001)
	   		.addRandomEdges1(8, 9)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 7001 nodes", 7001)
	   		.addRandomEdges1(3, 7)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 9997 nodes", 9999)
	   		.addRandomEdges1(8, 9)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 1, 9999 nodes", 9999)
	   		.addRandomEdges1(1, 5)
	   		.shuffleEdges()
	   		.write();

	   new Tests("Random graph, method 2, 11 nodes", 11)
	   		.addRandomEdges2(5)
	   		.write();
	   new Tests("Random graph, method 2, 1001 nodes", 1001)
	   		.addRandomEdges2(99)
	   		.write();
	   new Tests("Random graph, method 2, 3001 nodes", 3001)
	   		.addRandomEdges2(57)
	   		.write();
	   new Tests("Random graph, method 2, 4001 nodes", 4001)
	   		.addRandomEdges2(47)
	   		.write();
	   new Tests("Random graph, method 2, 5011 nodes", 4999)
	   		.addRandomEdges2(39)
	   		.write();
	   new Tests("Random graph, method 2, 7001 nodes", 7001)
	   		.addRandomEdges2(21)
	   		.write();
	   new Tests("Random graph, method 2, 9999 nodes", 9999)
	   		.addRandomEdges2(17)
	   		.shuffleEdges()
	   		.write();
	   new Tests("Random graph, method 2, 9999 nodes", 9999)
	   		.addRandomEdges2(15)
	   		.write();

	   new Tests("Nearly regular graph, 1001 nodes, max degree 3", 1001)
	   		.generateNearlyRegular(3)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly regular graph, 9999 nodes, max degree 3", 9999)
	   		.generateNearlyRegular(3)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly regular graph, 1001 nodes, max degree 17", 1001)
	   		.generateNearlyRegular(17)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly regular graph, 9999 nodes, max degree 17", 9999)
	   		.generateNearlyRegular(17)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly regular graph, 5555 nodes, max degree 21", 5555)
	   		.generateNearlyRegular(21)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Nearly regular graph, 2001 nodes, max degree 99", 2001)
	   		.generateNearlyRegular(99)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();

	   new Tests("Layered graph 10x10, 101 nodes, max degree 5", 101)
	   		.generateLayered(10, 10, 5)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Layered graph 20x10, 201 nodes, max degree 7", 201)
	   		.generateLayered(20, 10, 7)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Layered graph 10x20, 201 nodes, max degree 7", 201)
	   		.generateLayered(10, 20, 7)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Layered graph 50x50, 2501 nodes, max degree 31", 2501)
	   		.generateLayered(50, 50, 31)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Layered graph 50x100, 5001 nodes, max degree 37", 5001)
	   		.generateLayered(50, 100, 37)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Layered graph 100x50, 5001 nodes, max degree 39", 5001)
	   		.generateLayered(100, 50, 39)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Layered graph 99x99, 5001 nodes, max degree 41", 5001)
	   		.generateLayered(100, 50, 41)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();

	   new Tests("Honeycomb 4x2, 9 nodes", 9)
	   		.generateHoneycomb(4, 2)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Honeycomb 10x10, 101 nodes", 101)
	   		.generateHoneycomb(10, 10)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Honeycomb 50x50, 2501 nodes", 2501)
	   		.generateHoneycomb(50, 50)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Honeycomb 100x50, 5001 nodes", 5001)
	   		.generateHoneycomb(100, 50)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Honeycomb 4x2000, 8001 nodes", 8001)
	   		.generateHoneycomb(4, 2000)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Honeycomb 16x624, 8001 nodes", 9985)
	   		.generateHoneycomb(16, 624)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	   new Tests("Honeycomb 98x99, 9703 nodes", 9703)
	   		.generateHoneycomb(98, 99)
	   		.shuffleNodes()
	   		.shuffleEdges()
	   		.write();
	}
}
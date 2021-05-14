import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

/**
 * Incorrect solution for NEERC'2010 Problem K: K-Graph Oddity.
 * @author Maxim Babenko
 */
public class kgraph_mb_greedy1 {
    public static void main(String[] args) throws Exception {
        new kgraph_mb_greedy1().go();
    }

    void go() throws Exception {
        read();
        solve();
        write();
    }

    private static class Node {
        public int color;
        public int degree;
        public ArrayList<Integer> neighbors = new ArrayList<Integer>();
    }

    private int colorCount;
    private Node[] nodes;

    private void read() throws FileNotFoundException {
        Scanner in = new Scanner(new File("kgraph.in"));
        int nodeCount = in.nextInt();
        int edgeCount = in.nextInt();
        in.nextLine();
        nodes = new Node[nodeCount];
        for (int i = 0; i < nodeCount; i++) {
            nodes[i] = new Node();
        }
        for (int i = 0; i < edgeCount; i++) {
            int a = in.nextInt() - 1;
            int b = in.nextInt() - 1;
            in.nextLine();
            nodes[a].neighbors.add(b);
            nodes[a].degree++;
            nodes[b].neighbors.add(a);
            nodes[b].degree++;
        }
        in.close();
    }

    private void write() throws FileNotFoundException {
        PrintWriter out = new PrintWriter("kgraph.out");
        out.println(colorCount);
        for (int i = 0; i < nodes.length; i++)
            out.println(nodes[i].color + 1);
        out.close();
    }

    private void solve() {
        // Compute colorCount.
        colorCount = 0;
        for (int i = 0; i < nodes.length; i++) {
            if (nodes[i].degree > colorCount) {
                colorCount = nodes[i].degree;
            }
        }

        if (colorCount % 2 == 0) {
            colorCount++;
        }
                
        // Compute node ordering.
        List<Integer> nodeOrdering = new ArrayList<Integer>(nodes.length);
        for (int i = 0; i < nodes.length; i++) {
        	nodeOrdering.add(i);
        }

        assert nodeOrdering.size() == nodes.length;

        // Compute colors.
        int[] usedColors = new int[colorCount];
        for (int i = 0; i < colorCount; i++) {
            usedColors[i] = -1;
        }
        for (int i = 0; i < nodes.length; i++) {
            nodes[i].color = -1;
        }
        for (int i = nodeOrdering.size() - 1; i >= 0; i--) {
            int nodeIndex = nodeOrdering.get(i);
            for (int j = 0; j < nodes[nodeIndex].neighbors.size(); j++) {
                int neighborIndex = nodes[nodeIndex].neighbors.get(j);
                int neighborColor = nodes[neighborIndex].color;
                if (neighborColor >= 0) {
                    usedColors[neighborColor] = i;
                }
            }

            for (int j = 0; j < colorCount; ++j) {
                if (usedColors[j] != i) {
                    nodes[nodeIndex].color = j;
                    break;
                }
            }

            assert nodes[nodeIndex].color >= 0;
        }
    }
}

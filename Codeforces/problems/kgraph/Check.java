/*--------------------------------------------------------------*/
/* ACM ICPC 2010-2011                                           */
/* Northeastern European Regional Contest                       */
/* St Petersburg - Barnaul - Tashkent - Batumi, November 24, 201*/
/*--------------------------------------------------------------*/
/* Problem K. K-Graph Oddity                                    */
/*                                                              */
/* Original idea                                                */
/* Problem statement     Roman Elizarov                         */
/* Testset               Maxim Babenko                          */
/*--------------------------------------------------------------*/
/* Checker                                                      */
/*                                                              */
/* Author                Maxim Babenko                          */
/*--------------------------------------------------------------*/
 
import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
    Checker for NEERC'2010 Problem K: K-Graph Oddity.
    @author Maxim Babenko
*/
public class Check implements Checker {
	private static class Edge {
		public int a;
		public int b;
	}

	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int nodeCount = inf.nextInt();
		int edgeCount = inf.nextInt();
		Edge[] edges = new Edge[edgeCount];
		for (int i = 0; i < edgeCount; i++) {
			int a = inf.nextInt() - 1;
			int b = inf.nextInt() - 1;
			edges[i] = new Edge();
			edges[i].a = a;
			edges[i].b = b;
		}

		int oufColors = ouf.nextInt();
		int ansColors = ans.nextInt();
		if (oufColors != ansColors)
			throw new Outcome(Outcome.Type.WA, String.format("Color count mismatch: %d instead of %d", oufColors, ansColors));

		int[] colors = new int[nodeCount];
		for (int i = 0; i < nodeCount; i++) {
			int color = ouf.nextInt();
			if (color < 1 || color > ansColors)
				throw new Outcome(Outcome.Type.WA, String.format("Node %d is given an invalid color %d", i + 1, color));
			colors[i] = color;
		}

		for (int i = 0; i < edgeCount; i++) {
			int a = edges[i].a;
			int b = edges[i].b;
			if (colors[a] == colors[b])
				throw new Outcome(Outcome.Type.WA, String.format("Not a proper coloring: endpoints (%d,%d) of edge %d are both of color %d",
					a + 1, b + 1, i + 1, colors[a]));
		}

		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		
		return new Outcome(Outcome.Type.OK, String.format("%d node(s), %d edge(s), %d color(s)", nodeCount, edgeCount, oufColors));
	}
}

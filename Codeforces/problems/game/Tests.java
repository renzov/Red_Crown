import solver.CostMap;
import solver.CostMapView;
import solver.Solve;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

/**
    Tests generator for NEERC'2010 Problem G: Game of 10.
    @author Roman Elizarov
*/
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

	private static final Random RND = new Random(20101110);

	private static final int N = 4;

	private final PrintWriter out;

	private Tests(String description) throws IOException {
		String tn = String.format("%02d", ++TEST_COUNTER);
		File tests = new File("tests");
		tests.mkdir();
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + description);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(tests, tn)));
	}

	private static class Move {
		final int r;
		final int c;
		final int k;

		private Move(int r, int c, int k) {
			this.r = r;
			this.c = c;
			this.k = k;
		}

		@Override
		public String toString() {
			return r + " " + c + " " + k;
		}
	}

	private void write(Move move, String strategy) {
		out.println(move + " " + strategy);
		out.close();
	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		new Tests("First sample, random strategy").write(new Move(2, 2, 2), "RND");
		new Tests("1 1 1 move, worst non-losing move strategy").write(new Move(1, 1, 1), "WNL");
		for (int i = 0; i < 2; i++) {
			Move move = new Move(RND.nextInt(4) + 1, RND.nextInt(4) + 1, RND.nextInt(4) + 1);
			new Tests(move + " move, best0 strategy").write(move, "BEST0");
		}
		for (int i = 0; i < 2; i++) {
			Move move = new Move(RND.nextInt(4) + 1, RND.nextInt(4) + 1, RND.nextInt(4) + 1);
			new Tests(move + " move, best1 strategy").write(move, "BEST1");
		}
		// generate all possible first moves
		List<Move> moves = new ArrayList<Move>();
		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				for (int k = 1; k <= N; k++)
					moves.add(new Move(r, c, k));
		Collections.shuffle(moves, RND);
		for (Move move : moves)
			new Tests(move + " move, best strategy").write(move, "BEST");
		// check cost map view (will solve game if needed)
		CostMapView.getCostMap(CostMap.FILE);
	}
}
package solver;

import java.io.IOException;
import java.util.*;

/**
 * @author Roman Elizarov
 */
public class Play {
	private static final int N = Position.N;
	private static final int MAX_TURN = N * N;

	private final Field field;

	public static void main(String[] args) throws IOException {
		Strategy player1 = args.length == 0 ? Strategy.HUMAN : Strategy.valueOf(args[0].toUpperCase(Locale.US));
		Strategy player2 = args.length <= 1 ? Strategy.HUMAN : Strategy.valueOf(args[1].toUpperCase(Locale.US));
		long seed = new Random().nextLong();
		boolean spin = false;
		int period = 0;
		if (args.length > 2) {
			spin = args[2].equalsIgnoreCase("spin");
			if (spin) {
				if (args.length > 3)
					period = Integer.parseInt(args[3]);
			} else
				seed = Long.parseLong(args[2]);
		}
		Strategy.rnd = new Random(seed);
		System.out.println("Using random seed " + seed);
		Play play = new Play(player1, player2, period != 0);
		if (spin) {
			play.spin(period);
		} else
			play.go();
	}

	private final Strategy player1;
	private final Strategy player2;
	private final boolean quiet;

	public Play(Strategy player1, Strategy player2, boolean quiet) throws IOException {
		this.player1 = player1;
		this.player2 = player2;
		this.quiet = quiet;
		this.field = new Field(CostMapView.getCostMap(CostMap.FILE));
	}

	private void spin(int period) {
		int[] outcomes = new int[Outcome.values().length];
		for (int i = 1;; i++) {
			Outcome outcome = go();
			outcomes[outcome.ordinal()]++;
			if (period != 0 && i % period == 0) {
				System.out.print(i + ":");
				for (Outcome o : Outcome.values()) {
					int cnt = outcomes[o.ordinal()];
					System.out.printf(" %s=%d (%d%%)", o, cnt, 100L * cnt / i);
				}
				System.out.println();
			}
		}
	}

	private Outcome go() {
		field.clear();
		int turn;
		Outcome outcome = Outcome.DRAW;
		for (turn = 1; turn <= MAX_TURN; turn++) {
			if (!quiet) {
				printFieldAnalysis();
				System.out.print(">");
			}
			Strategy player = turn % 2 == 1 ? player1 : player2;
			Move move = field.getMove(player);
			if (player != Strategy.HUMAN && !quiet)
				System.out.println(move);
			if (field.makeMove(move)) {
				if (!quiet)
					field.print();
				outcome = turn % 2 == 1 ? Outcome.PLAYER_1_WINS : Outcome.PLAYER_2_WINS;
				break;
			}
		}
		if (turn > MAX_TURN)
			turn--;
		if (!quiet)
			System.out.println(outcome + " !!! Game over in " + turn + " turns.");
		return outcome;
	}

	private void printFieldAnalysis() {
		field.print();
		SortedMap<Byte, List<Move>> moves = field.analyzeMoves();
		for (Map.Entry<Byte, List<Move>> entry : moves.entrySet()) {
			System.out.println(Cost.costToString(entry.getKey()) + " " + entry.getValue());
		}
	}
}

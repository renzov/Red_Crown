package solver;

import java.util.*;

/**
 * @author Roman Elizarov
 */
public enum Strategy {
	/** Human player */
	HUMAN {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			int m = in.nextInt();
			Move move = new Move(m / 100, (m / 10) % 10, m % 10);
			if (!collect(moves).contains(move))
				throw new IllegalArgumentException("Invalid move " + m);
			return move;
		}},

	/** Best move */
	BEST {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			return pickAny(moves.get(moves.lastKey()));
		}},

	/** Worst, but non-immediately loosing move */
	WNL {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			SortedMap<Byte, List<Move>> nil = moves.tailMap((byte)(Cost.LOOSE + 1));
			Byte cost = nil.isEmpty() ? moves.firstKey() : nil.firstKey();
			return pickAny(moves.get(cost));
		}},

	/** Fully random move */
	RND {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			return pickAny(collect(moves));
		}},

	/** Make immediately winning moves, otherwise random */
	BEST0 {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			if (moves.lastKey() == Cost.WIN)
				return pickAny(moves.get(moves.lastKey()));
			return RND.getMove(f, moves);
		}},

	/** Make immediately winning moves, avoid immediately loosing moves, otherwise random */
	BEST1 {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			if (moves.lastKey() == Cost.WIN)
				return pickAny(moves.get(moves.lastKey()));
			if (moves.size() > 1 && moves.firstKey() == Cost.LOOSE)
				moves.remove(moves.firstKey());
			return RND.getMove(f, moves);
		}},

	/** Make immediately winning moves, horizontal symmetrical moves, or random if symmetry is broken */
	SYM {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			if (moves.lastKey() == Cost.WIN)
				return pickAny(moves.get(moves.lastKey()));
			int n = Position.N;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (f[i][j] != 0 && f[n - i - 1][j] == 0)
						return new Move(n - i - 1, j, n - f[i][j] + 1);
			return RND.getMove(f, moves);
		}},

	/** Make immediately winning moves, radial symmetrical moves, or random if symmetry is broken */
	SYM0 {
		@Override
		public Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves) {
			if (moves.lastKey() == Cost.WIN)
				return pickAny(moves.get(moves.lastKey()));
			int n = Position.N;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (f[i][j] != 0 && f[n - i - 1][n - j - 1] == 0)
						return new Move(n - i - 1, n - j - 1, n - f[i][j] + 1);
			return RND.getMove(f, moves);
		}};

	private static final Scanner in = new Scanner(System.in);
	
	public static Random rnd = new Random();

	private static List<Move> collect(SortedMap<Byte, List<Move>> moves) {
		List<Move> result = new ArrayList<Move>();
		for (List<Move> list : moves.values()) {
			result.addAll(list);
		}
		return result;
	}

	private static Move pickAny(List<Move> list) {
		return list.get(rnd.nextInt(list.size()));
	}

	public abstract Move getMove(int[][] f, SortedMap<Byte, List<Move>> moves);
}

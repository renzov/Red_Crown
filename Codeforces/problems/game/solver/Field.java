package solver;

import java.util.*;

public class Field {
	private static final int N = Position.N;

	private final CostMap costMap;

	private final Position p = new Position();
	private final int[][] f = new int[N][N];

	public Field(CostMap costMap) {
		this.costMap = costMap;
	}

	public void clear() {
		p.clear();
		for (int[] r : f)
			Arrays.fill(r, 0);
	}

	public boolean canMove(Move move) {
		return f[move.r][move.c] == 0;
	}

	public boolean makeMove(Move move) {
		assert canMove(move);
		f[move.r][move.c] = move.k;
		return p.move(move);
	}

	public Move getMove(Strategy player) {
		SortedMap<Byte, List<Move>> moves = analyzeMoves();
		if (moves.isEmpty())
			return null;
		return player.getMove(f, moves);
	}

	public SortedMap<Byte, List<Move>> analyzeMoves() {
		Position np = new Position();
		SortedMap<Byte, List<Move>> moves = new TreeMap<Byte, List<Move>>();
		for (int i = 0; i < N; i++)
			if (!p.rowFilled(i))
				for (int j = 0; j < N; j++)
					if (!p.isFilled(i, j))
						for (int k = 1; k <= N; k++) {
							np.copyFrom(p);
							Byte cost;
							if (np.move(i, j, k))
								cost = Cost.WIN;
							else {
								byte c = findCost(np);
								if (c == Cost.UNKNOWN) {
									f[i][j] = k;
									System.out.println("!!! Unknown cost after move " + i + "" + j + "" + k + " !!!");
									print(np, f);
									System.exit(1);
								}
								cost = Cost.turnCost(c);
							}
							List<Move> list = moves.get(cost);
							if (list == null)
								moves.put(cost, list = new ArrayList<Move>());
							list.add(new Move(i, j, k));
						}
		return moves;
	}

	private byte findCost(Position p) {
		byte cost = p.heuristicCost();
		if (cost != Cost.UNKNOWN)
			return cost;
		Position q = new Position(p);
		cost = costMap.get(q.approximatelyNormalizeAndNumber());
		if (cost != Cost.UNKNOWN)
			return cost;
		cost = findCostViaTransposeAndPermutation(q);
		if (cost != Cost.UNKNOWN)
			return cost;
		q.inverse();
		return findCostViaTransposeAndPermutation(q);
	}

	private byte findCostViaTransposeAndPermutation(Position q) {
		byte cost = findCostViaPermutation(q);
		if (cost != Cost.UNKNOWN)
			return cost;
		q.transpose();
		return findCostViaPermutation(q);
	}

	private byte findCostViaPermutation(Position p) {
		byte cost;
		Position q = new Position();
		p.sortRows();
		do {
			q.copyFrom(p);
			q.sortColumns();
			do {
				cost = costMap.get(q.number());
				if (cost != Cost.UNKNOWN)
					return cost;
			} while (q.nextColumnPermutation());
		} while (p.nextRowPermutation());
		return cost;
	}

	private void print(Position p, int[][] f) {
		for (int j = 0; j < N; j++)
			System.out.print("-");
		System.out.println(" id #" + new Position(p).approximatelyNormalizeAndNumber());
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				System.out.print(f[i][j]);
				assert (f[i][j] != 0) == p.isFilled(i, j);
			}
			System.out.println();
		}
	}

	public void print() {
		print(p, f);
	}
}

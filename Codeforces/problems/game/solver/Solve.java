package solver;

import java.io.*;
import java.util.Locale;

/**
 * @author Roman Elizarov
 */
public class Solve {
	private static final int N = Position.N;
	private static final int MAX_TURN = N * N;
	private static final int EXPECTED_SIZE = N == 4 ? 1416880 : 0;

	private static final double MILLION = 1e6;
	private static final double REPORT = MILLION / 10;

	public static void main(String[] args) throws IOException {
		solve(CostMap.FILE);
	}

	public static void solve(File file) throws IOException {
		new Solve(file).go();
	}

	private final Position[] positions = new Position[MAX_TURN + 1];
	private final Move[][] moves = new Move[MAX_TURN][N * N * N];
	private final CostMapImpl costMap = new CostMapImpl();
	private long startTime;
	private int lastSize;
	private long lastTime;

	private final File file;

	private Solve(File file) {
		this.file = file;
	}

	public void go() throws IOException {
		if (EXPECTED_SIZE != 0)
			System.err.printf(Locale.US, "%.1fM actual positions are expected to be reached%n", EXPECTED_SIZE / MILLION);
		System.err.println("Please wait while the game is being solved...");
		init();
		lastTime = startTime = System.currentTimeMillis();
		int cost = computeMove(1);
		reportPositions();
		System.err.printf(Locale.US, "Done in %.3f sec, %s%n",
			(System.currentTimeMillis() - startTime) / 1000.0,
			Cost.costToString(cost));
		saveMapToFile(file);
	}

	private void init() {
		for (int i = 0; i < positions.length; i++)
			positions[i] = new Position();
		for (int i = 0; i < moves.length; i++) {
			Move[] moveList = moves[i];
			for (int j = 0; j < moveList.length; j++)
				moveList[j] = new Move();
		}
	}

	private void saveMapToFile(File file) throws IOException {
		DataOutputStream out = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(file)));
		try {
			costMap.writeMapTo(out);
		} finally {
			out.close();
		}
		System.err.println("Saved to " + file + ", " + file.length() + " bytes");
	}

	private int computeMove(int turn) {
		if (turn > MAX_TURN)
			return Cost.DRAW;
		Position curPos = positions[turn - 1];
		long num = curPos.approximatelyNormalizeAndNumber();
		int cost = costMap.get(num);
		if (cost != Cost.UNKNOWN)
			return cost;
		Position newPos = positions[turn];
		
		// heuristic only search (quick)
		boolean trim = false; // don't trim any moves
		int moveCount = 0;
		Move[] moveList = moves[turn - 1];
	preSearch:
		for (int r = 0; r < N; r++)
			if (!curPos.rowFilled(r))
				for (int c = 0; c < N; c++)
					if (!curPos.isFilled(r, c)) {
						for (int k = 1; k <= N; k++) {
							if (newPos.copyFrom(curPos).move(r, c, k)) {
								cost = Cost.WIN;
								if (trim)
									break preSearch;
								else
									continue;
							}
							byte hc = newPos.heuristicCost();
							if (hc == Cost.UNKNOWN) {
								moveList[moveCount++].set(r, c, k);
								continue;
							}
							cost = Math.max(cost, Cost.turnCost(hc));
						}
					}
		
		// full search (only non-heuristically known moves)
		if (!trim || cost < Cost.WIN2) {
			for (int i = 0; i < moveCount; i++) {
				newPos.copyFrom(curPos).move(moveList[i]);
				int cc = computeMove(turn + 1);
				assert cc != Cost.UNKNOWN;
				cost = Math.max(cost, Cost.turnCost(cc));
			}
		}
		costMap.put(num, cost);
		if (costMap.size() % REPORT == 0)
			reportPositions();
		return cost;
	}

	private void reportPositions() {
		long time = System.currentTimeMillis();
		System.err.printf(Locale.US, "%02d%% -- %.1fM positions, %.3fM positions per second, estimated %.0f seconds remaining%n",
			costMap.size() * 100 / EXPECTED_SIZE, costMap.size() / MILLION,
			(costMap.size() - lastSize) / 1000.0 / (time - lastTime),
			(EXPECTED_SIZE - costMap.size()) / 1000.0 * (time - startTime)  / costMap.size());
		lastSize = costMap.size();
		lastTime = time;
	}
}

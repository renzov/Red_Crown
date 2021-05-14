package solver;

import java.util.Arrays;
import java.util.Locale;

/**
 * @author Roman Elizarov
 */
public class Position {
	public static final int N = 4;
	public static final int WIN_SUM = N * (N + 1) / 2;
	public static final int MAX_SUM = WIN_SUM + 1;

	private final int[] row = new int[N];
	private final int[] col = new int[N];

	private static boolean canWin(int cnt, int sum) {
		return sum + (N - cnt) <= WIN_SUM && sum + (N - cnt) * N >= WIN_SUM;
	}

	private static int trimSum(int cnt, int sum) {
		return canWin(cnt, sum) ? sum : MAX_SUM;
	}

	private static int packPattern(int bits, int sum) {
		return (sum << N) | bits;
	}

	private static final int BIT_MASK = (1 << N) - 1;
	private static final int MAX_PATTERN = packPattern(BIT_MASK, WIN_SUM + 1);

	private static final int[] PATTERN_TO_INDEX = new int[MAX_PATTERN + 1];
	private static final int PATTERN_COUNT;
	private static final long[] ROW_PATTERN_MUL = new long[N];
	private static final int COL_SUM_COUNT = MAX_SUM + 1;
	private static final long[] COL_SUM_MUL = new long[N];
	private static final int[] BITS_TO_CNT = new int[BIT_MASK + 1];

	public static final long MAX_POSITION_NUMBER;

	private static int unpackSum(int ptn) {
		return ptn >>> N;
	}

	private static int unpackBits(int ptn) {
		return ptn & BIT_MASK;
	}

	private static int unpackCnt(int ptn) {
		return BITS_TO_CNT[unpackBits(ptn)];
	}

	private static int inverseSum(int ptn) {
		int sum = unpackSum(ptn);
		if (sum == MAX_SUM)
			return ptn; 
		int bits = unpackBits(ptn);
		int cnt = BITS_TO_CNT[bits];
		int p = packPattern(bits, (N + 1) * cnt - sum);
		assert PATTERN_TO_INDEX[p] >= 0;
		return p;
	}

	static {
		Arrays.fill(PATTERN_TO_INDEX, -1); // just in case...
		int cnt = 0;
		for (int bits = 0; bits < (1 << N); bits++) {
			int bc = Integer.bitCount(bits);
			for (int sum = bc; sum <= bc * N; sum++) {
				if (trimSum(bc, sum) != sum)
					continue;
				int p = packPattern(bits, sum);
				PATTERN_TO_INDEX[p] = cnt;
				cnt++;
			}
		}
		PATTERN_COUNT = cnt;
		ROW_PATTERN_MUL[0] = 1;
		for (int i = 1; i < N; i++)
			ROW_PATTERN_MUL[i] = PATTERN_COUNT * ROW_PATTERN_MUL[i - 1];
		COL_SUM_MUL[0] = ROW_PATTERN_MUL[N - 1] * cnt;
		for (int i = 1; i < N; i++)
			COL_SUM_MUL[i] = COL_SUM_COUNT * COL_SUM_MUL[i - 1];
		for (int i = 0; i <= BIT_MASK; i++)
			BITS_TO_CNT[i] = Integer.bitCount(i);

		MAX_POSITION_NUMBER = COL_SUM_COUNT * COL_SUM_MUL[N - 1];
		System.err.printf(Locale.US, "Enumerated %d row patterns, maximal number of positions is %.3fM%n",
				cnt, MAX_POSITION_NUMBER / 1000000.0);
	}

	public Position() {}

	public Position(Position p) {
		copyFrom(p);
	}

	public Position copyFrom(Position p) {
		System.arraycopy(p.row, 0, row, 0, N);
		System.arraycopy(p.col, 0, col, 0, N);
		return this;
	}

	public boolean isFilled(int r, int c) {
		return (row[r] & (1 << c)) != 0;
	}

	private static final boolean DRAW_HEURISTIC = true;
	private static final boolean WIN_HEURISTIC = false;
	private static final boolean LOOSE_HEURISTIC = false;

	public byte heuristicCost() {
		if (!DRAW_HEURISTIC)
			return Cost.UNKNOWN;
		boolean draw = true;
		boolean loose = LOOSE_HEURISTIC;
		for (int r = 0; r < N; r++) {
			int cnt = unpackCnt(row[r]);
			int sum = unpackSum(row[r]);
			if (canWin(cnt, sum)) {
				if (WIN_HEURISTIC && cnt == N - 1)
					return Cost.WIN;
				draw = false;
			}
			if (LOOSE_HEURISTIC && loose) {
				if (!willLoose(cnt, sum)) {
					if (cnt == N - 1) {
						for (int c = 0; c < N; c++)
							if (!isFilled(r, c)) {
								if (!willLoose(unpackCnt(col[c]), unpackSum(col[c])))
									loose = false;
								break;
							}
					} else
						loose = false;
				}
			}
		}
		for (int c = 0; c < N; c++) {
			int cnt = unpackCnt(col[c]);
			int sum = unpackSum(col[c]);
			if (canWin(cnt, sum)) {
				if (WIN_HEURISTIC && cnt == N - 1)
					return Cost.WIN;
				draw = false;
			}
			if (LOOSE_HEURISTIC && loose) {
				if (!willLoose(cnt, sum)) {
					if (cnt == N - 1) {
						for (int r = 0; r < N; r++)
							if (!isFilled(r, c)) {
								if (!willLoose(unpackCnt(row[r]), unpackSum(row[r])))
									loose = false;
								break;
							}
					} else
						loose = false;
				}
			}
		}
		return draw ? Cost.DRAW : loose ? Cost.LOOSE : Cost.UNKNOWN;
	}

	private static boolean willLoose(int cnt, int sum) {
		return cnt == N || cnt == N - 2 && sum + N + 1 == WIN_SUM;
	}

	public boolean move(Move move) {
		return move(move.r, move.c, move.k);
	}
	
	public boolean move(int r, int c, int k) {
		assert r >= 0 && r < N;
		assert c >= 0 && c < N;
		assert k >= 1 && k <= N;
		int rs = unpackSum(row[r]) + k;
		int cs = unpackSum(col[c]) + k;
		int rb = unpackBits(row[r]);
		int cb = unpackBits(col[c]);
		assert (rb & (1 << c)) == 0;
		assert (cb & (1 << r)) == 0;
		rb |= (1 << c);
		cb |= (1 << r);
		row[r] = packPattern(rb, trimSum(BITS_TO_CNT[rb], rs));
		col[c] = packPattern(cb, trimSum(BITS_TO_CNT[cb], cs));
		return rowFilled(r) && rs == WIN_SUM || colFilled(c) && cs == WIN_SUM;
	}

	public boolean rowFilled(int r) {
		return unpackBits(row[r]) == BIT_MASK;
	}

	public boolean colFilled(int c) {
		return unpackBits(col[c]) == BIT_MASK;
	}

	public long approximatelyNormalizeAndNumber() {
		long n1 = anaInternal();
		inverse();
		long n2 = anaInternal();
		return Math.min(n1, n2);
	}

	private long anaInternal() {
		while (sortColumns() || sortRows()); // spin while changes
		long n1 = number();
		transpose();
		long n2 = number();
		return Math.min(n1, n2);
	}

	public long number() {
		long result = 0;
		for (int i = 0; i < N; i++) {
			int pi = PATTERN_TO_INDEX[row[i]];
			assert pi >= 0;
			result += pi * ROW_PATTERN_MUL[i];
		}
		for (int i = 0; i < N; i++)
			result += unpackSum(col[i]) * COL_SUM_MUL[i];
		return result;
	}

	boolean sortColumns() {
		boolean c0 = false;
		boolean c1;
		do {
			c1 = false;
			for (int i = N - 1; --i >= 0;)
				if (col[i + 1] > col[i]) {
					swapColumns(i, i + 1);
					c1 = true;
				}
			c0 |= c1;
		} while (c1);
		return c0;
	}

	public void swapColumns(int i, int j) {
		assert i < j;
		swap(col, i, j);
		for (int r = 0; r < N; r++) {
			swapBits(row, r, i, j);
		}
	}

	public boolean sortRows() {
		boolean c0 = false;
		boolean c1;
		do {
			c1 = false;
			for (int i = N - 1; --i >= 0;)
				if (row[i + 1] > row[i]) {
					swapRows(i, i + 1);
					c1 = true;
				}
			c0 |= c1;
		} while (c1);
		return c0;
	}

	public void swapRows(int i, int j) {
		assert i < j;
		swap(row, i, j);
		for (int c = 0; c < N; c++) {
			swapBits(col, c, i, j);
		}
	}

	public void transpose() {
		for (int i = 0; i < N; i++) {
			int t = row[i];
			row[i] = col[i];
			col[i] = t;
		}
	}

	public void inverse() {
		for (int i = 0; i < N; i++) {
			row[i] = inverseSum(row[i]);
			col[i] = inverseSum(col[i]);
		}
	}

	private void swap(int[] a, int i, int j) {
		int t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	private void swapBits(int[] a, int p, int i, int j) {
		int d = j - i;
		assert d > 0;
		int bits = a[p];
		int m1 = 1 << i;
		int m2 = 1 << j;
		a[p] = (bits & ~m1 & ~m2) | ((bits & m1) << d) | ((bits & m2) >> d);
	}

	public boolean nextRowPermutation() {
		for (int k = N - 1; --k >= 0;)
			if (row[k] > row[k + 1]) {
				for (int l = N; --l >= 0;)
					if (row[k] > row[l]) {
						swapRows(k, l);
						flipRows(k + 1, N - 1);
						return true;
					}
			}
		return false;
	}

	private void flipRows(int a, int b) {
		for (int i = a, j = b; i < j; i++, j--)
			swapRows(i, j);
	}

	public boolean nextColumnPermutation() {
		for (int k = N - 1; --k >= 0;)
			if (col[k] > col[k + 1]) {
				for (int l = N; --l >= 0;)
					if (col[k] > col[l]) {
						swapColumns(k, l);
						flipColumns(k + 1, N - 1);
						return true;
					}
			}
		return false;
	}

	private void flipColumns(int a, int b) {
		for (int i = a, j = b; i < j; i++, j--)
			swapColumns(i, j);
	}

	public void clear() {
		Arrays.fill(row, 0);
		Arrays.fill(col, 0);
	}
}

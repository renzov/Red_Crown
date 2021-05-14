package solver;

/**
 * @author Roman Elizarov
 */
public class Cost {
	public static final byte WIN = Byte.MAX_VALUE;
	public static final byte DRAW = 0;
	public static final byte LOOSE = turnCost(WIN);
	public static final byte WIN2 = turnCost(LOOSE);
	public static final byte UNKNOWN = Byte.MIN_VALUE;

	public static String costToString(int cost) {
		if (cost == UNKNOWN)
			return "UNKNOWN";
		if (cost > 0)
			return "win in " + (WIN - cost + 1) + " turns";
		if (cost < 0)
			return "loose in " + (WIN + cost + 1) + " turns";
		return "draw";
	}

	public static byte turnCost(int c) {
		return (byte)(c > 0 ? -c + 1 : c < 0 ? -c - 1 : 0);
	}
}

package solver;

/**
 * @author Roman Elizarov
 */
public class Move {
	public int r;
	public int c;
	public int k;

	public Move() {
	}

	public Move(int r, int c, int k) {
		set(r, c, k);
	}

	void set(int r, int c, int k) {
		this.r = r;
		this.c = c;
		this.k = k;
	}

	@Override
	public String toString() {
		return r + "" + c + "" + k;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		Move move = (Move)o;
		return c == move.c && k == move.k && r == move.r;
	}

	@Override
	public int hashCode() {
		return 31 * (31 * r + c) + k;
	}
}

package solver;

import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

/**
 * @author Roman Elizarov
 */
public class CostMapImpl implements CostMap {
	private static final long MAGIC = 7046029254386354333L;
	private static final long EMPTY = Position.MAX_POSITION_NUMBER;
	private static final int MAX_SHIFT = 64 - (Position.N >= 4 ? 22 : 4);

	private Core core = new Core(MAX_SHIFT);

	public int size() {
		return core.size;
	}

	public void put(long pos, int cost) {
		core.put(pos, (byte)cost);
		if (core.needsRehash())
			core = core.rehash();
	}

	public byte get(long pos) {
		return core.get(pos);
	}

	public void writeMapTo(DataOutput out) throws IOException {
		core.writeMapTo(out);
	}

	private static class Core {
		final int shift;
		final int mask;
		final long[] p;
		final byte[] c;
		final int threshold;
		int size;

		Core(int shift) {
			System.err.printf("Allocating 2^%d slots for cost hash map%n", 64 - shift);
			this.shift = shift;
			mask = (int)(0xffffffffffffffffL >>> shift);
			p = new long[mask + 1];
			c = new byte[mask + 1];
			Arrays.fill(p, EMPTY);
			threshold = mask / 2; 
		}

		void writeMapTo(DataOutput out) throws IOException {
			int bytes = 1;
			while (bytes < 8 && (1L << (bytes * 8)) < Position.MAX_POSITION_NUMBER)
				bytes++;
			System.err.printf("Writing 2^%d hash slots with %d elements (filled %d%%) using %d+1 bytes per slot%n",
					64 - shift, size, 100L * size / p.length, bytes);
			out.writeLong(MAGIC);
			out.writeLong(EMPTY);
			out.writeByte(bytes);
			out.writeByte(shift);
			for (int i = 0; i <= mask; i++) {
				long pos = p[i];
				for (int j = bytes; --j >= -0;)
					out.writeByte((byte)(pos >>> (8 * j)));
				out.writeByte(c[i]);
			}
		}

		boolean needsRehash() {
			return size >= threshold;
		}
		
		public Core rehash() {
			Core nc = new Core(shift - 1);
			for (int i = 0; i <= mask; i++)
				if (p[i] != EMPTY)
					nc.put(p[i], c[i]);
			return nc;
		}
		
		void put(long pos, byte cost) {
			int i = (int)((pos * MAGIC) >>> shift);
			while (p[i] != EMPTY) {
				if (p[i] == pos) {
					c[i] = cost;
					return;
				}
				i = (i + 1) & mask;
			}
			p[i] = pos;
			c[i] = cost;
			size++;
		}

		byte get(long pos) {
			int i = (int)((pos * MAGIC) >>> shift);
			while (p[i] != EMPTY) {
				if (p[i] == pos)
					return c[i];
				i = (i + 1) & mask;
			}
			return Cost.UNKNOWN;
		}

	}
}

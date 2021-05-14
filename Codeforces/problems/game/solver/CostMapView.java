package solver;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

/**
 * @author Roman Elizarov
 */
public class CostMapView implements CostMap {
	private static final int OFFSET = 18;
	
	private final FileInputStream in;
	private final MappedByteBuffer map;
	private final long magic;
	private final long empty;
	private final int bytes;
	private final int shift;
	private final int mask;

	private static class WrongFile extends Exception {}

	public static CostMapView getCostMap(File mapFile) throws IOException {
		if (!mapFile.exists())
			Solve.solve(mapFile);
		try {
			return new CostMapView(mapFile);
		} catch (WrongFile e) {
			System.err.printf("Failed to open %s -- wrong file format (old file?)%n", mapFile);
			Solve.solve(mapFile);
			try {
				return new CostMapView(mapFile);
			} catch (WrongFile wrongFile) {
				throw new AssertionError("This cannot happen!");
			}
		}
	}

	private CostMapView(File file) throws IOException, WrongFile {
		in = new FileInputStream(file);
		map = in.getChannel().map(FileChannel.MapMode.READ_ONLY, 0, file.length());
		magic = map.getLong(0);
		empty = map.getLong(8);
		if (empty != Position.MAX_POSITION_NUMBER)
			throw new WrongFile();
		bytes = map.get(16);
		shift = map.get(17);
		mask = (int)(0xffffffffffffffffL >>> shift);
		System.err.printf("Opened file %s with 2^%d hash slots using %d+1 bytes per slot%n",
				file, 64 - shift, bytes);
	}

	public void close() throws IOException {
		in.close();
	}

	public byte get(long pos) {
		int i = (int)((pos * magic) >>> shift);
		long p;
		while ((p = getPosition(i)) != empty) {
			if (p == pos)
				return getCost(i);
			i = (i + 1) & mask;
		}
		return Cost.UNKNOWN;
	}

	private long getPosition(int i) {
		int j = OFFSET + (bytes + 1) * i;
		long result = 0;
		for (int k = 0; k < bytes; k++)
			result = (result << 8) | (0xff & map.get(j++));
		return result;
	}

	private byte getCost(int i) {
		return map.get(OFFSET + (bytes + 1) * i + bytes);
	}
}

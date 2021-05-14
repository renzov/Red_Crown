package solver;

import java.io.File;

/**
 * @author Roman Elizarov
 */
public interface CostMap {
	public static final File FILE = new File("game" + Position.WIN_SUM + ".costmap");
	public byte get(long pos);
}

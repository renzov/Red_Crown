package solver;

import junit.framework.TestCase;

import java.util.Random;

/**
 * @author Roman Elizarov
 */
public class PositionTest extends TestCase {
	public void testNormalize3() {
		if (Position.N < 3)
			return;
		Position p = new Position();
		p.move(0, 0, 2);
		p.move(0, 2, 3);
		p.move(1, 2, 2);
		p.move(2, 0, 3);
		p.move(2, 1, 1);

		Position q = new Position();
		q.move(0, 1, 3);
		q.move(0, 2, 2);
		q.move(1, 0, 3);
		q.move(1, 1, 2);
		q.move(2, 0, 1);

		assertEquals(p.approximatelyNormalizeAndNumber(), q.approximatelyNormalizeAndNumber());
	}

	public void testNormalize4() {
		if (Position.N < 4)
			return;
 		Position p = new Position();
		p.move(0, 2, 2);
		p.move(0, 3, 1);
		p.move(1, 2, 1);
		p.move(2, 0, 1);
		p.move(2, 1, 2);
		long num = new Position(p).approximatelyNormalizeAndNumber();

		Random r = new Random(20101018);
		for (int k = 0; k < 1000; k++) {
			int i = r.nextInt(Position.N - 1);
			int j = i + 1 + r.nextInt(Position.N - i - 1);
			if (r.nextBoolean())
				p.swapColumns(i, j);
			else
				p.swapRows(i, j);
			assertEquals(num, new Position(p).approximatelyNormalizeAndNumber());
		}

	}

}

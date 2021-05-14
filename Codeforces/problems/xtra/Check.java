import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
    Checker for NEERC'2010 Problem X: Xtrapolation.
    @author Roman Elizarov
*/
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		String wa = null;
		int n = 0;
		while (!ans.seekEoF()) {
			if (ouf.seekEoF())
				throw new Outcome(Outcome.Type.PE, "not enough numbers");
			n++;
			long ja = ans.nextLong();
			long pa = ouf.nextLong();
			if (pa != ja && wa == null)
				wa = String.format("number %d: %d instead of %d", n, pa, ja);
		}
		if (wa != null)
			throw new Outcome(Outcome.Type.WA, wa);
		return new Outcome(Outcome.Type.OK, String.format("%d", n));
	}
}

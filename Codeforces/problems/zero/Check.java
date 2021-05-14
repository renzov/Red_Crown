import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
    Checker for NEERC'2010 Problem Z: Zero-complexity Transposition.
    @author Roman Elizarov
*/
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int n = inf.nextInt();
		String wa = null;
		for (int i = 0; i < n; i++) {
			long pa = ouf.nextLong();
			long ja = ans.nextLong();
			if (wa == null && ja != pa)
				wa = String.format("%d instead of %d", pa, ja);
		}
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		if (wa != null)
			throw new Outcome(Outcome.Type.WA, wa);
		return new Outcome(Outcome.Type.OK, String.format("%d", n));
	}
}

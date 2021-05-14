import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
 * Checker for NEERC'2010 Problem A: Alignment of Code.
 * @author Roman Elizarov
 */
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int lc = 0;
		while (!ans.isEoF()) {
			lc++;
			if (ouf.isEoF())
				throw new Outcome(Outcome.Type.WA, String.format("Abrupt end of file on line %d", lc));
			String pa = ouf.nextLine();
			String ja = ans.nextLine();
			if (!ja.equals(pa))
				throw new Outcome(Outcome.Type.WA, String.format("'%s' instead of '%s'", pa, ja));
		}
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.WA, "extra information in the output file");
		return new Outcome(Outcome.Type.OK, String.format("%d lines", lc));
	}
}

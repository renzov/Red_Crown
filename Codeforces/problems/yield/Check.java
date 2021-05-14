import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
    Checker for NEERC'2010 Problem Y: Yield.
    (C) Roman Elizarov
*/
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int pa = ouf.nextInt();
		int ja = ans.nextInt();
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		if (pa != ja)
			throw new Outcome(Outcome.Type.WA, String.format("%d instead of %d", pa, ja));
		return new Outcome(Outcome.Type.OK, String.format("%d", pa));
	}
}

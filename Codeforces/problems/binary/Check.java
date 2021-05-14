import ru.ifmo.testlib.*;
import java.math.BigInteger;

public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		String pa = ouf.nextToken();
		String ja = ans.nextToken();
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		if (!pa.equals(ja))
			throw new Outcome(Outcome.Type.WA, pa + " instead of " + ja);
		return new Outcome(Outcome.Type.OK, "" + pa);
	}
}

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.*;
import static java.lang.Math.*;

public class Check implements Checker {
	public Outcome test(InStream in, InStream ouf, InStream ans) {
		// read input
		int n = in.nextInt();
		long[] a = new long[n];
		for (int i = 0; i < n; i++)
			a[i] = in.nextInt();
		int m = in.nextInt();
		long[] b = new long[m];
		for (int i = 0; i < m; i++)
			b[i] = in.nextInt();

		// read ans & ouf
		String wa = null;
		long ja = ans.nextLong();
		long pa = ouf.nextLong();
		if (pa > ja)
			wa = "Expected: " + ja + ", found: " + pa;

		boolean[] u = new boolean[m];

		long pc = 0;
		for (int i = 0; i < n; i++) {
			int v = ouf.nextInt();
			if (v < 1 || v > m)  {
				if (wa == null) {
					wa = "Team " + (i + 1) + " - no such shelter " + v;
				}
				continue;
			} 
			v--;
			u[v] = true;
			pc = pc + abs(a[i] - b[v]);
		}

		// check that ouf is done
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "Extra information in the output file");

		// throw any wa seen so far
		if (wa != null)
			throw new Outcome(Outcome.Type.WA, wa);

		// check the rest of answer for WAs
		for (int i = 0; i < m; i++)
			if (!u[i])
				return new Outcome(WA, "No team goes to shelter " + (i + 1));

		if (pc != pa)
			return new Outcome(WA, "Promised " + pa + ", actually " + pc);

		if (pa < ja)
			return new Outcome(FAIL, "Expected: " + ja + ", found: " + pa);

		return new Outcome(OK, "" + ja);
	}
}

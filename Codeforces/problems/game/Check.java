import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
    Checker for NEERC'2010 Problem G: Game of 10.
    @author Roman Elizarov
*/
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		for (int moves = 1;; moves++) {
			String line = ouf.nextLine();
			if (line.length() == 0)
				throw new Outcome(Outcome.Type.FAIL, "Abrupt end of file");
			char ch = line.charAt(0);
			if ((moves % 2 == 1) && (ch >= 'A' && ch <= 'Z')) {
				// interact had written outcome instead of its move
				String[] s = line.split(" ", 2);
				Outcome.Type type = Outcome.Type.valueOf(s[0]);
				throw new Outcome(type, s[1]);
			}
			// otherwise just skip this line and go on...
		}
	}
}

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int ja = ans.nextInt();
        int pa = ouf.nextInt();
        if (ja != pa) {
            return new Outcome(WA, "Length expected: " + ja + ", found: " + pa);
        }
        for (int i = 0; i < ja; i++) {
            int j1 = ans.nextInt();
            int p1 = ouf.nextInt();
            if (j1 != p1) {
                return new Outcome(WA, "Wrong sequence, element " + i + " - expected: " + j1 + ", found: " + p1);
            }
            int j2 = ans.nextInt();
            int p2 = ouf.nextInt();
            if (j2 != p2) {
                return new Outcome(WA, "Wrong sequence, degree " + i + " - expected: " + j2 + ", found: " + p2);
            }
        }

        return new Outcome(OK, (ja == -1) ? "Not an integer" : ("Length = " + ja));
    }
}

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
            int jv = ans.nextInt();
            int pv = ouf.nextInt();
            if (jv != pv) {
                return new Outcome(WA, "Wrong sequence, element " + i + " - expected: " + jv + ", found: " + pv);
            }
        }

        return new Outcome(OK, "Length = " + ja);
    }
}

import ru.ifmo.testlib.*;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int jury = ans.nextInt();
        int cont = ouf.nextInt();
        if (!ouf.seekEoF()) {
            throw new Outcome(Outcome.Type.PE, "Extra information in the output file");
        }
        if (jury == cont) {
            return new Outcome(Outcome.Type.OK, String.valueOf(jury));
        } else {
            return new Outcome(Outcome.Type.WA, String.format("Expected %d, found %d", jury, cont));
        }
    }
}

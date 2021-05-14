/*--------------------------------------------------------------*/
/* ACM ICPC 2010-2011                                           */
/* Northeastern European Regional Contest                       */
/* St Petersburg - Barnaul - Tashkent - Batumi, November 24, 201*/
/*--------------------------------------------------------------*/
/* Problem D. Dome of Circus                                    */
/*                                                              */
/* Original idea         Georgiy Korneev                        */
/* Problem statement     Roman Elizarov                         */
/* Testset               Maxim Buzdalov                         */
/*--------------------------------------------------------------*/
/* Checker                                                      */
/*                                                              */
/* Author                Maxim Buzdalov                         */
/*--------------------------------------------------------------*/
 
import ru.ifmo.testlib.*;
import java.util.*;

/**
 * NEERC 2010
 * A checker for the problem Dome of Circus
 * @author Maxim Buzdalov
 */
public class Check implements Checker {
    static final double EPS = 1e-3;

    @Override
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        Locale.setDefault(Locale.US);
        double juryZ = ans.nextDouble();
        double juryR = ans.nextDouble();
        double contZ = ouf.nextDouble();
        double contR = ouf.nextDouble();
        if (!ouf.seekEoF())
	    throw new Outcome(Outcome.Type.PE, "extra information in the output file");
        if (contZ < 0 || contR < 0) {
            Outcome.quit(Outcome.Type.WA, "Some of the numbers are negative");
        }
        if (contZ * contR * contR > (juryZ + EPS) * (juryR + EPS) * (juryR + EPS)) {
            Outcome.quit(Outcome.Type.WA,
                    "Contestant's answer is not optimal: Z = %f, R = %f, V = %f" +
                    ", whereas jury's answer is Z = %f, R = %f, V = %f",
                    contZ, contR, contZ * contR * contR * Math.PI / 3,
                    juryZ, juryR, juryZ * juryR * juryR * Math.PI / 3);
        }
        //Checking the answer for validity
        int n = inf.nextInt();
        for (int i = 0; i < n; ++i) {
            double x = inf.nextDouble();
            double y = inf.nextDouble();
            double z = inf.nextDouble();
            double r = Math.sqrt(x * x + y * y);
            if (contR + EPS < r) {
                Outcome.quit(Outcome.Type.WA, "Contestant's answer does not cover vertex %d", i + 1);
            }
            double coneHeight = contZ * (contR - r) / contR;
            if (coneHeight + EPS < z) {
                Outcome.quit(Outcome.Type.WA, "Contestant's answer does not cover vertex %d", i + 1);
            }
        }
        if (juryZ * juryR * juryR > (contZ + EPS) * (contR + EPS) * (contR + EPS)) {
            Outcome.quit(Outcome.Type.FAIL,
                    "Contestant found a better answer: Z = %f, R = %f, V = %f" +
                    ", whereas jury's answer is Z = %f, R = %f, V = %f",
                    contZ, contR, contZ * contR * contR * Math.PI / 3,
                    juryZ, juryR, juryZ * juryR * juryR * Math.PI / 3);
        }
        return new Outcome(Outcome.Type.OK, "N = " + n);
    }
}

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem F: Factorial Simplification
 * @author Andrey Lopatin
 */

public class factorial_al {
  static final int MaxNM = 1000;
  static final int MaxV = 10000;
  static final int MaxA = 10007; //next prime after MaxV, using library method here hangs 


  static int rangeInt (String s, int a, int b) {
    int x = Integer.parseInt (s);
    if (x < a || x > b) {
      throw new RuntimeException (x + " is not in " + a + ".." + b);
    }
    return x;
  }


  public static void main (String args []) throws Exception {
    
    //build divisors list
    int [] D = new int [MaxA + 1], E = new int [MaxA + 1], P = new int [MaxA + 1];
    int pc = 0;

    for (int i = 2; i <= MaxA; i++) {
      if (D[i] == 0) {
        P[++pc] = i;
        D[i] = pc;
      }
      for (int j = 1; j <= D[i] && i * P[j] <= MaxA; j++) {
        D[i * P[j]] = j;
        E[i * P[j]] = i;
      }
    }

    //build factorial map
    int [][] M = new int [MaxA + 1][pc + 1];

    for (int i = 2; i <= MaxA; i++) {
      int a = i;
      while (a > 1) {
        ++M[i][D[a]];
        a = E[a];
      }
      for (int j = 1; j <= pc; j++) {
        M[i][j] += M[i - 1][j];
      }
    }


    BufferedReader in = new BufferedReader (new FileReader ("factorial.in"));
    PrintWriter out = new PrintWriter ("factorial.out");

    StringTokenizer t = new StringTokenizer (in.readLine ());
    int n = rangeInt (t.nextToken (), 1, MaxNM);
    int m = rangeInt (t.nextToken (), 1, MaxNM);
    if (t.hasMoreTokens ()) {
      throw new Exception ("EOL expected");
    }

    //loading source number
    int [] Q = new int [pc + 1];

    t = new StringTokenizer (in.readLine ());
    for (int i = 0; i < n; i++) {
      int a = rangeInt (t.nextToken (), 1, MaxV);
      for (int j = 1; j <= pc; j++) {
        Q[j] += M[a][j];
      }
    }
    if (t.hasMoreTokens ()) {
      throw new Exception ("EOL expected");
    }

    t = new StringTokenizer (in.readLine ());
    for (int i = 0; i < m; i++) {
      int a = rangeInt (t.nextToken (), 1, MaxV);
      for (int j = 1; j <= pc; j++) {
        Q[j] -= M[a][j];
      }
    }
    if (t.hasMoreTokens ()) {
      throw new Exception ("EOL expected");
    }

    if (in.ready ()) {
      throw new Exception ("EOF expected");
    }

    //checking the value is integer
    for (int j = 1; j <= pc; j++) {
      if (Q[j] < 0) {
        out.println ("-1");
        out.close ();
        return;
      }
    }

    //evaluating answer
    ArrayList <Integer> ans = new ArrayList <Integer> ();
    int cur = -1, deg = 0;
    for (;;) {
      int i;
      for (i = 2; i <= MaxA; i++) {
        int a = i;
        boolean fail = false;
        while (a > 1) {
          if (--Q[D[a]] < 0) {
            //System.out.println (a + " " + D[a] + " " + Q[D[a]]);
            fail = true;
          }
          a = E[a];
        }
        if (fail) {
          break;
        }
      }

      int a = i;
      while (a > 1) {
        ++Q[D[a]];
        a = E[a];
      }

      --i;

      if (i != cur) {
        if (deg > 0) {
          ans.add (cur);
          ans.add (deg);
        }
        cur = i;
        deg = 0;
      }

      if (i == 1) {
        break;
      }

      ++deg;
    }

    int k = ans.size () / 2;
    out.println (k);
    for (int i = 0; i < k; i++) {
      out.println (ans.get (2 * i) + " " + ans.get (2 * i + 1));
    }

    out.close ();
  }
}

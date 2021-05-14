import java.io.*;
import java.util.*;

/**
    Tests generator for NEERC'2010 Problem F: Factorial Simplification.
    @author Andrey Lopatin
    Based on sample from Roman Elizarov
*/
public class Tests {
  private static int TEST_COUNTER = 0;
  private static final File TESTS_DIR = new File("tests");
  private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

  private static final Random RND = new Random(2391717);

  private final PrintWriter out;

  private Tests(String description) throws IOException {
    String tn = String.format("%02d", ++TEST_COUNTER);
    File tests = new File("tests");
    tests.mkdir();
    PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
    lst.println(tn + " " + description);
    lst.close();
    out = new PrintWriter(new FileWriter(new File(tests, tn)));
  }


  private void write(int[] a, int[] b) {
    out.println(a.length + " " + b.length);
    for (int i = 0; i < a.length; i++) {
      out.print (a[i]);
      if (i < a.length - 1) {
        out.print (" ");
      } else {
        out.println ();
      }
    }
    for (int i = 0; i < b.length; i++) {
      out.print (b[i]);
      if (i < b.length - 1) {
        out.print (" ");
      } else {
        out.println ();
      }
    }
    out.close();
  }


  void writeShuffle (int[] a, int[] b) {
    int[] pa = new int [a.length], pb = new int [b.length];
    for (int i = 0; i < a.length; i++) {
      int t = RND.nextInt (i + 1);
      pa[i] = pa[t];
      pa[t] = i;
    }
    for (int i = 0; i < b.length; i++) {
      int t = RND.nextInt (i + 1);
      pb[i] = pb[t];
      pb[t] = i;
    }
    for (int i = 0; i < a.length; i++) {
      pa[i] = a[pa[i]];
    }
    for (int i = 0; i < b.length; i++) {
      pb[i] = b[pb[i]];
    }
    write (pa, pb);
  }



  public static void main(String[] args) throws IOException {
    TESTS_LST.delete();
    new Tests("Sample 1, no possible answer").write(new int[] {6}, new int[] {4, 4});
    new Tests("Sample 2, no factorials inside").write(new int[] {6}, new int[] {3, 4});
    new Tests("Sample 3, all number is representable").write(new int[] {9, 2, 2, 2}, new int[] {3, 4});
    new Tests("Smallest test").write(new int[] {1}, new int[] {1});
    new Tests("One Half").write(new int[] {1}, new int[] {2});
    new Tests("2!/1!").write(new int[] {2}, new int[] {1});
    new Tests("Small test, answer = 2!3!9!").write (new int[] {17, 6, 10, 11, 3}, new int [] {5, 5, 13, 7, 7, 5});

    int [] a, b;

    for (int tn = 0; tn < 2; tn++) {
      a = new int [RND.nextInt (5) + 5];
      b = new int [RND.nextInt (5) + 5];
      for (int i = 0; i < a.length; i++) {
        a[i] = RND.nextInt (10) + 11;
      }
      for (int i = 0; i < b.length; i++) {
        b[i] = RND.nextInt (10) + 5;
      }
      new Tests ("Small random test").write (a, b);
    }

    for (int tn = 0; tn < 5; tn++) {
      a = new int [RND.nextInt (100) + 901];
      b = new int [RND.nextInt (100) + 901];
      for (int i = 0; i < a.length; i++) {
        a[i] = RND.nextInt (5000) + 5001;
      }
      for (int i = 0; i < b.length; i++) {
        b[i] = RND.nextInt (5000) + 4901;
      }
      new Tests ("Random test (classic)").write (a, b);
    }


    a = new int [1000];
    Arrays.fill (a, 10000);
    b = new int [RND.nextInt (100) + 901];
    for (int i = 0; i < b.length; i++) {
      b[i] = RND.nextInt (5000) + 4901;
    }
    new Tests ("Max A, random B").write (a, b);
    
    
    b = new int [1000];
    Arrays.fill (b, 1);
    new Tests ("Max input").write (a, a);
    new Tests ("Max value of result (also maximal possible output number)").write (a, b);
    new Tests ("Test for underflow").write (b, a);

    b[2] = 2;
    b[3] = 3;
    b[9] = 9;

    new Tests ("Quite assymetric test with positive answer").write (new int[] {10000}, b);

    Arrays.fill (a, 8192);
    Arrays.fill (b, 8190);
    new Tests ("Max power of two (13000)").write (a, b);

    Arrays.fill (a, 9999);
    Arrays.fill (b, 9998);
    new Tests ("Large test with zero answer (9999!^1000 / 9998!^1000)").write (a, b);

    for (int i = 0; i < 1000; i++) {
      a[i] = i + 1;
    }
    Arrays.fill (b, 1);
    new Tests ("1 2 3 ... 1000 / 1 1 ... 1").writeShuffle (a, b);

    for (int i = 0; i < 1000; i++) {
      b[i] = i + 9001;
    }
    new Tests ("9001 9002 ... 10000 / 1 2 3 ... 1000").writeShuffle (b, a);


    int MaxA = 10000;
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

    for (int i = pc; i > pc - 1000; i--) {
      a[pc - i] = P[i];
    }
    Arrays.fill (b, 1); 
    new Tests ("p_{pmax} p_{pmax - 1} ... / 1 1 1 ... 1 (ans size 1003)").writeShuffle (a, b);

    for (int i = pc - 2; i > pc - 2 - 1000; i--) {
      a[pc - 2 - i] = P[i];
    }
    Arrays.fill (b, 1); 
    new Tests ("p_{pmax - 2} p_{pmax - 3} ... / 1 (ans size 1004)").writeShuffle (a, new int[] {1});

    for (int i = pc - 7; i > pc - 7 - 1000; i--) {
      a[pc - 7 - i] = P[i];
    }
    Arrays.fill (b, 1); 
    new Tests ("p_{pmax - 7} p_{pmax - 8} ... / 1 1 1 ... 1 (ans size 1006)").writeShuffle (a, b);

    int l = pc - 1000;


    for (int i = 1; i <= l; i++) {
      a[1000 - i] = P[i];
    }

    for (int i = pc; i > pc - l; i--) {
      a[pc - i] = P[i];
    }

    for (int i = l + 1; i <= pc - l; i++) {
      b[i - l - 1] = P[i];
    }

    new Tests ("Nice thing with primes").writeShuffle (a, b);

    int [][] M = new int [MaxA + 1][pc + 1];

    for (int i = 2; i <= MaxA; i++) {
      int t = i;
      while (t > 1) {
        ++M[i][D[t]];
        t = E[t];
      }
      for (int j = 1; j <= pc; j++) {
        M[i][j] += M[i - 1][j];
      }
    }


    RND.setSeed (427856748543L);

    for (int tn = 0; tn < 5; tn++) {

      int [] Q = new int [pc + 1];
      int la = RND.nextInt (501) + 500;
      int lb = RND.nextInt (501) + 500;

      a = new int [la];
      b = new int [lb];

      for (int i = 0; i < la; i++) {
        a[i] = RND.nextInt (RND.nextInt (10000) + 1) + 1;
        for (int j = 1; j <= pc; j++) {
          Q[j] += M[a[i]][j];
        }
      }

      for (int i = 0; i < lb; i++) {
        b[i] = RND.nextInt (RND.nextInt (10000) + 1) + 1;
        for (int j = 1; j <= pc; j++) {
          Q[j] -= M[b[i]][j];
        }
      }

      for (int i = pc; i >= 1; i--) {
        while (Q[i] < 0) {
          int steps;
          for (steps = 0; steps < 2000; ++steps) {
            int x = RND.nextInt (la);
            int aval = ((a[x] + P[i] - 1) / P[i]) * P[i];
            if (aval <= 10000) {
              for (int j = a[x] + 1; j <= aval; j++) {
                int t = j;
                while (t > 1) {
                  Q[D[t]]++;
                  t = E[t];
                }
              }
              a[x] = aval;
              break;
            }
            x = RND.nextInt (lb);
            int bval = (b[x] / P[i]) * P[i] - 1;
            if (bval > 0) {
              for (int j = b[x]; j > bval; j--) {
                int t = j;
                while (t > 1) {
                  Q[D[t]]++;
                  t = E[t];
                }
              }
              b[x] = bval;
              break;
            }
          }
          if (steps == 2000) {
            throw new RuntimeException ("failed to generate tests");
          }
        }
      }

      Q = new int [pc + 1];
      for (int i = 0; i < la; i++) {
        for (int j = 1; j <= pc; j++) {
          Q[j] += M[a[i]][j];
        }
      }

      for (int i = 0; i < lb; i++) {
        for (int j = 1; j <= pc; j++) {
          Q[j] -= M[b[i]][j];
        }
      }

      for (int j = 1; j <= pc; j++) {
        if (Q[j] < 0) {
          throw new RuntimeException ("another epic fail at " + j + ": " + Q[j]);
        }
      }


      new Tests ("Test constructed to guarantee positive answer").writeShuffle (a, b);
    }

    for (int tn = 0; tn < 5; tn++) {

      int [] Q = new int [pc + 1];
      int la = RND.nextInt (501) + 500;
      int lb = RND.nextInt (501) + 500;

      a = new int [la];
      b = new int [lb];

      for (int i = 0; i < la; i++) {
        a[i] = RND.nextInt (RND.nextInt (RND.nextInt (10000) + 1) + 1) + 1;
        for (int j = 1; j <= pc; j++) {
          Q[j] += M[a[i]][j];
        }
      }

      for (int i = 0; i < lb; i++) {
        b[i] = RND.nextInt (RND.nextInt (10000) + 1) + 1;
        for (int j = 1; j <= pc; j++) {
          Q[j] -= M[b[i]][j];
        }
      }

      for (int i = pc; i >= 1; i--) {
        while (Q[i] < 0) {
          int steps;
          for (steps = 0; steps < 2000; ++steps) {
            int x = RND.nextInt (la);
            int aval = ((a[x] + P[i] - 1) / P[i]) * P[i];
            if (aval <= 10000) {
              for (int j = a[x] + 1; j <= aval; j++) {
                int t = j;
                while (t > 1) {
                  Q[D[t]]++;
                  t = E[t];
                }
              }
              a[x] = aval;
              break;
            }
            x = RND.nextInt (lb);
            int bval = (b[x] / P[i]) * P[i] - 1;
            if (bval > 0) {
              for (int j = b[x]; j > bval; j--) {
                int t = j;
                while (t > 1) {
                  Q[D[t]]++;
                  t = E[t];
                }
              }
              b[x] = bval;
              break;
            }
          }
          if (steps == 2000) {
            throw new RuntimeException ("failed to generate tests");
          }
        }
      }


      boolean ok = false;

      for (int steps = 0; steps < 2000 && !ok; steps++) {
        if (RND.nextInt (2) == 0) {
          int x = RND.nextInt (la);
          if (a[x] > 1) {
            int t = a[x];
            while (t > 1) {
              Q[D[t]]--;
              if (Q[D[t]] < 0) {
                ok = true;
              }
              t = E[t];
            }
            --a[x];
          }
        } else {
          int x = RND.nextInt (lb);
          if (b[x] < 10000) {
            int t = b[x] + 1;
            while (t > 1) {
              Q[D[t]]--;
              if (Q[D[t]] < 0) {
                ok = true;
              }
              t = E[t];
            }
            ++b[x];
          }
        }
      }




      Q = new int [pc + 1];
      for (int i = 0; i < la; i++) {
        for (int j = 1; j <= pc; j++) {
          Q[j] += M[a[i]][j];
        }
      }

      for (int i = 0; i < lb; i++) {
        for (int j = 1; j <= pc; j++) {
          Q[j] -= M[b[i]][j];
        }
      }

      int lcnt = 0;

      for (int i = 1; i <= pc; i++) {
        if (Q[i] < 0) {
          ++lcnt;
        }
      }

      if (lcnt == 0) {
        throw new RuntimeException ("Yet another epic fail: lcnt = 0");
      }


      new Tests ("Test constructed to guarantee negative answer (bad primes: " + lcnt + ")").writeShuffle (a, b);
    }

    for (int tn = 0; tn < 3; tn++) {

      int [] Q = new int [pc + 1];
      int la = RND.nextInt (51) + 950;
      int lb = RND.nextInt (51) + 950;

      a = new int [la];
      b = new int [lb];

      for (int i = 0; i < la; i++) {
        a[i] = RND.nextInt (RND.nextInt (RND.nextInt (10000) + 1) + 1) + 1;
        for (int j = 1; j <= pc; j++) {
          Q[j] += M[a[i]][j];
        }
      }

      for (int i = 0; i < lb; i++) {
        b[i] = RND.nextInt (RND.nextInt (10000) + 1) + 1;
        for (int j = 1; j <= pc; j++) {
          Q[j] -= M[b[i]][j];
        }
      }

      for (int i = pc; i >= 1; i--) {
        while (Q[i] < 0) {
          int steps;
          for (steps = 0; steps < 2000; ++steps) {
            int x = RND.nextInt (la);
            int aval = ((a[x] + P[i] - 1) / P[i]) * P[i];
            if (aval <= 10000) {
              for (int j = a[x] + 1; j <= aval; j++) {
                int t = j;
                while (t > 1) {
                  Q[D[t]]++;
                  t = E[t];
                }
              }
              a[x] = aval;
              break;
            }
            x = RND.nextInt (lb);
            int bval = (b[x] / P[i]) * P[i] - 1;
            if (bval > 0) {
              for (int j = b[x]; j > bval; j--) {
                int t = j;
                while (t > 1) {
                  Q[D[t]]++;
                  t = E[t];
                }
              }
              b[x] = bval;
              break;
            }
          }
          if (steps == 2000) {
            throw new RuntimeException ("failed to generate tests");
          }
        }
      }

      Q = new int [pc + 1];
      for (int i = 0; i < la; i++) {
        for (int j = 1; j <= pc; j++) {
          Q[j] += M[a[i]][j];
        }
      }

      for (int i = 0; i < lb; i++) {
        for (int j = 1; j <= pc; j++) {
          Q[j] -= M[b[i]][j];
        }
      }

      for (int j = 1; j <= pc; j++) {
        if (Q[j] < 0) {
          throw new RuntimeException ("another epic fail at " + j + ": " + Q[j]);
        }
      }


      new Tests ("Large test with very small positive answer").writeShuffle (a, b);
    }

  }
}
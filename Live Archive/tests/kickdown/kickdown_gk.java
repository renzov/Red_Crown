import java.io.*;
import java.util.*;

public class kickdown_gk {
    public void run() throws Exception {
        Scanner scanner = new Scanner(new File("kickdown.in"));
        String master = scanner.next();
        String driven = scanner.next();
        scanner.close();

        int ans = driven.length() + master.length();
        for (int i = -master.length(); i <= driven.length(); i++) {
            boolean f = true;
            for (int j = 0; j < driven.length(); j++) {
                f &= 
                    ((j - i < 0 || j - i >= master.length()) ? 0 : master.charAt(j - i)) +
                    driven.charAt(j) - '0' - '0' <= 3;
            }
            if (f) {
                ans = Math.min(ans, Math.max(i + master.length(), driven.length()) - Math.min(i, 0));
            }
        }
        
        PrintWriter out = new PrintWriter("kickdown.out");
        out.println(ans);
        out.close();
    }

    public static void main(String[] args) throws Exception {
        new kickdown_gk().run();
    }
}
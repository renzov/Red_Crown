import java.io.*;
import java.util.*;

public class java_c_as {

    public void run() throws IOException {
        Scanner in = new Scanner(new File("java_c.in"));
        PrintWriter out = new PrintWriter(new File("java_c.out"));

        String id = in.next();
        assert id.length() > 0 && id.length() <= 100;
        boolean cpp = false;
        boolean java = false;
        for (int i = 0; i < id.length(); i++) {
            char c = id.charAt(i);
            assert ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
            if (c == '_') {
	            cpp = true;
            }
            if ('A' <= c && c <= 'Z') {
                java = true;
            }
        }

        if (java && cpp) {
            out.println("Error!");
        } else if (java) {
            if ('A' <= id.charAt(0) && id.charAt(0) <= 'Z') {
                out.println("Error!");
            } else {
                String r = "";
                for (int i = 0; i < id.length(); i++) {
                    char c = id.charAt(i);
                    if ('A' <= c && c <= 'Z') {
                        r += "_" + (char) (c - 'A' + 'a');
                    } else {
                        r += c;
                    }
                }
                out.println(r);
            }
        } else if (cpp) {
            boolean invalid = false;
            String r = "";
            boolean newWord = true;
            for (int i = 0; i < id.length(); i++) {
                char c = id.charAt(i);
                if (c == '_') {
                    if (newWord) {
                        invalid = true;
                    } else {
                        newWord = true;
                    }
                } else {
                    if (i != 0 && newWord) {
                        r += (char) (c + 'A' - 'a');
                    } else {
                        r += c;
                    }
                    newWord = false;
                }
            }
            if (newWord) {
                invalid = true;
            }
            if (invalid) {
                out.println("Error!");
            } else {
                out.println(r);
            }
        } else {
            out.println(id);
        }

        in.close();
        out.close();
    }

    public static void main(String[] arg) throws IOException {
        new java_c_as().run();
    }
}

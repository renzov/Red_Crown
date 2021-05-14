import java.io.*;
import java.util.*;

public class game_buzdalov_oneWA {
    static int[][] field;
    static int[] findWinningMove() {
        for (int h = 0; h <= 1; ++h) {
            boolean horiz = h == 1;
            for (int row = 0; row < 4; ++row) {
                int rem = 10;
                int zi = -1;
                for (int col = 0; col < 4; ++col) {
                    if ((horiz ? field[row][col] : field[col][row]) == 0) {
                        zi = zi == -1 ? col : -2;
                    } else {
                        rem -= (horiz ? field[row][col] : field[col][row]);
                    }
                }
                if (zi >= 0 && rem >= 1 && rem <= 4) {
                    return new int[] { horiz ? row : zi, horiz ? zi : row, rem };
                }
            }
        }
        return null;
    }

    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        field = new int[4][4];

        theLoop:
        while (true) {
            int x = in.nextInt() - 1;
            int y = in.nextInt() - 1;
            int v = in.nextInt();
            field[x][y] = v;
            //Try to make the winning move, if possible.
            int[] ans;
            if ((ans = findWinningMove()) != null) {
                out.println((ans[0] + 1) + " " + (ans[1] + 1) + " " + ans[2] + " WIN");
                out.flush();
                break theLoop;
            }
            //OK, no winning move possible
            for (int c = 0; c < 4; ++c) {
                if (field[x][c] == 0) {
                    field[x][c] = 5 - v;
                    if ((ans = findWinningMove()) == null) {
                        out.println((x + 1) + " " + (c + 1) + " " + (5 - v));
                        out.flush();
                        continue theLoop;
                    }
                    field[x][c] = 0;
                }
            }
            throw new RuntimeException();
        }
        out.close();
        in.close();
    }
}

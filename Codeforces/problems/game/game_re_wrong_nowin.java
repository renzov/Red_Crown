import java.util.Scanner;

/**
 * Wrong solution for NEERC'2010 Problem G: Game of 10
 * It wins, but it does not detect winning move as problem statement requires.
 * @author Roman Elizarov
 */
public class game_re_wrong_nowin {
	private static final int N = 4;

	public static void main(String[] args) throws Exception {
		new game_re_wrong_nowin().go();
	}

	void go() throws Exception {
		Scanner in = new Scanner(System.in);
		for (;;) {
			// read move
			int r = in.nextInt();
			int c = in.nextInt();
			int k = in.nextInt();
			// make symmetric move
			System.out.println((N + 1 - r) + " " + c + " " + (N + 1 - k));
		}
	}

}

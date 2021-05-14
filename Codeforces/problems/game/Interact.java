import solver.*;

import java.io.*;
import java.util.Random;
import java.util.Scanner;

/**
    Interaction for NEERC'2010 Problem G: Game of 10.
    @author Roman Elizarov
*/
public class Interact {
	private static final int N = Position.N;

	public static void main(String[] args) throws IOException {
		File mapFile = CostMap.FILE;
		if (args.length > 0)
			mapFile = new File(args[0]);
		File inFile = new File("game.in");
		if (args.length > 1)
			inFile = new File(args[1]);
		File outFile = new File("game.out");
		if (args.length > 2)
			outFile = new File(args[2]);
		new Interact(mapFile, inFile, outFile).go();
	}

	private final Field field;
	private final File inFile;
	private final File outFile;

	public Interact(File mapFile, File inFile, File outFile) throws IOException {
		this.inFile = inFile;
		this.outFile = outFile;
		field = new Field(CostMapView.getCostMap(mapFile));
	}

	private void go() throws IOException {
		Scanner fin = new Scanner(inFile);
		Move move = new Move(fin.nextInt() - 1, fin.nextInt() - 1, fin.nextInt());
		Strategy strategy = Strategy.valueOf(fin.next());
		fin.close();

		// will play deterministically, rand seed depending on the first move
		Strategy.rnd = new Random(move.hashCode());

		BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
		PrintStream fout = new PrintStream(new FileOutputStream(outFile), true);

		boolean ok = false;
		int moves = 0;
		for (;;) {
			// make our move
			if (move == null) {
				fout.println("WA Draw");
				break;
			}
			if (field.makeMove(move)) {
				fout.println(String.format("WA we win by moving to %d %d %d", move.r + 1, move.c + 1, move.k));
				break;
			}
			
			// write our move to file and to contestant
			writeMove(fout, move);
			writeMove(System.out, move);
			moves++;

			// read contestant's move
			String line = stdin.readLine();
			fout.println(line); // echo to file
			moves++;

			// parse contestant's move
			String[] tokens = line.split("\\s+");
			if (tokens.length != 3 && tokens.length != 4) {
				fout.println("PE 3 or 4 space-separated tokens expected on a line");
				break;
			}
			try {
				move = new Move(Integer.parseInt(tokens[0]) - 1, Integer.parseInt(tokens[1]) - 1, Integer.parseInt(tokens[2]));
			} catch (NumberFormatException e) {
				fout.println("PE numbers expected");
				break;
			}
			if (move.r < 0 || move.r >= N || move.c < 0 || move.c >= N || move.k < 1 || move.k > N) {
				fout.println("PE move numbers out of range");
				break;
			}
			boolean win = tokens.length == 4;
			if (win && !tokens[3].equals("WIN")) {
				fout.println("PE WIN expected as 4th token");
				break;
			}


			if (!field.canMove(move)) {
				fout.println("WA cell is busy");
				break;
			}

			if (field.makeMove(move)) {
				if (win) {
					fout.println(String.format("OK Win in %d moves", moves));
					ok = true;
				} else
					fout.println("WA Winning move was not marked as WIN");
				break;
			}
			if (win) {
				fout.println("WA Non-winning move is marked as WIN");
				break;
			}

			// make our move
			move = field.getMove(strategy);
		}
		fin.close();
		fout.close();
		System.exit(ok ? 0 : 1); // must terminate with zero exit code is Ok
	}

	private void writeMove(PrintStream out, Move move) {
		out.println((move.r + 1) + " " + (move.c + 1) + " " + move.k);
	}
}

/*
    Solution for NEERC'2006 Problem F: Fool's Game
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
*/

import java.io.*;
import java.util.*;

public class fool_re {
	public static void main(String[] args) throws Exception {
		new fool_re().go();
		//stress();
	}

	static final String SUITS = "SCDH";
	static final String RANKS = "6789TJQKA";

	static class Card {
		int rank;
		char suit;

		Card(String s) {
			assert s.length() == 2;
			rank = RANKS.indexOf(s.charAt(0));
			suit = s.charAt(1);
			assert rank >= 0 && isValidSuit(suit);
		}

		public boolean equals(Object obj) {
			if (!(obj instanceof Card))
				return false;
			Card o = (Card) obj;
			return rank == o.rank && suit == o.suit;
		}

		public String toString() {
			return "" + RANKS.charAt(rank) + suit;
		}
	}

	static final int TAKING = -1;
	static final int FIRST = 0;
	static final int SECOND = 1;
	static final int OPEN = 2;
	static final int COVERED = 3;
	static final int REMOVED = 4;

	static class Position {
		int move; // TAKING, FIRST, SECOND
		int starting; // FIRST, SECOND
		int[] state;

		Position(int n1, int n2) {
			move = FIRST;
			starting = FIRST;
			state = new int[n1 + n2];
			for (int i = 0; i < n1; i++)
				state[i] = FIRST;
			for (int i = n1; i < n1 + n2; i++)
				state[i] = SECOND;
		}

		Position(Position o) {
			move = o.move;
			starting = o.starting;
			state = o.state.clone();
		}

		public boolean equals(Object obj) {
			if (!(obj instanceof Position))
				return false;
			Position o = (Position) obj;
			return move == o.move && starting == o.starting && Arrays.equals(state, o.state);
		}

		public int hashCode() {
			return pack();
		}

		int pack() {
			int w = ((move + 1) << 1) + starting;
			for (int a : state) {
				w *= 5;
				w += a;
			}
			return w;
		}

		void unpack(int w) {
			for (int i = state.length; --i >= 0;) {
				state[i] = w % 5;
				w /= 5;
			}
			starting = w & 1;
			move = (w >> 1) - 1;
		}

		public void moveTable(int to) {
			for (int i = 0; i < state.length; i++) {
				if (state[i] == OPEN || state[i] == COVERED)
					state[i] = to;
			}
		}

		public int getActiveSide() {
			return move == TAKING ? starting : move;
		}
	}

	char trump;
	int n;
	Card[] c;
	int mode = 0; // 0 -- normal, others for debug

	Map<Integer, Integer> sv = new HashMap<Integer, Integer>();

	void go() throws Exception {
		Scanner in = new Scanner(new File("fool.in"));
		int n1 = in.nextInt();
		int n2 = in.nextInt();
		String strump = in.next();
		in.nextLine();

		assert n1 >= 1 && n1 <= 6;
		assert n2 >= 1 && n2 <= 6;
		assert strump.length() == 1;
		trump = strump.charAt(0);
		assert isValidSuit(trump);

		n = n1 + n2;
		c = new Card[n];
		for (int i = 0; i < n1; i++)
			c[i] = new Card(in.next());
		in.nextLine();
		for (int i = n1; i < n; i++)
			c[i] = new Card(in.next());
		in.nextLine();

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				assert !c[i].equals(c[j]);
			}
		}
		in.close();

		Position pos = new Position(n1, n2);
		int result = solve(pos);

		//System.out.println("Positions: " + sv.size());
		//printWinnignMoves(pos);
		
		PrintWriter out = new PrintWriter(new File("fool.out"));
		out.println(result == FIRST ? "FIRST": "SECOND");
		out.close();
	}

	int solve(Position p) {
		int w = p.pack();
		Integer svres = sv.get(w);
		if (svres != null)
			return svres;

		int fc = 0;
		int sc = 0;
		int tc = 0;
		int oc = 0;
		for (int i = 0; i < n; i++) {
			switch (p.state[i]) {
			case FIRST:
				fc++;
				break;
			case SECOND:
				sc++;
				break;
			case OPEN:
				oc++;
				// fallsthrough!!!
			case COVERED:
				tc++;
			}
		}

		if (fc == 0)
			return FIRST;
		if (sc == 0)
			return SECOND;

		int active = p.getActiveSide();
		int otherc = active == FIRST ? sc : fc;
		int result = -1;

		scan:
		{
			if (p.move == p.starting) {
				// Current player is starting
				if (tc == 0) {
					// toss first card
					for (int i = 0; i < n; i++) {
						if (p.state[i] == active) {
							p.state[i] = OPEN;
							result = solve(p);
							p.state[i] = active;
							if (result == active)
								break scan;
						}
					}
				} else {
					// tc > 0
					if (mode != 3 && oc < otherc) {
						// toss more
						for (int j = 0; j < n; j++) {
							if (p.state[j] == OPEN || p.state[j] == COVERED) {
								for (int i = 0; i < n; i++) {
									if (p.state[i] == active && c[i].rank == c[j].rank) {
										p.state[i] = OPEN;
										result = solve(p);
										p.state[i] = active;
										if (result == active)
											break scan;
									}
								}
							}
						}
					}
					// give up tossing
					if (oc == 0) {
						// other player covered it all -- she wins round, cards removed
						p.moveTable(REMOVED);
						p.move = 1 - active;
						p.starting = 1 - p.starting;
						result = solve(p);
						p.unpack(w);
					} else {
						// other player still covers -- surrender move to her
						p.move = 1 - active;
						result = solve(p);
						p.move = active;
					}
				}
			} else if (p.move == 1 - p.starting) {
				// Current player is covering
				assert tc > 0;
				if (oc == 0) {
					// covered it all -- surrender move
					p.move = 1 - active;
					result = solve(p);
					p.move = active;
				} else {
					// stuff to cover
					boolean cancover = false;
					for (int j = 0; j < n; j++) {
						if (p.state[j] == OPEN)
							for (int i = 0; i < n; i++) {
								if (p.state[i] == active && trumps(c[i], c[j])) {
									cancover = true;
									p.state[i] = COVERED;
									p.state[j] = COVERED;
									result = solve(p);
									p.state[i] = active;
									p.state[j] = OPEN;
									if (result == active)
										break scan;
								}
							}
					}
					// give up covering -- decide to take everything
					if (mode != 4 || cancover) {
						p.move = TAKING;
						result = solve(p);
						p.move = active;
					}
				}
			} else {
				// covering player has decided to take -- starting player can toss more card to her
				assert p.move == TAKING;
				if (mode != 1 && (oc < otherc || mode == 2)) {
					// toss more
					for (int j = 0; j < n; j++) {
						if (p.state[j] == OPEN || p.state[j] == COVERED) {
							for (int i = 0; i < n; i++) {
								if (p.state[i] == active && c[i].rank == c[j].rank) {
									p.state[i] = OPEN;
									result = solve(p);
									p.state[i] = active;
									if (result == active)
										break scan;
								}
							}
						}
					}
				}
				// give up tossing -- let the covering player actually take stuff
				p.moveTable(1 - p.starting);
				p.move = p.starting;
				result = solve(p);
				p.unpack(w);
			}
		}

		sv.put(w, result);
		return result;
	}

	private boolean trumps(Card a, Card b) {
		if (a.suit == b.suit)
			return a.rank > b.rank;
		else
			return a.suit == trump;
	}

//----------------- debug only ------------------

	static void stress() {
		int n1 = 6;
		int n2 = 6;
		int n = n1 + n2;
		Random r = new Random();
		int maxpos = 0;
		while (true) {
			fool_re inst = new fool_re();
			inst.trump = SUITS.charAt(r.nextInt(4));
			inst.n = n;
			inst.c = new Card[n];
			for (int i = 0; i < n; i++) {
			nextcard:
				while (true) {
					inst.c[i] = new Card("" + RANKS.charAt(r.nextInt(9)) + SUITS.charAt(r.nextInt(4)));
					for (int j = 0; j < i; j++) {
						if (inst.c[i].equals(inst.c[j]))
							continue nextcard;
					}
					break;
				}
			}
			Position pos = new Position(n1, n2);
			int result0 = inst.solve(pos);
//			inst.sv.clear();
//			inst.mode = 1;
//			int result1 = inst.solve(pos);
//			if (result0 != result1)
//				System.out.println("Results differ for " + Arrays.asList(inst.c) + " with trump " + inst.trump);
			if (inst.sv.size() > maxpos) {
				maxpos = inst.sv.size();
				System.out.println("Max position fos " + Arrays.asList(inst.c) + " with trump " + inst.trump + " = " + maxpos);
			}
		}
	}

	static class Move {
		String desc;
		Position next;

		Move(String desc, Position next) {
			this.desc = desc;
			this.next = new Position(next);
		}

		public String toString() {
			return desc;
		}
	}

	Set<Position> printed;

	void printWinnignMoves(Position p) {
		printed = new HashSet<Position>();
		printWinningMovesRec(p, getMoves(p), "", 3);
	}

	void printWinningMovesRec(Position p, List<Move> moves, String prefix, int depth) {
		int cc = 0;
		while (true) {
			if (moves == null || moves.size() > 1)
				break;
			Move m = moves.get(0);
			System.out.print(cc == 0 ? prefix : ", ");
			System.out.print(p.getActiveSide() == FIRST ? "F:" : "S:");
			System.out.print(m.desc);
			if (!printed.add(m.next)) {
				System.out.println(" [SEE ABOVE]");
				return;
			}
			cc++;
			p = m.next;
			moves = getMoves(p);
		}
		if (moves != null && depth == 0) {
			System.out.println(" ...");
			return;
		}
		if (cc > 0)
			System.out.println();
		if (moves != null) {
			for (Move m : moves) {
				printWinningMovesRec(p, Collections.singletonList(m), prefix + "  | ", depth - 1);
			}
		}
	}

	List<Move> getMoves(Position p) {
		List<Move> moves = new ArrayList<Move>();
		
		int w = p.pack();

		int fc = 0;
		int sc = 0;
		int tc = 0;
		int oc = 0;
		for (int i = 0; i < n; i++) {
			switch (p.state[i]) {
			case FIRST:
				fc++;
				break;
			case SECOND:
				sc++;
				break;
			case OPEN:
				oc++;
				// fallsthrough!!!
			case COVERED:
				tc++;
			}
		}

		if (fc == 0)
			return null;
		if (sc == 0)
			return null;

		int active = p.getActiveSide();
		int otherc = active == FIRST ? sc : fc;
		int result = -1;

		{
			if (p.move == p.starting) {
				// Current player is starting
				if (tc == 0) {
					// toss first card
					for (int i = 0; i < n; i++) {
						if (p.state[i] == active) {
							p.state[i] = OPEN;
							result = solve(p);
							Move m = new Move("TOSS " + c[i], p);
							p.state[i] = active;
							if (result == active)
								return Collections.singletonList(m);
							moves.add(m);
						}
					}
				} else {
					// tc > 0
					if (oc < otherc) {
						// toss more
						for (int j = 0; j < n; j++) {
							if (p.state[j] == OPEN || p.state[j] == COVERED) {
								for (int i = 0; i < n; i++) {
									if (p.state[i] == active && c[i].rank == c[j].rank) {
										p.state[i] = OPEN;
										result = solve(p);
										Move m = new Move("TOSS " + c[i], p);
										p.state[i] = active;
										if (result == active)
											return Collections.singletonList(m);
										moves.add(m);
									}
								}
							}
						}
					}
					// give up tossing
					if (oc == 0) {
						// other player covered it all -- she wins round, cards removed
						p.moveTable(REMOVED);
						p.move = 1 - active;
						p.starting = 1 - p.starting;
						result = solve(p);
						Move m = new Move("GIVE UP TOSSING (CARDS REMOVED)", p);
						p.unpack(w);
						if (result == active)
							return Collections.singletonList(m);
						moves.add(m);
					} else {
						// other player still covers -- surrender move to her
						p.move = 1 - active;
						result = solve(p);
						Move m = new Move("LET OTHER COVER", p);
						p.move = active;
						if (result == active)
							return Collections.singletonList(m);
						moves.add(m);
					}
				}
			} else if (p.move == 1 - p.starting) {
				// Current player is covering
				assert tc > 0;
				if (oc == 0) {
					// covered it all -- surrender move
					p.move = 1 - active;
					result = solve(p);
					Move m = new Move("LET OTHER TOSS", p);
					p.move = active;
					if (result == active)
						return Collections.singletonList(m);
					moves.add(m);
				} else {
					// stuff to cover
					for (int j = 0; j < n; j++) {
						if (p.state[j] == OPEN)
							for (int i = 0; i < n; i++) {
								if (p.state[i] == active && trumps(c[i], c[j])) {
									p.state[i] = COVERED;
									p.state[j] = COVERED;
									result = solve(p);
									Move m = new Move("COVER " + c[j] + " WITH " + c[i], p);
									p.state[i] = active;
									p.state[j] = OPEN;
									if (result == active)
										return Collections.singletonList(m);
									moves.add(m);
								}
							}
					}
					// give up covering -- decide to take everything
					p.move = TAKING;
					result = solve(p);
					Move m = new Move("GIVE UP COVERING", p);
					p.move = active;
					if (result == active)
						return Collections.singletonList(m);
					moves.add(m);
				}
			} else {
				// covering player has decided to take -- starting player can toss more card to her
				assert p.move == TAKING;
				if (oc < otherc) {
					// toss more
					for (int j = 0; j < n; j++) {
						if (p.state[j] == OPEN || p.state[j] == COVERED) {
							for (int i = 0; i < n; i++) {
								if (p.state[i] == active && c[i].rank == c[j].rank) {
									p.state[i] = OPEN;
									result = solve(p);
									Move m = new Move("TOSS IN " + c[i], p);
									p.state[i] = active;
									if (result == active)
										return Collections.singletonList(m);
									moves.add(m);
								}
							}
						}
					}
				}
				// give up tossing -- let the covering player actually take stuff
				p.moveTable(1 - p.starting);
				p.move = p.starting;
				result = solve(p);
				Move m = new Move("GIVE CARDS", p);
				p.unpack(w);
				if (result == active)
					return Collections.singletonList(m);
				moves.add(m);
			}
		}

		assert result == 1 - active; // other wins whatever we do
		return moves;
	}

	//----------------- just for validation ------------------

	static boolean isValidSuit(char s) {
		return SUITS.contains("" + s);
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could added to a soulution source
	 * without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public static class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(0) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}



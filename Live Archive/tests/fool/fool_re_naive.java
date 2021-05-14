/*
    Solution for NEERC'2006 Problem F: Fool's Game
    (C) Roman Elizarov
    Note: this solution attempts to check correctness of the input
    Note: This is NAIVE solution (slower)
*/

import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class fool_re_naive {
	public static void main(String[] args) throws Exception {
		new fool_re_naive().go();
	}

	static class Card {
		int rank;
		char suit;

		Card(String s) {
			assert s.length() == 2;
			switch (s.charAt(0)) {
				case '6':
					rank = 6;
					break;
				case '7':
					rank = 7;
					break;
				case '8':
					rank = 8;
					break;
				case '9':
					rank = 9;
					break;
				case 'T':
					rank = 10;
					break;
				case 'J':
					rank = 11;
					break;
				case 'Q':
					rank = 12;
					break;
				case 'K':
					rank = 13;
					break;
				case 'A':
					rank = 14;
					break;
				default:
					assert false : "wrong rank";
			}
			suit = s.charAt(1);
			assert isValidSuit(suit);
		}

		public boolean equals(Object obj) {
			if (!(obj instanceof Card))
				return false;
			Card o = (Card) obj;
			return rank == o.rank && suit == o.suit;
		}
	}

	static final int FIRST = 0;
	static final int SECOND = 1;
	static final int OPEN = 2;
	static final int COVERED = 3;
	static final int REMOVED = 4;

	static class Position {
		int move;
		int starting;
		int[] state;


		Position() {
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
			int result = (move << 1) + starting;
			for (int a : state) {
				result *= 5;
				result += a;
			}
			return result;
		}

		public void moveTable(int to) {
			for (int i = 0; i < state.length; i++) {
				if (state[i] == OPEN || state[i] == COVERED)
					state[i] = to;
			}
		}
	}

	char trump;
	int n;
	Card[] c;

	Map<Position, Integer> sv = new HashMap<Position, Integer>();

	void go() throws Exception {
		Scanner in = new Scanner(new File("fool.in"));
		int n1 = in.nextInt();
		int n2 = in.nextInt();
		String strump = in.next();

		assert n1 >= 1 && n1 <= 6;
		assert n2 >= 1 && n2 <= 6;
		assert strump.length() == 1;
		trump = strump.charAt(0);
		assert isValidSuit(trump);

		n = n1 + n2;
		c = new Card[n];
		for (int i = 0; i < n1; i++)
			c[i] = new Card(in.next());
		for (int i = n1; i < n; i++)
			c[i] = new Card(in.next());

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				assert !c[i].equals(c[j]);
			}
		}
		in.close();

		Position pos = new Position();
		pos.move = FIRST;
		pos.starting = FIRST;
		pos.state = new int[n];
		for (int i = 0; i < n1; i++)
			pos.state[i] = FIRST;
		for (int i = n1; i < n; i++)
			pos.state[i] = SECOND;
		int result = solve(pos);

		//System.out.println(sv.size());
		
		PrintWriter out = new PrintWriter(new File("fool.out"));
		out.println(result == FIRST ? "FIRST": "SECOND");
		out.close();
	}

	int solve(Position p) {
		Integer svres = sv.get(p);
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

		int otherc = p.move == FIRST ? sc : fc;
		int result = -1;

		scan:
		{
			if (p.move == p.starting) {
				// Current player is starting
				if (tc == 0) {
					// toss first card
					for (int i = 0; i < n; i++) {
						if (p.state[i] == p.move) {
							p.state[i] = OPEN;
							result = solve(p);
							p.state[i] = p.move;
							if (result == p.move)
								break scan;
						}
					}
				} else {
					// tc > 0
					if (oc < otherc) {
						// toss move
						for (int j = 0; j < n; j++) {
							if (p.state[j] == OPEN || p.state[j] == COVERED) {
								for (int i = 0; i < n; i++) {
									if (p.state[i] == p.move && c[i].rank == c[j].rank) {
										p.state[i] = OPEN;
										result = solve(p);
										p.state[i] = p.move;
										if (result == p.move)
											break scan;
									}
								}
							}
						}
					}
					// give up tossing
					if (oc == 0) {
						// other player covered it all -- she wins round, cards removed
						Position q = new Position(p);
						q.moveTable(REMOVED);
						q.move = 1 - q.move;
						q.starting = 1 - q.starting;
						result = solve(q);
					} else {
						// other player still covers -- surrender move to her
						p.move = 1 - p.move;
						result = solve(p);
						p.move = 1 - p.move;
					}
				}
			} else {
				// Current player is covering
				assert tc > 0;
				if (oc == 0) {
					// covered it all -- surrender move
					p.move = 1 - p.move;
					result = solve(p);
					p.move = 1 - p.move;
				} else {
					// stuff to cover
					for (int j = 0; j < n; j++) {
						if (p.state[j] == OPEN)
							for (int i = 0; i < n; i++) {
								if (p.state[i] == p.move && trumps(c[i], c[j])) {
									p.state[i] = COVERED;
									p.state[j] = COVERED;
									result = solve(p);
									p.state[i] = p.move;
									p.state[j] = OPEN;
									if (result == p.move)
										break scan;
								}
							}
					}
					// give up covering -- take everything
					Position q = new Position(p);
					q.moveTable(p.move);
					q.move = 1 - q.move;
					result = solve(q);
				}
			}
		}

		sv.put(new Position(p), result);
		return result;
	}

	private boolean trumps(Card a, Card b) {
		if (a.suit == b.suit)
			return a.rank > b.rank;
		else
			return a.suit == trump;
	}

	//----------------- just for validation ------------------

	static boolean isValidSuit(char s) {
		return s == 'S' || s == 'C' || s == 'D' || s == 'H';
	}
}



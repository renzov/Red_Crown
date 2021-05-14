import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2010 Problem H: Hands of Poker.
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class hands_re {
	static final int HAND_SIZE = 5;
	static final int C1 = HAND_SIZE - 1;
	static final int C2 = HAND_SIZE - 2;
	static final int C3 = HAND_SIZE - 3;
	static final int C4 = HAND_SIZE - 4;
	static final int C5 = HAND_SIZE - 5;

	static final String R = "23456789TJQKA";
	static final String S = "CDHS";

	static final int ACE = R.indexOf('A');
	static final int TWO = R.indexOf('2');
	static final int THREE = R.indexOf('3');
	static final int FOUR = R.indexOf('4');
	static final int FIVE = R.indexOf('5');

	static final int CARD_BITS = 4;
	static final int CARD_MASK = (1 << CARD_BITS) - 1;
	static final int FLUSH_SHIFT = HAND_SIZE * CARD_BITS;
	static final int FLUSH_MASK = 1 << FLUSH_SHIFT;

	static int getCard(int hand, int i) {
		assert i >= 0 && i < HAND_SIZE;
		return (hand >> (CARD_BITS * i)) & CARD_MASK;
	}

	static int setCard(int hand, int i, int rank) {
		assert i >= 0 && i < HAND_SIZE;
		int shift = CARD_BITS * i;
		return (hand & ~(CARD_MASK << shift)) | (rank << shift);
	}

	static int swapCard(int hand, int i, int j) {
		return setCard(setCard(hand, i, getCard(hand, j)), j, getCard(hand, i));
	}

	static int moveCard(int hand, int to, int from) {
		assert to >= from;
		for (int i = from; i < to; i++)
			hand = swapCard(hand, i, i + 1);
		return hand;
	}

	static boolean isFlush(int hand) {
		return (hand >> FLUSH_SHIFT) != 0;
	}

	static int setFlush(int hand) {
		return hand | FLUSH_MASK;
	}

	private static int clearFlush(int hand) {
		return hand & ~FLUSH_MASK;
	}

	static final int ACE_ROLLED_STRAIGHT =
			setCard(setCard(setCard(setCard(setCard(0,
					C1, ACE),
					C2, FIVE),
					C3, FOUR),
					C4, THREE),
					C5, TWO);

	public static void main(String[] args) throws Exception {
		new hands_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int hand;

	void read() throws Exception {
		Scanner in = new Scanner(new File("hands.in"));
		int[] r = new int[HAND_SIZE];
		int[] s = new int[HAND_SIZE];
		Set<String> cards = new HashSet<String>();
		for (int i = 0; i < HAND_SIZE; i++) {
			String card = in.next();
			assert card.length() == 2;
			r[i] = R.indexOf(card.charAt(0));
			s[i] = S.indexOf(card.charAt(1));
			assert r[i] >= 0 && s[i] >= 0;
			assert cards.add(card); // assert all cards are distinct
		}
		in.nextLine();
		Arrays.sort(r);
		for (int i = 0; i < HAND_SIZE; i++)
			hand = setCard(hand, i, r[i]);
		boolean flush = true;
		for (int i = 1; i < HAND_SIZE; i++)
			flush &= s[i] == s[i - 1];
		if (flush)
			hand = setFlush(hand);
		in.close();
	}

	enum Ranking {
		HIGH_CARD {
			@Override
			int map(int hand) {
				return hand;
			}},
		ONE_PAIR {
			@Override
			int map(int hand) {
				for (int i = HAND_SIZE; --i > 0;)
					if (getCard(hand, i) == getCard(hand, i - 1))
						return moveCard(moveCard(hand, C1, i), C2, i - 1);
				return -1;
			}},
		TWO_PAIRS {
			@Override
			int map(int hand) {
				hand = ONE_PAIR.map(hand);
				if (hand < 0)
					return -1;
				for (int i = HAND_SIZE - 2; --i > 0;)
					if (getCard(hand, i) == getCard(hand, i - 1))
						return moveCard(moveCard(hand, C3, i), C4, i - 1);
				return -1;
			}},
		THREE_OF_A_KIND {
			@Override
			int map(int hand) {
				for (int i = HAND_SIZE; --i > 1;)
					if (getCard(hand, i) == getCard(hand, i - 1) && getCard(hand, i) == getCard(hand, i - 2))
						return moveCard(moveCard(moveCard(hand, C1, i), C2, i - 1), C3, i - 2);
				return -1;
			}},
		STRAIGHT {
			@Override
			int map(int hand) {
				if (hand == ACE_ROLLED_STRAIGHT)
					return moveCard(hand, C1, C2);
				for (int i = HAND_SIZE; --i > 0;)
					 if (getCard(hand, i) != getCard(hand, i - 1) + 1)
						 return -1;
				return hand;
			}},
		FLUSH {
			@Override
			int map(int hand) {
				return isFlush(hand) ? hand : -1;
			}},
		FULL_HOUSE {
			@Override
			int map(int hand) {
				hand = THREE_OF_A_KIND.map(hand);
				return hand < 0 ? -1 : getCard(hand, C4) == getCard(hand, C5) ? hand : -1;
			}},
		FOUR_OR_A_KIND {
			@Override
			int map(int hand) {
				for (int i = HAND_SIZE; --i > 2;)
					if (getCard(hand, i) == getCard(hand, i - 1) && getCard(hand, i) == getCard(hand, i - 2) && getCard(hand, i) == getCard(hand, i - 3))
						return moveCard(moveCard(moveCard(moveCard(hand, C1, i), C2, i - 1), C3, i - 2), C4, i - 3);
				return -1;
			}},
		STRAIGHT_FLUSH {
			@Override
			int map(int hand) {
				return isFlush(hand) ? STRAIGHT.map(clearFlush(hand)) : -1;
			}};

		abstract int map(int hand);
	}

	static final Ranking[] RANKINGS = Ranking.values();

	static class Hand implements Comparable<Hand> {
		final int hand;
		final int map;
		final Ranking ranking;

		Hand(int hand) {
			this.hand = hand;
			for (int i = RANKINGS.length; --i >= 0;) {
				Ranking ranking = RANKINGS[i];
				int map = ranking.map(hand);
				if (map >= 0) {
					this.map = map;
					this.ranking = ranking;
					return;
				}
			}
			throw new AssertionError("This cannot happen");
		}

		public int compareTo(Hand o) {
			int i = ranking.compareTo(o.ranking);
			if (i != 0)
				return i;
			return map - o.map;
		}
	}

	final List<Hand> hands = new ArrayList<Hand>();

	void generate(int hand, int i, int high, int hc, boolean canflush) {
		if (hc > 1)
			canflush = false;
		if (i == -1) {
			generate(hand, -2, high, hc, canflush);
			if (canflush)
				generate(setFlush(hand), -2, high, hc, canflush);
		} else if (i == -2) {
			hands.add(new Hand(hand));			
		} else for (int card = high; card >= 0; card--)
			if (card < high || hc < S.length())
				generate(setCard(hand, i, card), i - 1, card, card < high ? 1 : (hc + 1), canflush);
	}

	int v;

	void solve() {
		generate(0, C1, ACE, 0, true);
		Collections.sort(hands);
		v = 0;
		boolean found = false;
		for (Hand hand : hands) {
			v++;
			if (hand.hand == this.hand) {
				System.err.println(hand.ranking);
				found = true;
				break;
			}
		}
		assert found;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("hands.out");
		out.println(v);
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to veryfy 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a soulution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
		final BufferedReader in;
		String line = "";
		int pos;
		int lineNo;

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
	}
}

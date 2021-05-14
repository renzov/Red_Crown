import java.io.*;
import java.util.*;

public class hands_buzdalov {
    static final Map<Character, Integer> rankMap = new HashMap<Character, Integer>();
    static final Map<Character, Integer> suitMap = new HashMap<Character, Integer>();
    static {
        for (int i = 0; i < 4; ++i) {
            suitMap.put("CDHS".charAt(i), i);
        }
        for (int i = 0; i < 13; ++i) {
            rankMap.put("23456789TJQKA".charAt(i), i);
        }
    }

    static class Card implements Comparable<Card> {
        public final int rank;
        public final int suit;
        public Card(int rank, int suit) {
            this.rank = rank;
            this.suit = suit;
        }
        public Card(String code) {
            this(rankMap.get(code.charAt(0)), suitMap.get(code.charAt(1)));
        }
        public int compareTo(Card that) {
            return rank - that.rank;
        }
        public String toString() { return "23456789TJQKA".charAt(rank) + "" + "CDHS".charAt(suit); }
    }
    static abstract class Hand<D extends Hand> implements Comparable<Hand> {
        public final int id;
        public Hand(int id) { this.id = id; }
        public int compareTo(Hand that) {
            if (id != that.id) return id - that.id;
            return compareToImpl((D) that);
        }
        public abstract int compareToImpl(D d);
    }
    static class SF extends Hand<SF> {
        public final int biggest;
        public SF(int biggest) { super(0); this.biggest = biggest; }
        public int compareToImpl(SF that) {
            return biggest - that.biggest;
        }
    }
    static class K4_1 extends Hand<K4_1> {
        public final int r4, r1;
        public K4_1(int r4, int r1) { super(-1); this.r4 = r4; this.r1 = r1; }
        public int compareToImpl(K4_1 that) {
            return r4 == that.r4 ? r1 - that.r1 : r4 - that.r4;
        }
    }
    static class K3_2 extends Hand<K3_2> {
        public final int r3, r2;
        public K3_2(int r3, int r2) { super(-2); this.r3 = r3; this.r2 = r2; }
        public int compareToImpl(K3_2 that) {
            return r3 == that.r3 ? r2 - that.r2 : r3 - that.r3;
        }
    }
    static class Flush extends Hand<Flush> {
        public final Card[] cards;
        public Flush(Card[] cards) { super(-3); this.cards = cards; }
        public int compareToImpl(Flush that) {
            for (int i = cards.length - 1; i >= 0; --i) {
                int diff = cards[i].compareTo(that.cards[i]);
                if (diff != 0) return diff;
            }
            return 0;
        }
    }
    static class Straight extends Hand<Straight> {
        public final int biggest;
        public Straight(int biggest) { super(-4); this.biggest = biggest; }
        public int compareToImpl(Straight that) {
            return biggest - that.biggest;
        }
    }
    static class K3_1_1 extends Hand<K3_1_1> {
        public final int r3, r1_1, r1_2;
        public K3_1_1(int r3, int r1_1, int r1_2) { super(-5); this.r1_1 = r1_1; this.r1_2 = r1_2; this.r3 = r3; }
        public int compareToImpl(K3_1_1 that) {
            if (r3 != that.r3) return r3 - that.r3;
            if (r1_1 != that.r1_1) return r1_1 - that.r1_1;
            return r1_2 - that.r1_2;
        }
    }
    static class K2_2_1 extends Hand<K2_2_1> {
        public final int r2_1, r2_2, r1;
        public K2_2_1(int r2_1, int r2_2, int r1) { super(-6); this.r2_1 = r2_1; this.r2_2 = r2_2; this.r1 = r1; }
        public int compareToImpl(K2_2_1 that) {
            if (r2_1 != that.r2_1) return r2_1 - that.r2_1;
            if (r2_2 != that.r2_2) return r2_2 - that.r2_2;
            return r1 - that.r1;
        }
    }
    static class Pair extends Hand<Pair> {
        public final int p;
        public final Card[] cards;
        public Pair(int p, Card[] cards) { super(-7); this.cards = cards; this.p = p; }
        public int compareToImpl(Pair that) {
            if (p != that.p) return p - that.p;
            for (int i = 3, j = 4, k = 4; i > 0; --i) {
                while (this.cards[j].rank == p) --j;
                while (that.cards[k].rank == p) --k;
                int diff = this.cards[j--].rank - that.cards[k--].rank;
                if (diff != 0) return diff;
            }
            return 0;
        }
    }
    static class High extends Hand<High> {
        public final Card[] cards;
        public High(Card[] cards) { super(-8); this.cards = cards; }
        public int compareToImpl(High that) {
            for (int i = cards.length - 1; i >= 0; --i) {
                int diff = cards[i].compareTo(that.cards[i]);
                if (diff != 0) return diff;
            }
            return 0;
        }
    }
    static Hand parse(Card... cards) {
        Arrays.sort(cards);
        for (int i = 1; i < cards.length; ++i) {
            if (cards[i - 1].rank == cards[i].rank && cards[i - 1].suit == cards[i].suit) {
                //a random but valid hand
                return new Straight(7);
            }
        }
        boolean isFlush = true;
        boolean isStraight = true;
        int rs = cards[0].rank;
        for (int i = 1; i < cards.length; ++i) {
            rs += cards[i].rank;
            isFlush &= cards[i - 1].suit == cards[i].suit;
            isStraight &= cards[i - 1].rank + 1 == cards[i].rank || i + 1 == cards.length && cards[i].rank == 12 && cards[i - 1].rank == 3;
        }
        if (isFlush && isStraight) {
            return new SF(cards[3].rank + 1 == cards[4].rank ? cards[4].rank : 3);
        } else if (cards[1].rank == cards[4].rank) {
            return new K4_1(cards[1].rank, cards[0].rank);
        } else if (cards[0].rank == cards[3].rank) {
            return new K4_1(cards[0].rank, cards[4].rank);
        } else if ((cards[0].rank == cards[1].rank && cards[2].rank == cards[4].rank)) {
            return new K3_2(cards[4].rank, cards[0].rank);
        } else if ((cards[0].rank == cards[2].rank && cards[3].rank == cards[4].rank)) {
            return new K3_2(cards[0].rank, cards[4].rank);
        } else if (isFlush) {
            return new Flush(cards);
        } else if (isStraight) {
            return new Straight(cards[3].rank + 1 == cards[4].rank ? cards[4].rank : 3);
        }
        for (int l = 0; l <= 2; ++l) {
            if (cards[l].rank == cards[l + 2].rank) {
                return new K3_1_1(cards[l].rank, l == 2 ? cards[1].rank : cards[4].rank, l == 0 ? cards[3].rank : cards[0].rank);
            }
        }
        for (int l = 0; l <= 1; ++l) {
            if (cards[l].rank != cards[l + 1].rank) continue;
            for (int r = l + 2; r <= 3; ++r) {
                if (cards[r].rank == cards[r + 1].rank) {
                    return new K2_2_1(cards[r].rank, cards[l].rank, rs - 2 * (cards[l].rank + cards[r].rank));
                }
            }
        }
        for (int l = 0; l < 4; ++l) {
            if (cards[l].rank == cards[l + 1].rank) {
                return new Pair(cards[l].rank, cards);
            }
        }
        return new High(cards);
    }
    static Set<Hand> generate() {
        Card[] cards = new Card[52];
        for (int j = 0, t = 0; j < 4; ++j) {
            for (int i = 0; i < 13; ++i, ++t) {
                cards[t] = new Card(i, j);
            }
        }
        Set<Hand> rv = new TreeSet<Hand>();
        for (int i0 = 0; i0 < 13; ++i0) {
        for (int i1 = i0; i1 < 13; ++i1) {
        for (int i2 = i1; i2 < 13; ++i2) {
        for (int i3 = i2; i3 < 13; ++i3) {
        for (int i4 = i3; i4 < 13; ++i4) {
            for (int s1 = 0; s1 < 52; s1 += 13) {
            for (int s2 = s1; s2 < 52; s2 += 13) {
            for (int s3 = s2; s3 < 52; s3 += 13) {
            for (int s4 = s3; s4 < 52; s4 += 13) {
                rv.add(parse(cards[i0], cards[i1 + s1], cards[i2 + s2], cards[i3 + s3], cards[i4 + s4]));
            }
            }
            }
            }
        }
        }
        }
        }
        }
        return rv;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("hands.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        in.close();

        Card[] cards = new Card[5];
        for (int i = 0; i < cards.length; ++i) {
            cards[i] = new Card(st.nextToken());
        }
        Hand h = parse(cards);
        Set<Hand> all = generate();
        int count = 0;
        for (Hand hh : all) {
            ++count;
            if (hh.compareTo(h) == 0) {
                break;
            }
        }
        PrintWriter out = new PrintWriter("hands.out");
        out.println(count);
        out.close();
    }
}

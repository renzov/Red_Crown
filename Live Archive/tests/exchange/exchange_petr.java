import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class exchange_petr {
    public static void main(String[] args) throws Exception {
        new exchange_petr().run();
    }

    static class Order {
        int count;
        int price;
        int id;
        int kind;
        boolean active;

        public Order(int id, int count, int price, int kind) {
            this.kind = kind;
            this.count = count;
            this.price = price;
            this.id = id;
            active = true;
        }
    }

    static class BuyComparator implements Comparator<Order> {
        public int compare(Order o1, Order o2) {
            if (o1.price > o2.price)
                return -1;
            else if (o1.price < o2.price)
                return 1;
            else if (o1.id < o2.id)
                return -1;
            else if (o1.id > o2.id)
                return 1;
            else
                return 0;
        }
    }

    static class SellComparator implements Comparator<Order> {
        public int compare(Order o1, Order o2) {
            if (o1.price < o2.price)
                return -1;
            else if (o1.price > o2.price)
                return 1;
            else if (o1.id < o2.id)
                return -1;
            else if (o1.id > o2.id)
                return 1;
            else
                return 0;
        }
    }

    int n;
    SortedSet<Order> buys = new TreeSet<Order>(new BuyComparator());
    SortedSet<Order> sells = new TreeSet<Order>(new SellComparator());
    Map<Integer, Order> all = new HashMap<Integer, Order>();
    int[] buyAmount;
    int[] sellAmount;

    private void run() throws Exception {
        Scanner scanner = new Scanner(new File("exchange.in"));
        PrintWriter writer = new PrintWriter("exchange.out");

        n = scanner.nextInt();
        buyAmount = new int[100000];
        sellAmount = new int[100000];

        for (int step = 0; step < n; ++step) {
            String w = scanner.next();

            if (w.compareTo("BUY") == 0) {
                int amount = scanner.nextInt();
                int price = scanner.nextInt();
                while (amount > 0 && sells.size() > 0) {
                    Order bestSell = sells.first();
                    if (bestSell.active) {
                        if (bestSell.price > price)
                            break;
                        int by = Math.min(bestSell.count, amount);
                        amount -= by;
                        bestSell.count -= by;
                        sellAmount[bestSell.price] -= by;
                        if (bestSell.count == 0)
                            bestSell.active = false;
                        writer.println("TRADE " + by + " " + bestSell.price);
                    } else sells.remove(bestSell);
                }
                Order we = new Order(step + 1, amount, price, 1);
                all.put(we.id, we);
                if (amount > 0) {
                    buys.add(we);
                    buyAmount[price] += amount;
                } else we.active = false;
            } else if (w.compareTo("SELL") == 0) {
                int amount = scanner.nextInt();
                int price = scanner.nextInt();
                while (amount > 0 && buys.size() > 0) {
                    Order bestBuy = buys.first();
                    if (bestBuy.active) {
                        if (bestBuy.price < price)
                            break;
                        int by = Math.min(bestBuy.count, amount);
                        amount -= by;
                        bestBuy.count -= by;
                        buyAmount[bestBuy.price] -= by;
                        if (bestBuy.count == 0)
                            bestBuy.active = false;
                        writer.println("TRADE " + by + " " + bestBuy.price);
                    } else buys.remove(bestBuy);
                }
                Order we = new Order(step + 1, amount, price, 2);
                all.put(we.id, we);
                if (amount > 0) {
                    sells.add(we);
                    sellAmount[price] += amount;
                } else we.active = false;
            } else if (w.compareTo("CANCEL") == 0) {
                int id = scanner.nextInt();
                Order o = all.get(id);
                if (o.active) {
                    o.active = false;
                    if (o.kind == 1)
                        buyAmount[o.price] -= o.count;
                    else
                        sellAmount[o.price] -= o.count;
                }
            } else {
                throw new Exception();
            }

            int askSize = 0;
            int askPrice = 99999;
            int bidSize = 0;
            int bidPrice = 0;

            while (sells.size() > 0) {
                Order bestSell = sells.first();
                if (bestSell.active) {
                    askPrice = bestSell.price;
                    askSize = sellAmount[askPrice];
                    break;
                } else sells.remove(bestSell);
            }

            while (buys.size() > 0) {
                Order bestBuy = buys.first();
                if (bestBuy.active) {
                    bidPrice = bestBuy.price;
                    bidSize = buyAmount[bidPrice];
                    break;
                } else buys.remove(bestBuy);
            }

            writer.println("QUOTE " + bidSize + " " + bidPrice + " - " + askSize + " " + askPrice);            
        }

        writer.close();
    }
}

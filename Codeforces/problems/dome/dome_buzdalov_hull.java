import java.io.*;
import java.util.*;

public class dome_buzdalov_hull {
    static final double EPS = 0;

    static boolean eq(double a, double b) {
        return Math.abs(a - b) <= EPS;
    }
    static int cmp(double a, double b) {
        return eq(a, b) ? 0 : a < b ? -1 : 1;
    }
    static boolean lt(double a, double b) {
        return a < b && !eq(a, b);
    }
    static boolean le(double a, double b) {
        return a < b || eq(a, b);
    }
    static boolean gt(double a, double b) {
        return a > b && !eq(a, b);
    }
    static boolean ge(double a, double b) {
        return a > b || eq(a, b);
    }

    static void a$$ert(String msg, boolean exp) {
        if (!exp) {
            throw new AssertionError(msg);
        }
    }

    static class Point {
        public final double x, y;

        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public double vmulAtMe(Point l, Point r) {
            return (l.x - x) * (r.y - y) - (l.y - y) * (r.x - x);
        }
        public double len2AtMe(Point p) {
            double dx = p.x - x;
            double dy = p.y - y;
            return dx * dx + dy * dy;
        }
    }

    static Point[] chull(Point[] pts) {
        if (pts.length == 0) {
            return pts;
        }
        for (int i = 1; i < pts.length; ++i) {
            if (lt(pts[i].x, pts[0].x) || eq(pts[i].x, pts[0].x) && lt(pts[i].y, pts[0].y)) {
                Point tmp = pts[0];
                pts[0] = pts[i];
                pts[i] = tmp;
            }
        }
        final Point zero = pts[0];
        Arrays.sort(pts, 1, pts.length, new Comparator<Point>() {
            public int compare(Point l, Point r) {
                double vm = zero.vmulAtMe(l, r);
                if (eq(vm, 0)) {
                    return cmp(zero.len2AtMe(l), zero.len2AtMe(r));
                } else {
                    return lt(vm, 0) ? 1 : -1;
                }
            }
        });
        List<Point> stack = new ArrayList<Point>();
        stack.add(pts[0]);
        for (int i = 1; i < pts.length; ++i) {
            if (!eq(pts[i].x, pts[i - 1].x) || !eq(pts[i].y, pts[i - 1].y)) {
                int sz = stack.size();
                while (sz > 1 && ge(0, stack.get(sz - 2).vmulAtMe(stack.get(sz - 1), pts[i]))) {
                    stack.remove(--sz);
                }
                stack.add(pts[i]);
            }
        }
        return stack.toArray(new Point[stack.size()]);
    }

    public static double[] solve(double[] r, double[] z) {
        Point[] pts = new Point[r.length];
        for (int i = 0; i < pts.length; ++i) {
            pts[i] = new Point(r[i], z[i]);
        }
        return solve(pts);
    }

    private static double[] solve(Point[] pts) {
        pts = chull(pts);
        double ansZ = Double.POSITIVE_INFINITY;
        double ansR = Double.POSITIVE_INFINITY;
        double ansV = Double.POSITIVE_INFINITY;
        for (int i = 0; i < pts.length; ++i) {
            Point curr = pts[i];
            Point next = pts[(i + 1) % pts.length];
            Point prev = pts[(i + pts.length - 1) % pts.length];
            double min = curr.x <= next.x ? 0 : Math.max(0, (curr.y - next.y) / (next.x - curr.x));
            double max = curr.x >= prev.x ? Double.POSITIVE_INFINITY : (curr.y - prev.y) / (prev.x - curr.x);
            //This is a test for a point being not in the upper chain
            if ((prev.x < curr.x || prev.x == curr.x && prev.y > curr.y) && (curr.x < next.x || curr.x == next.x && curr.y < next.y)) {
                continue;
            }
            if (min <= max) {
                double opt = 2 * curr.y / curr.x;
                if (min <= opt && opt <= max) {
                    double optZ = 3 * curr.y;
                    double optR = 1.5 * curr.x;
                    double optV = optR * optR * optZ;
                    if (ansV > optV) {
                        ansV = optV;
                        ansZ = optZ;
                        ansR = optR;
                    }
                } else {
                    double minZ = curr.y + curr.x * min;
                    double minR = curr.x + curr.y / min;
                    double minV = minR * minR * minZ;
                    double maxZ = curr.y + curr.x * max;
                    double maxR = curr.x + curr.y / max;
                    double maxV = maxR * maxR * maxZ;
                    if (minV <= maxV) {
                        if (ansV > minV) {
                            ansV = minV;
                            ansR = minR;
                            ansZ = minZ;
                        }
                    } else {
                        if (ansV > maxV) {
                            ansV = maxV;
                            ansR = maxR;
                            ansZ = maxZ;
                        }
                    }
                }
            }
        }
        return new double[] { ansZ, ansR };
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("dome.in"));
        int n = Integer.parseInt(in.readLine());
        a$$ert("N is out of bounds", 1 <= n && n <= 10000);
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            String s = in.readLine();
            int fws = s.indexOf(' ');
            int lws = s.lastIndexOf(' ');
            double x = Double.parseDouble(s.substring(0, fws));
            double y = Double.parseDouble(s.substring(fws + 1, lws));
            double z = Double.parseDouble(s.substring(lws + 1));
            a$$ert("X is out of bounds", -10000 <= x && x <= 10000);
            a$$ert("Y is out of bounds", -10000 <= y && y <= 10000);
            a$$ert("Z is out of bounds",      0 <  z && z <= 10000);
            pts[i] = new Point(Math.sqrt(x * x + y * y), z);
        }
        in.close();

        double[] res = solve(pts);

        PrintWriter out = new PrintWriter("dome.out");
        out.println(res[0] + " " + res[1]);
        out.close();
    }
}

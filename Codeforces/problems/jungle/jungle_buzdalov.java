import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class jungle_buzdalov {
    static class Point {
        public final int x, y;
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
        public Point subtract(Point arg) {
            return new Point(x - arg.x, y - arg.y);
        }
        public long vmul(Point arg) {
            return (long) (x) * arg.y - (long) (y) * arg.x;
        }
        public long smul(Point arg) {
            return (long) (x) * arg.x + (long) (y) * arg.y;
        }
        public String toString() {
            return "(" + x + "; " + y + ")";
        }
    }

    static class SegmentListElement {
        public final Point source, target;
        public SegmentListElement prev = this, next = this;
        public double left = 0;
        public double right = 1;

        public SegmentListElement(Point source, Point target) {
            this.source = source;
            this.target = target;
        }

        public boolean disappeared() {
            return left >= right;
        }
        public void removeMe() {
            prev.next = next;
            next.prev = prev;
            next = prev = null;
        }
    }

    static class SegmentList {
        private SegmentListElement last = null;

        public boolean insert(Point source, Point target) {
            SegmentListElement curr = new SegmentListElement(source, target);
            if (last == null) {
                last = curr;
            } else {
                curr.next = last.next;
                curr.next.prev = curr;
                curr.prev = last;
                curr.prev.next = curr;
                intersect(curr);
                intersect(curr.prev);
                if (!curr.disappeared()) {
                    last = curr;
                    while (curr.prev.disappeared() && curr.prev != curr) {
                        curr.prev.removeMe();
                        intersect(curr.prev);
                    }
                    while (curr.next.disappeared() && curr.next != curr) {
                        curr.next.removeMe();
                        intersect(curr);
                    }
                    if (curr.next == curr) {
                        last = null;
                    }
                }
            }
            return last != null;
        }
        private void intersect(SegmentListElement left) {
            SegmentListElement right = left.next;
            // L(TL - SL) * t + R(SR - TR) * u = D(SR - SL)
            Point L = left.target.subtract(left.source);
            Point R = right.source.subtract(right.target);
            if (L.vmul(R) <= 0) {
                //Equal, or intersecting not in this order
                return;
            }
            Point D = right.source.subtract(left.source);
            long det = L.vmul(R);
            long det0 = D.vmul(R);
            long det1 = L.vmul(D);
            if (det == 0) {
                if (L.vmul(D) == 0) {
                    throw new AssertionError("Segments are collinear. Must not happen");
                }
            } else {
                left.right = Math.min(left.right, (double) det0 / det);
                right.left = Math.max(right.left, (double) det1 / det);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("jungle.in"));
        int n = Integer.parseInt(in.readLine());
        Point[] pts = new Point[2 * n];
        for (int i = 0; i < n; ++i) {
            String s = in.readLine();
            int ws = s.indexOf(' ');
            pts[i] = pts[n + i] = new Point(Integer.parseInt(s.substring(0, ws)),
                               Integer.parseInt(s.substring(ws + 1)));
        }
        in.close();

        int left = 0;
        int right = (n + 1) / 2 - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            SegmentList list = new SegmentList();
            boolean hasInterior = true;
            for (int i = 0; i < n; ++i) {
                if (!list.insert(pts[i], pts[mid + 1 + i])) {
                    hasInterior = false;
                    break;
                }
            }
            if (hasInterior) {
                left = mid;
            } else {
                right = mid;
            }
        }

        PrintWriter out = new PrintWriter("jungle.out");
        out.println(right);
        out.close();
    }
}

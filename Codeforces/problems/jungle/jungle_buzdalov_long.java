import java.io.*;
import java.util.*;

public class jungle_buzdalov_long {
    static final boolean ALWAYS_LONG_COMPARE = false;

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

    static final long SEPARATOR = 10000000;
    static final long LIMIT = 500000000000000L;

    static int compare(long leftNum, long leftDen, long rightNum, long rightDen) {
        if (!ALWAYS_LONG_COMPARE &&
                Math.abs(leftNum) < Long.MAX_VALUE / Math.abs(rightDen) &&
                Math.abs(rightNum) < Long.MAX_VALUE / Math.abs(leftDen)) {
            long left = leftNum * rightDen;
            long right = rightNum * leftDen;
            //seem to be no overflow on real data
            return left == right ? 0 : left < right ? -1 : 1;
        }

        if (Math.abs(leftNum) >= LIMIT) throw new AssertionError("Possible overflow " + leftNum);
        if (Math.abs(leftDen) >= LIMIT) throw new AssertionError("Possible overflow " + leftDen);
        if (Math.abs(rightNum) >= LIMIT) throw new AssertionError("Possible overflow " + rightNum);
        if (Math.abs(rightDen) >= LIMIT) throw new AssertionError("Possible overflow " + rightDen);

        long leftNumB = leftNum / SEPARATOR;
        long leftNumS = leftNum % SEPARATOR;
        long leftDenB = leftDen / SEPARATOR;
        long leftDenS = leftDen % SEPARATOR;
        long rightNumB = rightNum / SEPARATOR;
        long rightNumS = rightNum % SEPARATOR;
        long rightDenB = rightDen / SEPARATOR;
        long rightDenS = rightDen % SEPARATOR;

        long leftMid = leftNumS * rightDenB + leftNumB * rightDenS;
        long leftSmall = leftNumS * rightDenS;
        long left12 = leftNumB * rightDenB + leftMid / SEPARATOR;
        long left06 = leftMid % SEPARATOR + leftSmall / SEPARATOR;
        long left00 = leftSmall % SEPARATOR;

        long rightMid = rightNumS * leftDenB + rightNumB * leftDenS;
        long rightSmall = rightNumS * leftDenS;
        long right12 = rightNumB * leftDenB + rightMid / SEPARATOR;
        long right06 = rightMid % SEPARATOR + rightSmall / SEPARATOR;
        long right00 = rightSmall % SEPARATOR;

        if (left12 != right12) {
            return left12 < right12 ? -1 : 1;
        }
        if (left06 != right06) {
            return left06 < right06 ? -1 : 1;
        }
        if (left00 != right00) {
            return left00 < right00 ? -1 : 1;
        }
        return 0;
    }

    static class SegmentListElement {
        public final Point source, target;
        public SegmentListElement prev = this, next = this;
        public long leftNum = 0, leftDen = 1;
        public long rightNum = 1, rightDen = 1;

        public SegmentListElement(Point source, Point target) {
            this.source = source;
            this.target = target;
        }

        public boolean disappeared() {
            return compare(leftNum, leftDen, rightNum, rightDen) >= 0;
        }
        public void removeMe() {
            prev.next = next;
            next.prev = prev;
            next = prev = null;
        }
        public String toString() {
            return source + "--" + (double) (leftNum) / leftDen + "--" + (double) (rightNum) / rightDen + "--" + target;
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
                if (det < 0) {
                    det = -det;
                    det0 = -det0;
                    det1 = -det1;
                }
                if (compare(det0, det, left.rightNum, left.rightDen) < 0) {
                    left.rightNum = det0;
                    left.rightDen = det;
                }
                if (compare(det1, det, right.leftNum, right.leftDen) > 0) {
                    right.leftNum = det1;
                    right.leftDen = det;
                }
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

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

public class driving_mb {
    private static final String INPUT_FILENAME = "driving.in";
    private static final String OUTPUT_FILENAME = "driving.out";

    Point startPoint;
    Point endPoint;
    int radius;
    Skyscraper[] skyscrapers;
    double answer;

    static final double EPSILON = 1e-6;

    final HashMap<Point, Node> nodes = new HashMap<Point, Node>();
    Node startNode;
    Node endNode;

    class Skyscraper {
        public int x1;
        public int y1;
        public int x2;
        public int y2;
    }

    static enum Color {
        WHITE,
        GRAY,
        BLACK
    }

    static class Point {
        final public double x;
        final public double y;

        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public String toString() {
            return Double.toString(x) + " " + Double.toString(y);
        }

        public int hashCode() {
            return (int) Math.rint(x / 1e-3) ^ (int) Math.rint (y / 1e-3);
        }

        public boolean equals(Object obj) {
            if (obj == null || !(obj instanceof Point)) {
                return false;
            }
            Point point = (Point) obj;
            return Math.abs(x - point.x) < EPSILON && Math.abs(y - point.y) < EPSILON;
        }
    }

    static class Node {
        final public Point point;
        final public Vector<Edge> edges = new Vector<Edge>();

        public Color color = Color.WHITE;
        public double distance;

        public Node(Point point) {
            this.point = point;
        }
    }

    static class Edge {
        final public double length;
        final public Node head;

        public Edge(double length, Node head) {
            this.length = length;
            this.head = head;
        }
    }

    static class Segment {
        final public Point start;
        final public Point end;

        public Segment(Point start, Point end) {
            this.start = start;
            this.end = end;
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        new driving_mb().run();
    }

    public void run() throws FileNotFoundException {
        readInput();
        solve();
        writeOutput();
    }

    private void writeOutput() throws FileNotFoundException {
        PrintWriter writer = new PrintWriter(new File(OUTPUT_FILENAME));
        if (answer > -EPSILON) {
            writer.println(answer);
        } else {
            writer.println("no solution");
        }
        writer.close();
    }

    private void solve() {
        buildGraph();
        runDijkstra();
    }

    static class NodeComparator implements Comparator<Node> {
        public int compare(Node o1, Node o2) {
            if (o1.distance < o2.distance) {
                return -1;
            } else if (o1.distance > o2.distance) {
                return +1;
            } else {
                return 0;
            }
        }
    }

    private void runDijkstra() {
        PriorityQueue<Node> queue = new PriorityQueue<Node>(nodes.size(), new NodeComparator());

        startNode.color = Color.BLACK;
        startNode.distance = 0;
        queue.add(startNode);

        answer = -1;

        while (!queue.isEmpty()) {
            Node node1 = queue.remove();
            node1.color = Color.BLACK;

            if (node1 == endNode) {
                answer = node1.distance;
                break;
            }

            for (Edge edge : node1.edges) {
                Node node2 = edge.head;
                double newDistance = node1.distance + edge.length;
                if (node2.color == Color.WHITE) {
                    node2.distance = newDistance;
                    node2.color = Color.GRAY;
                    queue.add(node2);
                } else if (node2.color == Color.GRAY && node2.distance > newDistance) {
                    queue.remove(node2);
                    node2.distance = newDistance;
                    queue.add(node2);
                }
            }
        }
    }

    private Node getNode(Point point) {
        Node node = nodes.get(point);
        if (node == null) {
            node = new Node(point);
            nodes.put(point, node);
        }
        return node;
    }

    private void addEdges(Node n1, Node n2, double length) {
        if (n1 != n2) {
            n1.edges.add(new Edge(length, n2));
            n2.edges.add(new Edge(length, n1));
        }
    }

    private void addStraightEdges(Node n1, Node n2) {
        double length = getDistance(n1.point.x,  n1.point.y,  n2.point.x,  n2.point.y);
        addEdges(n1, n2, length);
    }

    private void addCircularEdges(Node n1, Node n2) {
        double dist  = getDistance(n1.point.x,  n1.point.y,  n2.point.x,  n2.point.y);
        double phi = Math.asin(dist / radius / 2);
        double length = 2 * phi * radius;
        addEdges(n1, n2, length);
    }

    private double sqr(double x) {
        return  x * x;
    }

    private double getDistance(double x1, double y1, double x2, double y2) {
        return Math.sqrt(sqr(x1 - x2) + sqr(y1 - y2));
    }

    class DistanceResult {
        public double dist;
        public double x;
        public double y;
    }

    private void getDistance(double x0, double y0, double x1, double y1, double x2, double y2, DistanceResult result) {
        result.dist = Double.MAX_VALUE;

        double d1 = getDistance(x0, y0, x1, y1);
        if (d1 < result.dist) {
            result.dist = d1;
            result.x = x1;
            result.y = y1;
        }

        double d2 = getDistance(x0, y0, x2, y2);
        if (d2 < result.dist) {
            result.dist = d2;
            result.x = x2;
            result.y = y2;
        }

        double a = sqr(x2 - x1) + sqr(y2 - y1);
        double b = (x1 - x0) * (x2 - x1) + (y1 - y0) * (y2 - y1);
        double t = -b /a;
        if (t > -EPSILON && t < 1 + EPSILON) {
            double x = x1 + t * (x2 - x1);
            double y = y1 + t * (y2 - y1);
            double d3 = getDistance(x0, y0, x, y);
            if (d3 < result.dist) {
                result.dist = d3;
                result.x = x;
                result.y = y;
            }
        }
    }

    private boolean isInsideSkyscraper(Skyscraper skyscraper, double x, double y) {
        if (x < skyscraper.x1 - radius + EPSILON || y < skyscraper.y1 - radius + EPSILON ||
            x > skyscraper.x2 + radius - EPSILON || y > skyscraper.y2 + radius - EPSILON) {
            return false;
        }

        if (x < skyscraper.x1 + EPSILON && y < skyscraper.y1 + EPSILON) {
            return sqr(x - skyscraper.x1) + sqr(y - skyscraper.y1) < (double) (radius * radius) - EPSILON;
        }

        if (x > skyscraper.x2 - EPSILON && y < skyscraper.y1 + EPSILON) {
            return sqr(x - skyscraper.x2) + sqr(y - skyscraper.y1) < (double) (radius * radius) - EPSILON;
        }

        if (x < skyscraper.x1 + EPSILON && y > skyscraper.y2 - EPSILON) {
            return sqr(x - skyscraper.x1) + sqr(y - skyscraper.y2) < (double) (radius * radius) - EPSILON;
        }

        if (x > skyscraper.x2 - EPSILON && y > skyscraper.y2 - EPSILON) {
            return sqr(x - skyscraper.x2) + sqr(y - skyscraper.y2) < (double) (radius * radius) - EPSILON;
        }

        return true;
    }
    
    private boolean isInsideSkyscraper(double x, double y) {
        for (Skyscraper skyscraper : skyscrapers) {
            if (isInsideSkyscraper(skyscraper, x, y)) {
                return true;
            }
        }
        return false;
    }

    final DistanceResult distanceResult = new DistanceResult();

    private boolean checkIntersection(Skyscraper skyscraper, double x1, double y1, double x2, double y2) {
        getDistance(skyscraper.x1, skyscraper.y1,  x1, y1, x2, y2, distanceResult);
        if (distanceResult.dist < radius - EPSILON || isInsideSkyscraper(skyscraper, distanceResult.x, distanceResult.y)) {
            return true;
        }

        getDistance(skyscraper.x1, skyscraper.y2,  x1, y1, x2, y2, distanceResult);
        if (distanceResult.dist < radius - EPSILON || isInsideSkyscraper(skyscraper, distanceResult.x, distanceResult.y)) {
            return true;
        }

        getDistance(skyscraper.x2, skyscraper.y1,  x1, y1, x2, y2, distanceResult);
        if (distanceResult.dist < radius - EPSILON || isInsideSkyscraper(skyscraper, distanceResult.x, distanceResult.y)) {
            return true;
        }

        getDistance(skyscraper.x2, skyscraper.y2,  x1, y1, x2, y2, distanceResult);
        if (distanceResult.dist < radius - EPSILON || isInsideSkyscraper(skyscraper, distanceResult.x, distanceResult.y)) {
            return true;
        }
        
        return false;
    }

    private boolean checkIntersections(double x1, double y1, double x2, double y2) {
        for (Skyscraper skyscraper : skyscrapers) {
            if (checkIntersection(skyscraper, x1, y1, x2, y2)) {
                return true;
            }
        }
        return false;
    }

    private Vector<Segment> getTangentSegmentsBetweenCircles(double x0, double y0, double x1, double y1) {
        Vector<Segment> result = new Vector<Segment>(4);

        double xc = (x0 + x1) / 2;
        double yc = (y0 + y1) / 2;

        Vector<Point> tangentPoints = getTangentPointsFromPoint(x0, y0, xc, yc);
        for (Point tangentPoint : tangentPoints) {
            result.add(new Segment(tangentPoint, new Point(2 * xc - tangentPoint.x,  2 * yc - tangentPoint.y)));
        }

        double dx = x1 - x0;
        double dy = y1 - y0;
        double norm = Math.sqrt(sqr(dx) + sqr(dy));
        dx = dx / norm * radius;
        dy = dy / norm * radius;
        result.add(new Segment(new Point(x0 - dy, y0 + dx), new Point(x1 - dy, y1 + dx)));
        result.add(new Segment(new Point(x0 + dy, y0 - dx), new Point(x1 + dy, y1 - dx)));

        return result;
    }

    private Vector<Point> getTangentPointsFromPoint(double x0, double y0, double x1, double y1) {
        Vector<Point> result = new Vector<Point>(2);

        if (Math.abs(y0 - y1) < EPSILON) {
            if (Math.abs(x0 - x1) > radius - EPSILON) {
                double t = sqr(radius) / (x1 - x0);
                result.add(new Point(x0 + t, y0 + Math.sqrt(sqr(radius) - sqr(t))));
                result.add(new Point(x0 + t, y0 - Math.sqrt(sqr(radius) - sqr(t))));
            }
        } else {
            double a = sqr(x1 - x0) + sqr(y1 - y0);
            if (Math.abs(a) > EPSILON) {
                double b = sqr(radius) * (x1 - x0);
                double c = sqr(sqr(radius)) - sqr(radius) * sqr(y1 - y0);
                double d = sqr(b) - a * c;
                if (d >= -EPSILON) {
                    if (d < 0) {
                        d = 0;
                    }

                    double t1 = (b + Math.sqrt(d)) / a;
                    result.add(new Point(x0 + t1, y0 + ((sqr(radius) - t1 * (x1 - x0)) / (y1 - y0))));

                    double t2 = (b - Math.sqrt(d)) / a;
                    result.add(new Point(x0 + t2, y0 + ((sqr(radius) - t2 * (x1 - x0)) / (y1 - y0))));
                }
            }
        }
        return result;
    }

    private void processTangentPoints(Skyscraper skyscraper, Vector<Point> toCheck, Vector<Point> result) {
        for (Point point : toCheck) {
            if (!isInsideSkyscraper(skyscraper, point.x, point.y)) {
                result.add(point);
            }
        }
    }

    private Vector<Point> getTangentPoints(Skyscraper skyscraper, double x, double y) {
        Vector<Point> result = new Vector<Point>(2);
        processTangentPoints(skyscraper, getTangentPointsFromPoint(skyscraper.x1, skyscraper.y1, x, y), result);
        processTangentPoints(skyscraper, getTangentPointsFromPoint(skyscraper.x2, skyscraper.y1, x, y), result);
        processTangentPoints(skyscraper, getTangentPointsFromPoint(skyscraper.x1, skyscraper.y2, x, y), result);
        processTangentPoints(skyscraper, getTangentPointsFromPoint(skyscraper.x2, skyscraper.y2, x, y), result);
        return result;
    }

    private Point getCirclesSeparationPoints(double x0, double y0, double x1, double y1) {
        double dist = getDistance(x0, y0, x1, y1);
        if (dist > 2 * radius - EPSILON || Math.abs(x0 - x1) < EPSILON && Math.abs(y0 - y1) < EPSILON) {
            return null;
        }
        double dx = x1 - x0;
        double dy = y1 - y0;
        return new Point(x0 + dx / dist * radius, y0 + dy / dist * radius);
    }

    private Point[] getSkyscraperCorners(Skyscraper skyscraper) {
        return new Point[] {
                new Point(skyscraper.x1, skyscraper.y1),
                new Point(skyscraper.x1, skyscraper.y2),
                new Point(skyscraper.x2, skyscraper.y1),
                new Point(skyscraper.x2, skyscraper.y2)
        };
    }

    private static int compareAngles(double x0, double y0, double x1, double y1, double x2, double y2) {
        double dx1 = x1 - x0;
        double dy1 = y1 - y0;
        double dx2 = x2 - x0;
        double dy2 = y2 - y0;
        double det = dx2 * dy1 - dx1 * dy2;
        if (det > EPSILON) {
            return +1;
        } else if (det < -EPSILON) {
            return -1;
        } else {
            return 0;
        }
    }

    static class AngleComparator implements Comparator<Point> {
        private double x0;
        private double y0;

        public AngleComparator(double x0, double y0) {
            this.x0 = x0;
            this.y0 = y0;
        }

        public int compare(Point o1, Point o2) {
            return compareAngles(x0, y0, o1.x, o1.y, o2.x,  o2.y);
        }
    }

    private boolean isValidCornerPoint(Point p, double x0, double y0, double x1, double y1, double x2, double y2) {
        double xmin = Math.min(Math.min(x0, x1), x2);
        double ymin = Math.min(Math.min(y0, y1), y2);
        double xmax = Math.max(Math.max(x0, x1), x2);
        double ymax = Math.max(Math.max(y0, y1), y2);

        if (p.x < xmin - EPSILON || p.x > xmax + EPSILON || p.y < ymin - EPSILON || p.y > ymax + EPSILON) {
            return false;
        }

        if (isInsideSkyscraper(p.x,  p.y)) {
            return false;
        }

        return true;
    }

    private void buildCornerSubgraph(Skyscraper skyscraper1, double x0, double y0, double x1, double y1, double x2, double y2) {
        Vector<Point> cornerPoints = new Vector<Point>();
        Vector<Point> separationPoints = new Vector<Point>();

        cornerPoints.add(new Point(x1, y1));
        cornerPoints.add(new Point(x2, y2));

        for (Point point : getTangentPointsFromPoint(x0, y0, startNode.point.x, startNode.point.y)) {
            if (isValidCornerPoint(point, x0, y0, x1, y1, x2, y2)) {
                cornerPoints.add(point);
            }
        }

        for (Point point : getTangentPointsFromPoint(x0, y0, endNode.point.x, endNode.point.y)) {
            if (isValidCornerPoint(point, x0, y0, x1, y1, x2, y2)) {
                cornerPoints.add(point);
            }
        }

        for (Skyscraper skyscraper2 : skyscrapers) {
            if (skyscraper1 == skyscraper2) {
                continue;
            }
            Point[] corners = getSkyscraperCorners(skyscraper2);
            for (Point corner : corners) {
                Vector<Segment> tangentSegments = getTangentSegmentsBetweenCircles(x0, y0, corner.x, corner.y);
                for (Segment tangentSegment : tangentSegments) {
                    if (!checkIntersections(tangentSegment.start.x, tangentSegment.start.y, tangentSegment.end.x, tangentSegment.end.y)) {
                        cornerPoints.add(tangentSegment.start);
                    }
                }

                Point separationPoint = getCirclesSeparationPoints(x0, y0, corner.x, corner.y);
                if (separationPoint != null) {
                    separationPoints.add(separationPoint);
                }
            }
        }

        AngleComparator angleComparator = new AngleComparator(x0, y0);
        Collections.sort(cornerPoints, angleComparator);
        Collections.sort(separationPoints, angleComparator);

        int i = 0;
        int j = 0;
        while (i < cornerPoints.size()) {
            Point cornerPoint = cornerPoints.elementAt(i);
            Node cornerNode = getNode(cornerPoint);
            boolean makeEdge = true;

            for (;;)
            {
                if (j >= separationPoints.size()) {
                    break;
                }
                Point separationPoint = separationPoints.elementAt(j);
                if (compareAngles(x0, y0, cornerPoint.x,  cornerPoint.y, separationPoint.x,  separationPoint.y) < 0) {
                    break;
                }
                makeEdge = false;
                j++;
            }

            if (i > 0 && makeEdge) {
                Point prevCornerPoint = cornerPoints.elementAt(i - 1);
                Node prevCornerNode = getNode(prevCornerPoint);
                addCircularEdges(cornerNode, prevCornerNode);
            }
            i++;
        }
    }

    private void buildCornerSubgraphs(Skyscraper skyscraper) {
        buildCornerSubgraph(skyscraper, skyscraper.x1, skyscraper.y1,  skyscraper.x1 - radius, skyscraper.y1, skyscraper.x1, skyscraper.y1 - radius);
        buildCornerSubgraph(skyscraper, skyscraper.x2, skyscraper.y1,  skyscraper.x2, skyscraper.y1 - radius, skyscraper.x2 + radius, skyscraper.y1);
        buildCornerSubgraph(skyscraper, skyscraper.x2, skyscraper.y2,  skyscraper.x2 + radius, skyscraper.y2, skyscraper.x2, skyscraper.y2 + radius);
        buildCornerSubgraph(skyscraper, skyscraper.x1, skyscraper.y2,  skyscraper.x1, skyscraper.y2 + radius, skyscraper.x1 - radius, skyscraper.y2);
    }

    private void buildSideSubgraph(double x1, double y1, double x2, double y2) {
        if (!checkIntersections(x1, y1, x2, y2)) {
            Node n1 = getNode(new Point(x1, y1));
            Node n2 = getNode(new Point(x2, y2));
            addStraightEdges(n1, n2);
        }
    }

    private void buildSideSubgraphs(Skyscraper skyscraper) {
        buildSideSubgraph(skyscraper.x1, skyscraper.y1 - radius, skyscraper.x2, skyscraper.y1 - radius);
        buildSideSubgraph(skyscraper.x1, skyscraper.y2 + radius, skyscraper.x2, skyscraper.y2 + radius);
        buildSideSubgraph(skyscraper.x1 - radius, skyscraper.y1, skyscraper.x1 - radius, skyscraper.y2);
        buildSideSubgraph(skyscraper.x2 + radius, skyscraper.y1, skyscraper.x2 + radius, skyscraper.y2);
    }

    private void buildTangentEdges() {
        buildTangentEdgesFromPoint(startNode);
        buildTangentEdgesFromPoint(endNode);

        if (!checkIntersections(startNode.point.x,  startNode.point.y,  endNode.point.x,  endNode.point.y)) {
            addStraightEdges(startNode, endNode);
        }

        for (int i = 0; i < skyscrapers.length; i++) {
            Skyscraper skyscraper1 = skyscrapers[i];
            Point[] cornerPoints1 = getSkyscraperCorners(skyscraper1);
            for (int j = 0; j < cornerPoints1.length; j++) {
                Point cornerPoint1 = cornerPoints1[j];
                for (int k = i + 1; k < skyscrapers.length; k++) {
                    Skyscraper skyscraper2 = skyscrapers[k];
                    Point[] cornerPoints2 = getSkyscraperCorners(skyscraper2);
                    for (int l = 0; l < cornerPoints2.length; l++) {
                        Point cornerPoint2 = cornerPoints2[l];
                        Vector<Segment> tangentSegments = getTangentSegmentsBetweenCircles(cornerPoint1.x, cornerPoint1.y, cornerPoint2.x, cornerPoint2.y);
                        for (Segment tangentSegment : tangentSegments) {
                            if (!checkIntersections(tangentSegment.start.x, tangentSegment.start.y, tangentSegment.end.x, tangentSegment.end.y)) {
                                Node node1 = getNode(tangentSegment.start);
                                Node node2 = getNode(tangentSegment.end);
                                addStraightEdges(node1, node2);
                            }
                        }
                    }
                }
            }
        }
    }

    private void buildTangentEdgesFromPoint(Node node) {
        Point point = node.point;
        for (Skyscraper skyscraper : skyscrapers) {
            Vector<Point> tangentPoints = getTangentPoints(skyscraper, point.x, point.y);
            for (Point tangentPoint : tangentPoints) {
                if (!isInsideSkyscraper(tangentPoint.x, tangentPoint.y)) {
                    Node tangentNode = getNode(tangentPoint);
                    if (!checkIntersections(point.x,  point.y,  tangentPoint.x,  tangentPoint.y)) {
                        addStraightEdges(node, tangentNode);
                    }
                }
            }
        }
    }

    private void buildGraph() {
        startNode = getNode(startPoint);
        endNode = getNode(endPoint);

        for (Skyscraper skyscraper : skyscrapers) {
            buildSideSubgraphs(skyscraper);
            buildCornerSubgraphs(skyscraper);
        }

        buildTangentEdges();
    }

    private void readInput() throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(INPUT_FILENAME));
        radius = scanner.nextInt();
        int n = scanner.nextInt();

        int xstart = scanner.nextInt();
        int ystart = scanner.nextInt();
        startPoint = new Point(xstart, ystart);

        int xend = scanner.nextInt();
        int yend = scanner.nextInt();
        endPoint = new Point(xend, yend);

        skyscrapers = new Skyscraper[n];
        for (int i = 0; i < skyscrapers.length; i++) {
            Skyscraper skyscraper = new Skyscraper();
            skyscraper.x1 = scanner.nextInt();
            skyscraper.y1 = scanner.nextInt();
            skyscraper.x2 = scanner.nextInt();
            skyscraper.y2 = scanner.nextInt();
            skyscrapers[i] = skyscraper;
        }
    }
}

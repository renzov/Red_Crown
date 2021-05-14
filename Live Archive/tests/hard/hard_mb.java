import java.util.LinkedList;
import java.util.Scanner;
import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;

public class hard_mb {
    private static final String INPUT_FILENAME = "hard.in";
    private static final String OUTPUT_FILENAME = "hard.out";

    public static void main(String[] args) throws FileNotFoundException {
        new hard_mb().run();
    }

    public void run() throws FileNotFoundException {
        readInput();
        solve();
        writeOutput();
    }

    int n;
    int m;
    int numNodes;
    boolean[][] graph;
    int[] degrees;

    int sourceIndex;
    int sinkIndex;

    long[][] resCap;
    long[] excess;
    int[] height;
    int[] curArc;
    long scaleFactor;

    boolean[] minCutVisited;

    LinkedList<Integer> activeNodes;
    LinkedList<Integer> answer;

    private void writeOutput() throws FileNotFoundException {
        PrintWriter writer = new PrintWriter(new File(OUTPUT_FILENAME));
        writer.println(answer.size());
        for (Integer index : answer) {
            writer.println(index + 1);
        }
        writer.close();
    }

    private void solve() {
        allocate();
        calcDegrees();

        long lo = 0;
        long hi = n * scaleFactor;

        while (lo < hi - 1) {
            long mid = (lo + hi) / 2;
            if (tryGuess(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        tryGuess(lo);
    }

    private boolean tryGuess(long guess) {
        initPreflow(guess);
        findMaxFlow();
        return findMinCut();
    }

    private void minCutDfs(int i) {
        if (minCutVisited[i]) {
            return;
        }

        minCutVisited[i] = true;
        for (int j = 0; j < numNodes; j++) {
            if (resCap[j][i] > 0) {
                minCutDfs(j);
            }
        }
    }

    private boolean  findMinCut() {
        for (int i = 0; i < numNodes; i++) {
            minCutVisited[i] = false;
        }
        minCutDfs(sinkIndex);

        int numVisited = 0;
        for (int i = 0; i < n; i++) {
            if (minCutVisited[i]) {
                numVisited++;
            }
        }

        if (numVisited == n) {
            return false;
        }

        answer.clear();
        for (int i = 0; i < n; i++) {
            if (!minCutVisited[i]) {
                answer.add(i);
            }
        }

        return true;
    }

    private void allocate() {
        numNodes = n + 2;
        resCap = new long[numNodes][];
        for (int i = 0; i < numNodes; i++) {
            resCap[i] = new long[numNodes];
        }
        height = new int[numNodes];
        excess = new long[numNodes];
        activeNodes = new LinkedList<Integer>();
        minCutVisited = new boolean[numNodes];
        curArc = new int[numNodes];
        scaleFactor = 5 * numNodes * numNodes;
        answer = new LinkedList<Integer>();
    }

    private void findMaxFlow() {
        while (!activeNodes.isEmpty()) {
            int i = activeNodes.removeFirst();
            discharge(i);
        }
    }

    private void lift(int i) {
        int newHeight = Integer.MAX_VALUE;
        for (int j = 0; j < numNodes; j++) {
            if (resCap[i][j] > 0) {
                newHeight = Math.min(newHeight, height[j]);
            }
        }
        height[i] = newHeight + 1;
        curArc[i] = 0;
    }

    private void push(int i, int j) {
        long delta = Math.min(excess[i], resCap[i][j]);
        if (delta == 0)
            return;

        resCap[i][j] -= delta;
        resCap[j][i] += delta;
        if (excess[j] == 0 && j != sinkIndex) {
            activeNodes.addLast(j);
        }
        excess[j] += delta;
        excess[i] -= delta;
    }

    private void discharge(int i) {
        for (; ;) {
            while (curArc[i] < resCap.length) {
                int j = curArc[i];
                if (height[j] == height[i] - 1) {
                    push(i, j);
                }
                if (excess[i] == 0) {
                    return;
                }
                curArc[i]++;
            }
            lift(i);
        }
    }

    private void initPreflow(long guess) {
        sourceIndex = n;
        sinkIndex = n + 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                resCap[i][j] = graph[i][j] ? scaleFactor : 0;
            }

            resCap[sourceIndex][i] = m * scaleFactor;
            resCap[i][sourceIndex] = 0;

            resCap[i][sinkIndex] = 2 * guess + (m - degrees[i]) * scaleFactor;
            resCap[sinkIndex][i] = 0;
        }

        for (int i = 0; i < numNodes; i++) {
            excess[i] = i == sourceIndex ? Long.MAX_VALUE : 0;
            height[i] = i == sourceIndex ? numNodes : 0;
            curArc[i] = 0;
        }

        activeNodes.clear();
        for (int i = 0; i < n; i++) {
            push(sourceIndex, i);
        }
    }

    private void calcDegrees() {
        degrees = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j]) {
                    degrees[i]++;
                }
            }
        }
    }

    private void readInput() throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(INPUT_FILENAME));

        n = scanner.nextInt();
        m = scanner.nextInt();

        graph = new boolean[n][];
        for (int i = 0; i < n; i++) {
            graph[i] = new boolean[n];
        }

        for (int i = 0; i < m; i++) {
            int a = scanner.nextInt() - 1;
            int b = scanner.nextInt() - 1;
            graph[a][b] = true;
            graph[b][a] = true;
        }
    }
}

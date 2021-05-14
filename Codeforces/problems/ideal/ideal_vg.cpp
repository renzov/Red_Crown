#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

struct Edge
{
    Edge(int v, int c):v(v), c(c) {}
    int v, c;
};

const int INF = numeric_limits<int>::max();
const int NMAX = 100000;

int n;
typedef vector<Edge> Graph[NMAX];
Graph g;
vector<int> ans;

void bfs(int s, const Graph& g, vector<int>& d)
{
    queue<int> q;
    q.push(s);

    d.resize(n, INF);
    d[s] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for(size_t i = 0; i < g[v].size(); ++i) {
            const Edge& e = g[v][i];
            if (d[e.v] == INF) {
                d[e.v] = d[v] + 1;
                q.push(e.v);
            }
        }
    }
}

class ClearedUsed
{
public:
    ClearedUsed(size_t size)
        :used_(size, -1), curIdx_(0)
    {}

    void use(int idx)
    {
        used_[idx] = curIdx_;
    }

    bool isUsed(int idx)
    {
        return used_[idx] == curIdx_;
    }

    void clear()
    {
        ++curIdx_;
    }
private:
    int curIdx_;
    vector<int> used_;
};

int layer[2][NMAX];
int pos[2];

void solve() {
    vector<int> dFrom, dTo;
    int s = 0, t = n - 1;
    bfs(0, g, dFrom);
    int dist = dFrom[t];
    assert(dist != INF);
    bfs(t, g, dTo);

    vector<int> ans;

    ClearedUsed used(n);

    int ci = 0, ni = 1;
    pos[ci] = 1;
    layer[ci][0] = 0;
    for(int curDist = 0; curDist < dist; ++curDist) {
        int minColor = INF;

        for(size_t vertexIter = 0; vertexIter < pos[ci]; ++vertexIter) {
            int v = layer[ci][vertexIter];
            assert(dFrom[v] == curDist);
            for(size_t edgeIter = 0; edgeIter < g[v].size(); ++edgeIter) {
                const Edge& e = g[v][edgeIter];
                if (dTo[e.v] == dist - curDist - 1) {
                    if (e.c < minColor) {
                        minColor = e.c;
                        pos[ni] = 1;
                        layer[ni][0] = e.v;
                        used.clear();
                        used.use(e.v);
                    } else if (e.c == minColor && !used.isUsed(e.v)) {
                        layer[ni][pos[ni]++] = e.v;
                        used.use(e.v);
                    }
                }
            }
        }
        assert(minColor != INF);
        ans.push_back(minColor);

        pos[ci] = 0;
        swap(ci, ni);
    }
    
    assert(ans.size() == dist);
    printf("%d\n", ans.size());
    for(size_t i = 0; i < ans.size(); ++i) {
        if (i != 0) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
}

void readdata() {
    int m;
    assert(scanf("%d%d", &n, &m) == 2);
    assert(2 <= n && n <= 100000);
    assert(1 <= m && m <= 200000);
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        assert(scanf("%d%d%d", &a, &b, &c) == 3);
        assert(1 <= a && a <= n);
        assert(1 <= b && b <= n);
        assert(1 <= c && c <= 1e+9);
        --a; --b;
        g[a].push_back(Edge(b, c));
        g[b].push_back(Edge(a, c));
    }
}

int main() {
    freopen("ideal.in", "rt", stdin);
    freopen("ideal.out", "wt", stdout);
	readdata();
	solve();
	return 0;
}

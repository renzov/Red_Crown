#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 128;

vector<int> G[MAXN];
int P[MAXN];		// Shortest path from 1 to N
int W[MAXN][MAXN];	// Weight of the edges of G
int pre[MAXN];		// pre[u] is the father of u in the shortest path arborescence
int d[MAXN];		// d[u] distance of u from 1
int N, M;

void dijkstra(){
	for ( int i=1; i <= N; ++i ) d[i] = INT_MAX;
	d[1] = 0, pre[1] = -1;
	priority_queue< pii, vector<pii>, greater<pii> > q;
	q.push( pii( 0, 1 ) );

	int u, v, w;
	while ( !q.empty() ){
		u = q.top().second, w = q.top().first;
		q.pop();
		if ( w > d[u] ) continue;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			if ( w + W[u][v] < d[v] ){
				d[v] = w + W[u][v];
				pre[v] = u;
				q.push( pii( d[v], v ) );
			}
		}
	}
}

int main(){
	int u, v, w;
	
	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(v), G[v].push_back(u);
		W[u][v] = W[v][u] = w;
	}
	dijkstra();
	// Get a shortest path
	M = 0;
	u = N;
	do {
		P[M++] = u;
		u = pre[u];
	}
	while ( u != -1 );
	// Change the edges in the shortest path
	int base = d[N];
	int res = base;

	for ( int i=0; i < M - 1; ++i ){
		u = P[i], v = P[i + 1];
		w = W[u][v];
		W[u][v] = W[v][u] = w << 1;
		dijkstra();
		res = max( res, d[N] );
		W[u][v] = W[v][u] = w;
	}
	printf("%d\n", res - base);
	return 0;
}


#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 256;
const int MAXM = 25005;


int N, M, L;

int X[MAXM];
int Y[MAXM];
int W[MAXM];

vector<int> G[MAXN];

int d[MAXN];
int p[MAXN];
int best[MAXN];

void dijkstra(){
	int u, v, e, w, nw;

	fill( d, d + N, INT_MAX );
	fill( p, p + N, -1 );
	d[0] = 0;

	priority_queue< pii, vector<pii>, greater<pii> > Q;
	Q.push( pii( 0, 0 ) );

	while ( !Q.empty() ){
		u = Q.top().second;
		w = Q.top().first;
		Q.pop();

		if ( d[u] < w ) continue;
		if ( u == (N - 1) ) break;
		
		for ( int i=0; i < (int)G[u].size(); ++i ){
			e = G[u][i];
			v = X[e] ^ Y[e] ^ u;
			nw = w + W[e];
			if ( nw < d[v] ){
				d[v] = nw;
				p[v] = e;
				Q.push( pii( nw, v ) );
			}
		} 
	}
}

int main(){
	freopen ("rblock.in", "r", stdin);
	freopen ("rblock.out", "w", stdout);

	int u, v, e, D1, D2;
	scanf("%d %d", &N, &M);
	
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, W + i);
		u--, v--;
		X[i] = u, Y[i] = v;
		G[u].push_back(i);
		G[v].push_back(i);
	}
	// Find a shortest path
	dijkstra();
	D1 = d[N - 1];
	// Get edges in shortest path
	L = 0;
	u = N - 1;
	do {
		e = p[u];
		best[L++] = e;
		u = X[ e ] ^ Y[ e ] ^ u;
	}
	while ( u > 0 );
	// Change value for each edge in the shortest path
	D2 = D1; 
	for ( int i = 0; i < L; ++i ){
		e = best[i];
		W[e] <<= 1;
		dijkstra();	
		D2 = max( D2, d[N - 1] );
		W[e] >>= 1;
	}
	printf("%d\n", D2 - D1);
	return 0;
}

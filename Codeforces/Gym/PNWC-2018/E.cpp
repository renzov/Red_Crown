#include<cstdio>
#include<climits>
#include<algorithm>
#include<cassert>
using namespace std;
const int MAXM = 32;
const int INF = 1000000;
const int MAXV = 32*32*2;
const int MAXE = 32*32*32;

inline int in( const int &x ){ return x << 1; }
inline int out( const int &x ){ return (x << 1) | 1; }

char G[MAXM][MAXM];
int cost[MAXM];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
int V;

int m;
int from[MAXE];
int to[MAXE];
int nxt[MAXE];
int cap[MAXE];
int flow[MAXE];
int head[MAXV];

int pred[MAXV];
int q[MAXV];
int qt, qs;
int bneck[MAXV];

void add_edge( const int &u, const int &v, const int &c ){
	from[m] = u, to[m] = v, cap[m] = c, flow[m] = 0, nxt[m] = head[u], head[u] = m; m++;
	from[m] = v, to[m] = u, cap[m] = c, flow[m] = c, nxt[m] = head[v], head[v] = m; m++;
}

int max_flow( const int &s, const int &t ){
	int res = 0;
	int f;
	int u, v;
	int e;

	do {
		fill( pred, pred + V, -1 );
		fill( bneck, bneck + V, INT_MAX );
		// Search for an augmenting path
		qs = qt = 0;
		q[qt++] = s;
		while ( qs < qt && pred[t] == -1 ){
			u = q[qs++];
			for ( e = head[u]; e != -1; e = nxt[e] ){
				v = to[e];
				if ( pred[v] == -1 && flow[e] < cap[e] ){
					pred[v] = e;
					q[qt++] = v;
					bneck[v] = min( cap[e] - flow[e], bneck[u] );
				}
			}
		}
		if ( pred[t] != -1 ){	// flow augmentation
			v = t;
			f = bneck[t];
			while ( v != s ){
				e = pred[v];
				u = from[e];
				flow[e] += f;
				flow[e^1] -= f;
				v = u;
			}
			res += f;
		}
	}
	while ( pred[t] != -1 );
	return res;
}

int main(){
	int N, M, C;
	int S, T;
	int x, y;

	scanf("%d %d %d", &N, &M, &C);

	for ( int i=0; i < M; ++i )
		scanf("%s", G[i]);
	for ( int i=0; i < C; ++i )
		scanf("%d", cost + i );

	V = 2*N*M + 2;
	T = out(N*M);
	fill( head, head + V, -1 );

	// Now we add the arcs of the network
	add_edge( in(N*M), out(N*M), INT_MAX );
	for ( int i=0; i < M; ++i )
		for ( int j=0; j < N; ++j ){
			// add edge between in(v) and out(v)
			if ( G[i][j] == 'B' ){
				S = in(i*N + j);
				add_edge( in(i*N + j), out(i*N + j), INT_MAX );
			}
			else if ( G[i][j] == '.' ){
				add_edge( in(i*N + j), out(i*N + j), INT_MAX );				
			}
			else {
				add_edge( in(i*N + j), out(i*N + j), cost[ G[i][j] - 'a' ] );				
			}
			// add edge between adjacent vertices
			for ( int k=0; k < 4; ++k ){
				x = i + dx[k], y = j + dy[k];
				if ( x < 0 || y < 0 || x >= M || y >= N ) continue;
				add_edge( out( i*N + j ), in( x*N + y ), INT_MAX );
			}
			// add edge from border to sink
			if ( i == 0 || i == (M - 1) || j == 0 || j == (N - 1) ){
				add_edge( out( i*N + j ), in(N*M), INT_MAX );
			}
		}
	
	int res = max_flow( S, T );
	if ( res == INT_MAX ) puts("-1");
	else printf("%d\n", res);
	return 0;
}

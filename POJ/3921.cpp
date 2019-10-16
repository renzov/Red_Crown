#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
typedef pair<int,int> edge;
const int MAXN = 64;
const int MAXE = 5005;

int N, M, K;
int W[MAXN][MAXN];
edge E[MAXE];
int m;
int from[2*MAXE];
int to[2*MAXE];
int cap[2*MAXE];
int flow[2*MAXE];
int nxt[2*MAXE];
int head[2*MAXN];
int q[2*MAXN];
int qt, qf;
int bneck[2*MAXN];
int pre[2*MAXN];


inline int in(const int &v){ return v << 1; }
inline int out(const int &v){ return (v << 1) | 1; }

void add_edge( const int &u, const int &v, const int &c ){
	from[m] = u, to[m] = v, cap[m] = c, flow[m] = 0, nxt[m] = head[u], head[u] = m++;
	from[m] = v, to[m] = u, cap[m] = c, flow[m] = c, nxt[m] = head[v], head[v] = m++;
}

int max_flow( const int &s, const int &t ){
	int f = 0;
	int e;
	int eps;
	int u, v;

	do {
		// find an augmenting path
		fill( bneck, bneck + (N<<1), INT_MAX );
		fill( pre, pre + (N<<1), -1 );
		qt = qf = 0;
		q[qt++] = s;
		while ( qf < qt ){
			u = q[ qf++ ];
			for ( e = head[u]; e != -1; e=nxt[e] ){
				v = to[e];
				if ( v != s && cap[e] - flow[e] > 0 && pre[v] == -1 ){
					bneck[v] = min( bneck[u], cap[e] - flow[e] );
					pre[v] = e;
					q[ qt++ ] = v;
				}
			}
		}
		if ( bneck[t] < INT_MAX ){	// update residual network
			eps = bneck[t];
			f += eps;
			v = t;
			while ( v != s ){
				e = pre[v];
				flow[e] += eps;
				flow[e^1] -= eps;
				v = from[e];
			}
		}
	}
	while ( bneck[t] < INT_MAX );
	return f;
}

void floyd_warshall(){
	for ( int k=0; k < N; ++k )
		for ( int i=0;  i < N; ++i )
			for ( int j=0; j < N; ++j )
				if ( W[i][k] < INT_MAX && W[k][j] < INT_MAX )
					W[i][j] = min( W[i][j] , W[i][k] + W[k][j] );
}

void process(){
	// Initialize the data structures
	fill( head, head + (N << 1), -1 );
	m = 0;
	for ( int i=0; i < N; ++i ){
		W[i][i] = 0;
		for ( int j=i+1; j < N; ++j )
			W[i][j] = W[j][i] = INT_MAX;
	}	
	// Read the graph
	int u, v; 
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		E[i] = edge( u , v );
		W[u][v] = 1;
	}
	// set the arcs from in to out
	add_edge( in(0), out(0), INT_MAX );
	add_edge( in(N-1), out(N - 1), INT_MAX );
	for ( int i=1; i < N - 1; ++i )
		add_edge( in(i), out(i), 1 ); 
	// find shortest path between every pair
	floyd_warshall();
	// add the remaining edge to the network
	for ( int i=0; i < M; ++i ){
		u = E[i].first, v = E[i].second;
		if ( W[0][u] < INT_MAX && W[v][N - 1] < INT_MAX && W[0][u] + W[v][N-1] < K )
			add_edge( out(u), in(v), INT_MAX );
	}
	printf("%d\n", max_flow( in(0), out(N-1) ));
}

int main(){
	while ( scanf("%d %d %d", &N, &M, &K) && N )
		process();
	return 0;
}

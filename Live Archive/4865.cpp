#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 64;
const int MAXCAP = 100;
const int MAXE = 2*MAXN*MAXN + 6*MAXN;
int N, M;
int V[MAXN][MAXN];
bool cycle[MAXN][MAXN];
int R[MAXN];
int C[MAXN];

inline int row( const int &x ){ return x; }
inline int col( const int &x ){ return x + N; }
// Vertices 0 ... N - 1: rows
// Vertices N ... N + M - 1: columns
// Vertices N + M, N + M + 1: source and sink resp.
int from[MAXE];
int to[MAXE];
int cap[MAXE];
int flow[MAXE];
int nxt[MAXE];
int head[3*MAXN];
int E;
// Max flow variables
int q[3*MAXN];
int qt, qf;
int pre[3*MAXN];
int bneck[3*MAXN];
int n;
// DFS
int forbidden;	// Arc we can not traverse
int vis[3*MAXN];


void add_edge( const int &u, const int &v, const int &c ){
	from[E] = u, to[E] = v, cap[E] = c, flow[E] = 0, nxt[E] = head[u], head[u] = E++;
	from[E] = v, to[E] = u, cap[E] = c, flow[E] = c, nxt[E] = head[v], head[v] = E++;
}

int maxflow( const int &s, const int &t ){
	int f = 0;
	int eps;
	int u, v, e;
	do {
		// Initialize
		fill( pre, pre + n, -1 );
		bneck[s] = INT_MAX;
		qf = qt = 0;
		q[qt++] = s;
		
		while ( qf < qt && pre[t] == -1 ){
			u = q[qf++];
			for ( e = head[u]; e >= 0; e = nxt[e] ){
				v = to[e];
				if ( v != s && pre[v] == -1 && flow[e] < cap[e] ){
					pre[v] = e;
					q[qt++] = v;
					bneck[v] = min( bneck[u], cap[e] - flow[e] );
				}
			}
		}
		if ( pre[t] >= 0 ){
			eps = bneck[t];
			u = t;
			while ( u != s ){
				e = pre[u];
				flow[e] += eps;
				flow[e^1] -= eps;
				u = from[e];
			}
			f += eps;
		}
	}
	while ( pre[t] >= 0 );
	return f;
}

void dfs( const int &u ){
	vis[u] = true;
	int v;
	for ( int e=head[u]; e != -1 ; e=nxt[e] ){
		if ( e == forbidden ) continue;
		v = to[e];
		if ( v >= n - 2 ) continue;	// not traverse source and sink
		if ( !vis[v] && flow[e] < cap[e] )
			dfs( v );
	}
}

void process(){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			scanf("%d", V[i] + j);

	for ( int i=0; i < N; ++i ){
		scanf("%d", R + i);
		for ( int j=0; j < M; ++j )
			if ( V[i][j] >= 0 )
				R[i] -= V[i][j]; 
	}
	for ( int i=0; i < M; ++i ){
		scanf("%d", C + i);
		for ( int j=0; j < N; ++j )
			if ( V[j][i] >= 0 )
				C[i] -= V[j][i];
	}
	//puts("End reading");
	int source = N + M;
	int sink = N + M + 1;
	
	n = sink + 1;	// Number of vertices in the network
	fill( head, head + n, -1 );	// Initialize pointers
	E = 0;

	for ( int i=0; i < N; ++i )
		add_edge( source, row(i), R[i] );
	for ( int j=0; j < M; ++j )
		add_edge( col(j), sink, C[j] );
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			if ( V[i][j] < 0 )
				add_edge( row(i), col(j), MAXCAP );
	
	maxflow( source, sink );
	int u, v;
	int r, c;
	// Initialize matrix 
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			cycle[i][j] = false;
	
	for ( u=0; u < N; ++u ){
		for ( int e=head[u]; e != -1; e=nxt[e] ){
			v = to[e];
			if ( v == source || v == sink ) continue;
			r = u, c = v - N;
			V[r][c] = flow[e];	// solution value
			if ( flow[e] < cap[e] ){ // we can augment	
				fill( vis, vis + n, false );
				forbidden = e ^ 1;
				dfs( v );
				cycle[r][c] = vis[u];
			} 
			if ( cycle[r][c] ) continue;	// we already found a cycle
			if ( flow[e^1] < cap[e^1] ){	// we can decrease
				fill( vis, vis + n, false );
				forbidden = e;
				dfs( u );
				cycle[r][c] = vis[v];
			}
		}
	}
	
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < M; ++j ){
			if (j) putchar(' ');
			if ( cycle[i][j] ) printf("-1");
			else printf("%d", V[i][j]);
		}
		puts("");
	}
}

int main(){
	while ( scanf("%d %d", &N, &M) && N && M )
		process();
	return 0;
}

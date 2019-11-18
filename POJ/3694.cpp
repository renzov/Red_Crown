#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 100005;
const int NLOG = 18;

vector<int> G[MAXN];
int low[MAXN];
int dfsnum[MAXN];
int d[MAXN];
int num;
int N;
int M;
int log;
bool isbridge[MAXN];
int nxt[NLOG][MAXN];
int f[MAXN];
int bridges;

inline int find_set( const int &x ){	return ( x == f[x] )? x:( f[x] = find_set(f[x]) ); }
void join_sets( const int &u, const int &v ){
	if ( u == v ) return;
	if ( d[u] < d[v] ) f[v] = u;
	else f[u] = v;
}

int lca( int u, int v ){
	if ( u == v ) return u;
	if ( d[u] > d[v] ) swap(u, v);
	// d[u] <= d[v]
	for ( int i=log; i >= 0; --i )
		if ( (1<<i) <= (d[v] - d[u]) )
			v = nxt[i][v];
	if ( u == v ) return u;
	for ( int i=log; i >= 0; --i )
		if ( nxt[i][v] != nxt[i][u] )
			v = nxt[i][v], u = nxt[i][u];
	return nxt[0][u];
}

void dfs( const int &u, const int &p ){
	nxt[0][u] = p;
	dfsnum[u] = low[u] = num++;
	d[u] = ( p == -1 )? 0:(d[p] + 1);
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ){
			dfs( v, u );
			low[u] = min( low[u], low[v] );
			if ( !isbridge[v] )
				join_sets( find_set(u), find_set(v) );
			else 
				bridges++;
		}
		else if ( dfsnum[v] < dfsnum[u] ){
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	isbridge[u] = ( p != -1 && low[u] == dfsnum[u] );
}

void go_up_join(  int u,  int w ){
	int v;
	int res = 0;
	while ( u != w ){
		v = nxt[0][u];
		v = find_set(v);
		f[u] = v;
		u = v;
		bridges--;
	}
}

void process(){
	int u, v, w;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	num = 0;
	for ( int i=0; i < N; ++i )
		dfsnum[i] = -1, f[i] = i;
	// find depth, bridges and 2-edge-connected components and init LCA
	bridges = 0;
	dfs( 0 , -1 );
	// do LCA precomputation
	for ( log = 0; (1 << log) <= N; ++log ); log--;

	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j )
			if ( nxt[i-1][j] != -1 )
				nxt[i][j] = nxt[ i-1 ][ nxt[i-1][j] ];
			else
				nxt[i][j] = -1;

	// Ready to process the queries
	int Q, res;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		w = lca( u, v );
		u = find_set( u );
		v = find_set( v );
		res = 0;
		if 	( u != v ){
			w = find_set( w );	
			go_up_join( u, w );
			go_up_join( v, w );
		}
		printf("%d\n", bridges);
	}
	puts("");
}

int main(){
	int cases = 0;
	while ( scanf("%d %d", &N, &M) && N ){ 
		printf("Case %d:\n", ++cases );
		process();
		for ( int i=0; i < N; ++i ) G[i].clear();
	}
	return 0;
}

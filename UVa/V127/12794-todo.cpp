#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> edge;

const int MAXN = 10005;
const int MAXM = 2 * MAXN;

edge E[MAXM];
int W[MAXM];
bool isBridge[MAXM];
vector<int> G[MAXN];
int C[MAXN];
int dfsnum[MAXN];
int low[MAXN];
int f[MAXN];
int num = 0;

inline int find_set( const int &x ){ return ( x == f[x] )? x:( f[x] = find_set( f[x] ) );  }

void dfs( const int &u, const int &p ){
	dfsnum[u] = low[u] = num++;
	int v, e;

	for ( int i = 0; i < (int)G[u].size(); ++i ){
		e = G[u][i];
		v = E[e].first ^ E[e].second ^ u;
		if ( u == p ) continue;
		if ( dfsnum[v] == -1 ){
			dfs( v, u );
			low[u] = min( low[u], low[v] );
			if ( low[v] == dfsnum[v] )
				isBridge[e] = true;
		}
		else if ( dfsnum[v] < dfsnum[u] ){
			low[u] = min( low[u], dfsnum[v] );
		}
	}
}

void process( const int &N, const int &M ){
	int u, v;
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, W + i );
		u--, v--;
		E[i] = edge( u, v );
		G[u].push_back( i );
		G[v].push_back( i );
	}
	// Find the bridges of the graph
	fill( dfsnum, dfsnum + N, -1 );
	fill( isBridge, isBridge + M, false );
	for ( int i = 0; i < N; ++i )
		if ( dfsnum[i] == -1 )	
			dfs( i, -1 );
	
	// Find the weight of each cycle and compress
	for ( int i = 0; i < N; ++i )
		f[i] = i, C[i] = 0;

	for ( int i = 0; i < M; ++i )
		if ( !isBridge[i] ){
			u = E[i].first, v = E[i].second;
			u = find_set( u ), v = find_set( v );
			if ( u != v ){
				f[v] = u;
				C[u] += C[v];
			}
			C[u] += W[i];
		}
	// Create the tree that arises from the compression
	for ( int i = 0; i < M; ++i )
		if ( isBridge[i] ){
			u = E[i].first, v = E[i].second;
			u = find_set( u ), v = find_set( v );
			if ( u != v ){
				f[v] = u;
				C[u] += C[v];
			}
			C[u] += W[i];
		}


}

int main(){
	int N, M;
	while ( scanf("%d %d", &N, &M ) == 2 ){
		process( N, M );
		for ( int i = 0; i < N; ++i )
			G[i].clear();
	}
	return 0;
}

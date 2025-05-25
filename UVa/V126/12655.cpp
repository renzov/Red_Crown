#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXM = 100005;
const int MAXN = 20005;
const int NLOG = 17;

typedef pair<int, int> edge;
typedef pair<int, edge> wedge;

int N, M, S;
wedge E[MAXM];
vector<int> T[MAXN];
vector<int> W[MAXN];
int f[MAXN];
int L[MAXN];
int width[NLOG][MAXN];
int P[NLOG][MAXN];
int logN;

inline int find_set( const int &x ){ return ( x == f[x] )? x:( f[x] = find_set( f[x] ) ); }
inline void union_set( int x, int y ){ f[y] = x; }

int get_min( int v, int u ){
	// v is descendant of u 
	int res = INT_MAX;
	if ( v == u ) return res;
	for ( int i = logN; i >= 0; --i )
		if ( (L[v] - L[u]) >= (1 << i) ){
			res = min( res, width[i][v] );
			v = P[i][v];
		}
	return res;
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);
	// L[u] <= L[v]
	for ( int i = logN; i >= 0; --i )
		if ( (L[v] - L[u]) >= (1 << i) )
			v = P[i][v];
	// u and v are on the same level		
	if ( u == v ) return u;
	for ( int i = logN; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	}
	return P[0][u];
}

void preprocess_lca(){	
	for ( logN = 0; (1 << logN) < N; logN++ );
	logN--;

	int k;
	for ( int i = 1; i <= logN; ++i ){
		for ( int j = 0; j < N; ++j ){
			k = P[i - 1][j];
			if ( k == -1 ){
				P[i][j] = -1;
				width[i][j] = width[i - 1][j];
			}
			else {
				P[i][j] = P[i - 1][k];
				width[i][j] = min( width[i - 1][j], width[i - 1][k] );
			}
		}
	}
}

void dfs( const int &u, const int &pu ){
	if ( pu == -1 ) L[u] = 0;
	else L[u] = L[pu] + 1;

	int v, w;

	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		w = W[u][i];
		if ( v == pu ) continue;
		if ( P[0][v] == -1 ){
			P[0][v] = u;
			width[0][v] = w;
			dfs( v, u );
		}
	}
}

void process(){
	int u, v, w, z;

	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		E[i] = wedge( w, edge(u, v) );
	}
	// Kruskal's algorithm
	sort( E, E + M );
	// Initialize union_find
	for ( int i = 0; i < N; ++i )
		f[i] = i;
	
	// Find the max spanning tree
	for ( int i = M - 1; i >= 0; --i ){
		w = E[i].first;
		u = E[i].second.first;
		v = E[i].second.second;
		if ( find_set(u) != find_set(v) ){
			union_set( find_set(u), find_set(v) );
			T[u].push_back(v); W[u].push_back( w );
			T[v].push_back(u); W[v].push_back( w );
		}
	}
	// Preprocess tree for LCA queries
	width[0][0] = INT_MAX;
	fill( P[0], P[0] + N, -1 );
	dfs(0, -1);
	preprocess_lca();
	// Process the queries
	for ( int i = 0; i < S; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		z = lca( u, v );
		printf("%d\n", min( get_min( u, z ), get_min( v, z ) ) ); 
	}
}

void clean(){
	for ( int i = 0; i < N; ++i ){
		T[i].clear();
		W[i].clear();
	}
}

int main(){
	while ( scanf("%d %d %d", &N, &M, &S) == 3 ){
		process();
		clean();
	}
	return 0;
}

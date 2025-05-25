#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 50005;
const int LOG = 18;

int N;
int logN;
vector<int> T[MAXN];
int P[LOG][MAXN];
int L[MAXN];
int end_up[MAXN];
int end_down[MAXN];
int path_lca[MAXN];
int path_mid[MAXN];
int res;

void preprocess(){
	for ( logN = 0; (1 << logN) < N; ++logN  );
	logN--;
	
	for ( int i = 1; i <= logN; ++i )
		for ( int j = 0; j < N; ++j )
			P[i][j] = P[i - 1][j] == -1? -1:P[ i - 1 ][ P[ i - 1 ][ j ] ];
}

void dfs( const int &u, const int &p ){
	L[u] = p == -1? 0:(L[p] + 1);
	P[0][u] = p; 
	int v;
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( p == v ) continue;
		dfs(v, u);
	}
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);
	// L[u] <= L[v]
	for ( int i = logN; i >= 0; --i )
		if ( (L[v] - L[u]) >= (1 << i) )
			v = P[i][v];
	
	// L[u] == L[v]
	if ( u == v ) return u;

	for ( int i = logN; i >= 0; --i )
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];

	return P[0][u];
} 

void solve( const int &u, const int &p ){
	// returns the number of paths that will go above u
	int v;
	path_mid[u] = end_up[u] - 2 * path_lca[u] - end_down[u];
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		solve( v, u );
		path_mid[u] += path_mid[v];
	}
	res = max( res, path_mid[u] + path_lca[u] + end_down[u] );
}

int main(){
	freopen( "maxflow.in", "r", stdin );
	freopen( "maxflow.out", "w", stdout );

	int K;
	int u, v, w;

	scanf("%d %d", &N, &K);
	for ( int i = 1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	dfs( 0, -1 );
	preprocess();
	while ( K-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		w = lca(u, v);
		if ( w != u && w != v ){
			end_up[u]++;
			end_up[v]++;
			path_lca[w]++;
		}
		else if ( w == u ){
			end_down[u]++;
			end_up[v]++;
		}
		else {
			end_up[u]++;
			end_down[v]++;
		}
	}
	res = INT_MIN;
	solve( 0, -1 );
	printf("%d\n", res);
	return 0;
}

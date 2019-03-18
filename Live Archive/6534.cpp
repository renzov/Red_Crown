#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 40005;
const int NLOG = 16;
vector<int> T[MAXN];
vector<int> S[MAXN];
int nlog, qlog;
int LT[MAXN];
int LS[MAXN];
int PT[NLOG][MAXN];
int PS[NLOG][MAXN];
int D[MAXN];

void read_tree( const int &N, vector<int> G[] ){
	int u, v;
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v); G[v].push_back(u);
	}
}

int dfs( vector<int> G[], int L[], const int &u, const int &p, int par[] ){
	int v;
	int res = u;
	int best;
	par[u] = p;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		L[v] = L[u] + 1;
		best = dfs( G, L, v, u, par );
		if ( L[best] > L[res] ) res = best;
	}
	return res;
}

int lca( int u, int v, int P[][MAXN], int L[], const int &log  ){
	if ( L[u] > L[v] ) swap( u, v );
	// go up
	for ( int i=log - 1; i >= 0; --i )
		if ( L[v] - (1 << i) >= L[u] )
			v = P[ i ][ v ];
	if ( u == v ) return u;
	for ( int i=log - 1; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			v = P[i][v], u = P[i][u];
	}
	return P[0][u];
}

void preprocessLCA( int P[][MAXN], const int &log,  const int &n ){
	for ( int i=1; i < log; ++i )
		for ( int j=0; j < n; ++j )
			if ( P[i-1][j] != -1 ){
				P[i][j] = P[ P[i-1][j] ][j];
			}
			else {
				P[i][j] = -1;
			}
}

int main(){
	int N, Q;
	int diam;
	int aT, bT;	// Vertices that represent a diameter of T
	int aS, bS;	// Vertices that represent a diameter of S
	int d1, d2;
	int w;
	while ( scanf("%d %d", &N, &Q) == 2 ){
		read_tree( N, T );
		read_tree( Q, S );
		LT[0] = 0;
		aT = dfs( T, LT, 0, -1, PT[0] );
		LT[aT] = 0;
		bT = dfs( T, LT, aT, -1, PT[0] );

		LS[0] = 0;
		aS = dfs( S, LS, 0, -1, PS[0] );
		LS[aS] = 0;
		bS = dfs( S, LS, aS, -1, PS[0] );	
		diam = max( LT[bT], LS[bS] );
		// Precalculate LCA
		while ( (1 << nlog) < N ) nlog++;
		preprocessLCA( PT, nlog, N );
		while ( (1 << qlog) < Q ) qlog++;		
		preprocessLCA( PS, qlog, Q );
		// Find the longest path starting from every vertex in T
		for ( int i=0; i < N; ++i ){
			w = lca( i, aT, PT, LT, nlog );	
			d1 = LT[i] + LT[aT] - 2*LT[ w ];
			w = lca( i, bT, PT, LT, nlog );				
			d2 = LT[i] + LT[bT] - 2*LT[ w ];
			D[i] = max( d1, d2 );
		}
		long long res = 0;
		// Count the sum of every possible edge linking every pair of vertices

	}	
	return 0;
}

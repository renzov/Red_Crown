#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
const int NLOG = 18;

int L[MAXN];
int low[MAXN];
int dfsnum[MAXN];
int bridge[MAXN];
int P[NLOG][MAXN];
int log, num = 0;
vector<int> G[MAXN];

int lca( int a, int b ){
	if ( L[a] > L[b] )
		swap(a, b);
	
	for ( int i = log; i >= 0; --i )
		if ( (L[b] - L[a]) >= (1 << i) )
			b = P[i][b];

	if ( a == b ) return a;

	for ( int i = log; i >= 0; --i ){
		if ( P[i][a] != -1 && P[i][a] != P[i][b] )
			a = P[i][a], b = P[i][b];
	}
	return P[0][a];
}

void dfs( const int &u, const int &p ){
	int v;
	dfsnum[u] = low[u] = num++;
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ){
			L[v] = L[u] + 1;
			P[0][v] = u; 
			dfs( v, u );
			low[u] = min( low[u], low[v] );
		}
		else if ( dfsnum[v] < dfsnum[u] ){
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	bridge[u] = 0;
	if ( p != -1 && low[u] == dfsnum[u] ){ 
		bridge[u] = 1;
	}
}

void cntBridge( const int &u, const int &p ){
	int v;
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p || P[0][v] != u ) continue;
		bridge[v] += bridge[u];
		cntBridge( v, u );
	}
}

void precompute( const int &N ){
	for ( int i = 1; i <= log; ++i )
		for ( int u = 0; u < N; ++u )
			if ( P[i - 1][u] == -1 )
				P[i][u] = -1;
			else
				P[i][u] = P[i - 1][ P[i - 1][u] ];
}

int main(){
	int N, M, K;
	int u, v, root;
	freopen ("magic.in", "r", stdin);
	freopen ("magic.out", "w", stdout);

	scanf("%d %d %d", &N, &M, &root);
	root--;
	for ( log = 0; (1 << log) <= N; ++log );
	--log;

	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	// Precalc
	P[0][root] = -1;
	L[root] = 0;
	fill( dfsnum, dfsnum + N, -1 );
	dfs( root, -1 );
	cntBridge( root, -1 );
	precompute(N);

	scanf("%d", &K);
	while ( K-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		printf("%d\n", bridge[ lca(u, v) ]);
	}
	return 0;
}


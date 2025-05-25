#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 50005;
const int LOG = 18;

int N;
vector<int> T[MAXN];
int L[MAXN];
int P[MAXN][LOG + 5];

long long sum[MAXN] = {0};
long long sub[MAXN] = {0};

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);

	for ( int i=LOG - 1; i >= 0; --i )
		if ( (L[v] - L[u]) >= ( 1 << i ) )
			v = P[v][i];

	if ( u == v ) return u;
	
	for ( int j=LOG -  1; j >= 0; --j )
		if ( P[u][j] != -1 && P[u][j] != P[v][j] )
			u = P[u][j], v = P[v][j];

	return P[u][0];
} 


void dfs( const int &u, const int &p ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		L[v] = L[u] + 1;
		P[v][0] = u;
		dfs( v ,u );
	}
}

void solve( const int &u, const int &p ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		solve( v, u );
		sum[u] += ( sum[v] - sub[v] );
	}
}

void process(){
	int u, v; 

	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		T[u].push_back( v );
		T[v].push_back( u );
	}
	L[0] = 0;
	P[0][0] = -1;
	dfs( 0 , -1 );
	// LCA preprocess
	for ( int j=1; j < LOG; ++j )
		for ( int i=0; i < N; ++i ){
			P[i][j] = -1;
			if ( P[i][j - 1] != -1 )
				P[i][j] = P[ P[i][j - 1] ][j - 1];
		}
	// Process each query
	int Q, c, w;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d %d", &u, &v, &c );
		w = lca(u , v);
		sum[u] += c;
		sum[v] += c;
		sum[w] -= c;
		sub[w] += c;
	}
	solve( 0, -1 );
	for ( int i=0; i < N; ++i )
		printf("%lld\n", sum[i]);
}

void clean(){
	for ( int i=0; i < N; ++i ){
		sum[i] = sub[i] = 0;
		T[i].clear();
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	for ( int i=1; i <= runs; ++i ){
		printf("Case #%d:\n", i);
		process();
		clean();
	}
	return 0;
}

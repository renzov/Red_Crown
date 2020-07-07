#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
int N, Q;
const int MAXN = 200005;
const int LOG = 22;
vector<int> T[MAXN];
int L[MAXN];
int P[LOG][MAXN];
int V[MAXN];
int logn;

void dfs( const int &u, const int &p ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		L[v] = L[u] + 1;
		P[0][v] = u;
		dfs(v, u);
	}
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);
	for ( int i=logn; i >= 0; --i ){
		if ( (L[v] - L[u]) >= (1 << i) ){
			v = P[i][v];
		}
	}
	if ( u == v ) return u;
	for ( int i=logn; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] ){
			u = P[i][u], v = P[i][v];
		}
	}
	return P[0][u];
}

int main(){
	int u, v, w;
	scanf("%d %d", &N, &Q);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v), T[v].push_back(u);
	}

	P[0][0] = -1;
	dfs( 0, -1 );
	// preprocess
	for ( logn=0; (1 << logn) <= N; ++logn );
	logn--;
	assert( logn < LOG );
	for ( int i=1; i <= logn; ++i )
		fill( P[i], P[i] + N, -1 );

	for ( int i=1; i <= logn; ++i )
		for ( int j=0; j < N; ++j )
			if ( P[i - 1][j] != -1 )
				P[i][j] = P[ i - 1 ][ P[i - 1][j] ]; 

	int M;
	bool ok;
	int lowest;
	while ( Q-- ){
		scanf("%d", &M);
		lowest = -1;
		for ( int i=0; i < M; ++i ){
			scanf("%d", V + i);
			V[i]--;
			v = V[i];
			if ( L[v] > lowest ){
				lowest = L[v], u = v;
			}
		}
		if ( u != 0 ) u = P[0][u];
		ok = true;	
		for ( int i=0; i < M; ++i ){
			v = V[i];
			if ( v != 0 ) v = P[0][v];
			//printf("Testing %d - %d\n", u, v);
			if ( lca( u, v ) != v ) ok = false;
		}
		puts(ok? "YES":"NO");
	}
	return 0;
}

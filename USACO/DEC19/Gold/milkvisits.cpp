#include<cstdio>
#include<vector>
#include<cstdlib>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;
const int NLOG = 17;
int N;
vector<int> T[MAXN];
int C[MAXN];
int L[MAXN];
int P[MAXN][NLOG];
int log;
int Q[MAXN];
int res[MAXN];
vector<int> ans[MAXN];
vector<int> get[MAXN];
int cnt[MAXN];

void dfs( const int &u, const int &p ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			L[v] = L[u] + 1;
			P[v][0] = u;
			dfs(v, u);
		}
	}
}

void precalc(){
	for( log=0; (1<<log) < N; ++log );
	log--;

	for ( int i=0; i < N; ++i )
		for ( int j=1; j <= log; ++j )
			P[i][j] = -1;

	for ( int j=1; j <= log; ++j )
		for ( int i=0; i < N; ++i ){
			if ( P[i][j-1] != -1 )
				P[i][j] = P[ P[i][j-1] ][ j - 1 ];
		}
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);
	
	for ( int i=log; i >= 0; --i ){
		if ( (1 << i) <= L[v] - L[u] )
			v = P[v][i];
	}
	if ( u == v ) return u;
	
	for ( int j=log; j >= 0; --j ){
		if ( P[u][j] != -1 && P[u][j] != P[v][j] )
			u = P[u][j], v = P[v][j];
	}
	return P[u][0];
}

void answer_queries( const int &u, const int &p ){
	int idx;
	cnt[ C[u] ]++;
	// Get the values for the queries in which u is endvertex
	for ( int i=0; i < get[u].size(); ++i ){
		idx = get[u][i];
		res[ idx ] = max( res[ idx ], cnt[ Q[idx] ] );
	}
	int v;
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		answer_queries( v, u );
	}
	// Subtract the cnt of a color for the queries u is lca
	cnt[ C[u] ]--;
	for ( int i=0; i < ans[u].size(); ++i ){
		idx = ans[u][i];
		res[ idx ] -= cnt[ Q[idx] ];
	}
}

int main(){
	freopen ("milkvisits.in", "r", stdin);
	freopen ("milkvisits.out", "w", stdout);

	int M;
	int u, v, c, w;

	scanf("%d %d", &N, &M);

	for ( int i=0; i < N; ++i ){ 
		scanf("%d", C + i);
		C[i]--; // values from 0 ... N - 1
	}

	for (int i=1; i < N; ++i){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	// Compute the information for LCA computation
	L[0] = 0, P[0][0] = -1;
	dfs(0, -1);
	precalc();
	// Read the path ends and create the events
	for ( int i=0; i < M; ++i ){
		res[ i ] = -1;	// important for taking maximum later
		scanf("%d %d %d", &u, &v, Q + i);
		u--, v--, Q[i]--;
		// special case
		if ( u == v ){
			res[i] = ( C[i] == Q[i] )? 1:0;
			continue;
		}
		w = lca( u, v );
		ans[w].push_back( i );	// we need to get the answer of query i at vertex w
		if ( w != u ){
			get[u].push_back( i );	// we need to get the value of a color for query i	
		}
		if ( w != v ){
			get[v].push_back( i );	// we need to get the value of a color for query i
		} 
	}
	// Run a second dfs to compute the answers	
	fill( cnt, cnt + N, 0 );
	answer_queries( 0, -1 );
	for ( int i=0; i < M; ++i )
		if ( res[i] > 0 ) putchar('1');
		else putchar('0');
	puts("");
	return 0;
}

#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>
using namespace std;
const int MAXN = 100005;
const int MLOG = 19;

typedef pair<int,int> pii;

int N, M, Q;
vector<int> G[MAXN];
int dfsnum[MAXN];
int low[MAXN];
bool bridge[MAXN];
int L[MAXN];
int res;
int P[MLOG][MAXN];
int log;
set< pii > S[MAXN];

void insert( const int &u, const pii &e ){
	if ( S[u].empty() ){ 
		S[u].insert(e); return;
	}
	set<pii>::iterator a = S[u].lower_bound( pii( e.first , -INT_MAX ) );
}

void dfs( const int &u ){
	int v;
	low[u] = dfsnum[u] = num++;	
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			dfs( v );
			low[u] = min( low[u], low[v] ); 
			L[v] = L[u] + 1; 
			P[0][v] = u;
		}
		else {
			low[u] = min( low[u] , dfsnum[u] ); 
		}
	}
	if ( u != 1 && low[u] == dfsnum[u] ){
		bridge[u] = true;
		res++;
	}
}

int go_up( int u, int D ){
	for ( int i=log; i >= 0; --i )
		if ( D >= (1 << i) ){
			D -= ( 1 << i );
			u = P[i][u];
		}
	return u;
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap(u, v);
	v = go_up( v, L[v] - L[u] );
	if ( u == v ) return u;
	for ( int i=log; i >= 0 ; --i )
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	return P[0][u]; 
}

void process(){
	int u, v, w;
	fill( dfsnum, dfsnum + N, -1 );
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back( v );
		G[v].push_back( u );
	}
	L[1] = 0;
	P[0][1] = -1;
	res = 0;
	dfs( 0 );
	// LCA calculation
	for ( log=0; (1 << log) < N ; ++log );
	if ( log > 0 ) log--;
	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j ) 
			if ( P[i-1][j] != -1 )
				P[i][j] = P[ i - 1 ][ P[i-1][j] ];
	// Process the queries
	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		w = lca( u, v );
		if ( w != u ){ // Add event 
			insert( u , pii( i , L[w] ) );
		}
		if ( w != v ){ // Add event
			insert( v , pii( i , L[w] ) );	
		}
	}
}

int main(){	
	while ( scanf("%d %d", &N, &M) != EOF ){
		process();
	}
	return 0;
}

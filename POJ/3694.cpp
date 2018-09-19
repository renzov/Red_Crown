#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>
#include<climits>
using namespace std;
const int MAXN = 100005;
const int MLOG = 19;

typedef pair<int,int> pii;

int N, M, Q;
int num = 0;
vector<int> G[MAXN];
vector<int> T[MAXN];
int dfsnum[MAXN];
int low[MAXN];
bool bridge[MAXN];
int L[MAXN];
int rep[MAXN];
int res;
int P[MLOG][MAXN];
int log;
int cnt[1024];
set< pii > S[MAXN];


void insert( set<pii> &E, const pii &e ){
	set<pii>::iterator prev = E.lower_bound( pii( e.first , INT_MAX ) );
	set<pii>::iterator act =  prev--;
	set<pii>::iterator elim;
	if ( prev->second <= e.second ) return; // No need to insert
	if ( prev->first == e.first ){ // also prev.second > e.second
		--act;  // we begin eliminating from prev 
	}
	while ( act != E.end() && act->second >= e.second ){
		elim = act++;
		E.erase(elim);
	}
}

void dfs( const int &u ){
	int v;
	low[u] = dfsnum[u] = num++;	
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			T[u].push_back(v);
			dfs( v );
			low[u] = min( low[u], low[v] ); 
			L[v] = L[u] + 1; 
			P[0][v] = u;
		}
		else {
			low[u] = min( low[u] , dfsnum[u] ); 
		}
	}
	if ( u != 0 && low[u] == dfsnum[u] ){
		bridge[u] = true;
		res++;
	}
}

void solve( const int &u ){
	int v;
	int pu, pv;
	set<pii>::iterator it;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		solve( v );
		pu = rep[u], pv = rep[v];
		if ( S[pu].size() >= S[pv].size() ){
			it = S[pv].begin(); it++;
			for ( ; it != S[pv].end(); ++it )
				insert( S[pu], *it );
		}
		else {
			it = S[pu].begin(); it++;
			for ( ; it != S[pu].end(); ++it )
				insert( S[pv], *it );
			rep[u] = pv;
		}
	}
	if ( bridge[u] ){
		pu = rep[u];
		it = ++S[ pu ].begin();
		if ( it != S[ pu ].end() ){
			cnt[it->first]++;
		}
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

void process( const int &cases ){
	int u, v, w;
	fill( dfsnum, dfsnum + N, -1 );
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back( v );
		G[v].push_back( u );
	}
	L[0] = 0;
	P[0][0] = -1;
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
	fill( cnt, cnt + Q, 0 );
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		w = lca( u, v );
		if ( w != u ){ // Add event 
			insert( S[u] , pii( i , L[w] ) );
		}
		if ( w != v ){ // Add event
			insert( S[v] , pii( i , L[w] ) );	
		}
	}
	// Set representative
	for ( int i=0; i < N; ++i ) rep[i] = i;
	solve( 0 );
	// Print the result
	printf("Case: %d\n", cases );
	for ( int i=0; i < Q; ++i ){
		res -= cnt[i];
		printf("%d\n", res);
	}
}

void clean_up(){
	num = 0;
	for ( int i=0; i < N; ++i ){
		S[i].clear();
		G[i].clear();
		T[i].clear();
	}
}

int main(){	
	int cases = 0;
	while ( scanf("%d %d", &N, &M) != EOF ){
		cases++;
		for ( int i=0; i < N; ++i ) S[i].insert( pii( -INT_MAX, INT_MAX ) );
		process(cases);
		clean_up();
	}
	return 0;
}

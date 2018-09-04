#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int MLOG = 18;
int N; 
long long K;

int P[MLOG][MAXN];
long long S[MLOG][MAXN];
int W[MLOG][MAXN];
int L[MAXN];
int len[MAXN] = {0};
vector<int> G[MAXN];
int indeg[MAXN];
int par[MAXN];
bool inCycle[MAXN];
int log;

void mark_cycles(){
	queue<int> q;
	fill(  inCycle, inCycle + N, true );
	for (int i=0; i < N; ++i)
		if ( indeg[i] == 0 ){
			q.push(i);
			inCycle[i] = false;
		}
	int u, v;
	while ( !q.empty() ){
		v = q.front();
		q.pop();
		u = P[0][v];
		indeg[u]--;
		if ( indeg[u] == 0 ){
			q.push(u);
			inCycle[u] = false;
		}
	}
}

void dfs( const int &u, const int &p ){
	int v;
	if ( u != p ) par[u] = p;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( !inCycle[v] ){
			L[v] = L[u] + 1;
			dfs(v, p);
		}
	}
}

void cycle_len( const int &u, const int &p, int l ){
	if ( u == p ){
		len[p] = len[u] = l; 
	}
	else {
		cycle_len( P[0][u], p, l + 1 );
		len[u] = len[ P[0][u] ];
	}
}

int main(){
	int u, v;
	scanf("%d %lld", &N, &K);
	for ( v=0; v < N; ++v ){
		scanf("%d", &u);
		G[ u ].push_back( v );
		P[0][v] = u;
		indeg[ u ]++;
	}
	mark_cycles();
	for ( int i=0; i < N; ++i )
		if ( inCycle[i] ){ 
			L[i] = 0;
			dfs( i , i );
		}
	for ( int i=0; i < N; ++i ){
		scanf("%d", &S[0][i]);
		W[0][i] = S[0][i];
	}
	for ( log = 0; (1<<log) < N; ++log );
	if (log > 0) log--;
	// Calculate the values of P
	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j ){
			P[i][j] = P[ i-1 ][ P[i-1][j] ];
			S[i][j] = S[i-1][j] + S[ i-1 ][ P[i-1][j] ];
			W[i][j] = min( W[i-1][j] , W[i-1][ P[i-1][j] ] );
		}
	// Calculate the length of each cycle
	for ( int i=0; i < N; ++i )
		if ( inCycle[i] && len[i] == 0 ){
			if ( P[0][i] == i ){ // Special case
				len[i] = 1;
			}
			else {
				cycle_len( P[0][i] , i , 1 );
			}
		}
	// Ready to answer the queries
	return 0;
}


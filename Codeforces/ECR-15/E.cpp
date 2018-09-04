#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 100005;
const int MLOG = 19;
int N; 
long long K;

int P[MLOG][MAXN];
long long S[MLOG][MAXN];
int W[MLOG][MAXN];
int L[MAXN];
int len[MAXN] = {0};
long long sum[MAXN];
int mini[MAXN];
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

void cycle_len( const int &u, const int &p, const int &l, const long long &s, const int &m ){
	if ( u == p ){
		len[p] = len[u] = l;
		sum[p] = sum[u] = s;
		mini[p] = mini[u] = m;
	}
	else {
		cycle_len( P[0][u], p, l + 1 , s + S[0][u] , min( m, W[0][u] ) );
		len[u] = len[ P[0][u] ];
		sum[u] = sum[ P[0][u] ];
		mini[u] = sum[ P[0][u] ];
	}
}

long long get_sum( int u , long long D ){
	long long res = 0;
	for ( int i=log; D > 0 && i >= 0; --i ){
		if ( (1 << i) <= D ){
			res += S[i][u];
			u = P[i][u];
			D -= ( 1 << i );
		}
	}
	return res;
}

int get_mini( int u, long long D ){
	int res = INT_MAX;
	for ( int i=log; i >= 0; --i ){
		if ( (1 << i) <= D ){
			res = min( res, W[i][u] );
			u = P[i][u];
			D -= ( 1 << i );
		}
	}
	return res;
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
		scanf("%lld", &S[0][i]);
		W[0][i] = S[0][i];
	}
	for ( log = 0; (1<<log) < N; ++log );
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
				sum[i] = S[0][i];
				mini[i] = S[0][i];
			}
			else {
				cycle_len( P[0][i] , i , 1 , S[0][i], S[0][i] );
			}
		}
	// Ready to answer the queries
	for ( v=0; v < N; ++v ){
		// Parent of v in the cycle
		u = par[v];
		if ( (L[v] - L[u]) >= K ){
			printf("%lld %d\n", get_sum(v, K), get_mini(v, K));	
		}
		else {
			long long sum_res = get_sum( v, L[v] - L[u] );
			int mini_res = get_mini( v , L[v] - L[u] );
			long long full = ( K - (L[v] - L[u]) ) / len[u];
			long long left = ( K - (L[v] - L[u]) ) % len[u];
			sum_res += ( full * sum[u] );
			if ( full > 0 ) mini_res = min( mini_res, mini[u] );
			if ( left > 0 ){ 
				sum_res += get_sum( u , left );
				mini_res = min( mini_res , get_mini( v, left ) );
			}
			printf("%lld %d\n", sum_res, mini_res);
		}
	}
	return 0;
}


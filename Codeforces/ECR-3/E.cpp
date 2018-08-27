#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> edge;

const int MAXN = 200005;
const int MLOG = 19;

int N;
int M;
vector<int> T[MAXN];
vector<int> C[MAXN];
edge E[MAXN];
int W[MAXN];
int ord[MAXN];
bool inT[MAXN] = {0};
int f[MAXN];
int L[MAXN];
int P[MLOG][MAXN];
int ME[MLOG][MAXN];
int log;

inline int find_set( const int &x ){
	return ( x == f[x] )? x:( f[x] = find_set( f[x] ) );
}

bool cmp( const int &i, const int &j ){
	return W[i] < W[j];
}

void dfs( const int &u, const int &p ){
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){	
		v = T[u][i];
		if ( v == p ) continue;
		L[v] = L[u] + 1;
		ME[0][v] = C[u][i];
		P[0][v] = u;
		dfs( v, u );
	}
}

int go_up( int u, int D ){
	for ( int i=log; D >= 0 && i >= 0 ; --i ){
		if ( (1<<i) <= D ){
			D -= ( 1<<i );
			u = P[i][u];
		}
	}
	return u;
}

int get_max( int u, int D ){
	int res = 0;
	for ( int i=log; D >= 0 && i >= 0; --i ){
		if ( (1<<i) <= D ){
			D -= (1 << i);
			res = max( res , ME[i][u] );
			u = P[i][u];
		}
	}
	return res;
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap( u , v );
	v = go_up( v, L[v] - L[u] );
	if ( u == v ) return u;
	for ( int i=log; i >= 0; --i )
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	return P[0][u];
}

int main(){
	scanf("%d %d", &N, &M);
	int u, v, w;
	int l, m;
	int idx;
	long long cost = 0;
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		E[i].first = u, E[i].second = v;
		W[i] = w;
		ord[i] = i;
	}
	// Find a min spanning tree
	sort( ord, ord + M, cmp );
	for ( int i=0; i < N; ++i ) f[i] = i;
	for ( int i=0; i < M; ++i ){
		idx = ord[i];
		u = E[ idx ].first;
		v = E[ idx ].second;
		u = find_set( u );
		v = find_set( v );
		if ( u != v ){	// Join the sets and mark the edge
			f[v] = u;
			inT[i] = true;
			cost += W[i];
			T[u].push_back(v); C[u].push_back( W[i] );
			T[v].push_back(u); C[v].push_back( W[i] );
		}
	}
	// Preprocess T for LCA queries
	for ( log = 0; (1<<log) <= N; ++log );
	log--;
	L[0] = 0;
	P[0][0] = -1;
	ME[0][0] = 0;
	dfs( 0 , -1 );
	for ( int i=1; i <= log; ++i )
		for ( int j=0; j < N; ++j )
			if ( P[i-1][j] != -1 ){
				P[ i ][ j ] = P[ i-1 ][ P[i-1][j] ];
				ME[i][j] = max( ME[i-1][j] , ME[i-1][ P[i-1][j] ] );
			}
			else {
				P[i][j] = -1;
				ME[i][j] = ME[i-1][j];
			}
	
	for ( int i=0; i < M; ++i ){
		if ( inT[i] ) printf("%lld\n", cost);
		else {
			u = E[i].first;
			v = E[i].second;
			w = W[i];
			l = lca( u , v );
			m = max( get_max( u, L[u] - L[l] ), get_max( v, L[v] - L[l] ) );
			printf("%lld\n", cost + w - m);
		}
	}
	return 0;
}


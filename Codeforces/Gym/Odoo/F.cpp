#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 200005; 

int N, Q, K;
int A[MAXN];
int res[MAXN];
long long seg[4*MAXN];

vector<int> T[MAXN];
vector<int> Y[MAXN];
vector<int> X[MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }
inline bool div( const long long &x ){ return (x % K) == 0; }

void build( const int &node, const int &L, const int &R ){
	seg[node] = 1LL % K;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
}

void update( const int &node, const int &L, const int &R, const int &p, const int &val ){
	if ( L == R ){
		seg[node] = val;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p > M ) update( right(node), M + 1, R, p, val );
	else update( left(node), L, M, p, val );
	seg[node] = ( seg[left(node)] * seg[right(node)] ) % K;
}

int query( const int &node, const int &L, const int &R, const long long &val ){
	if ( !div( seg[node] * val ) ) return -2;	// not possible to make it multiple of K
	if ( L == R ) return L;
	int M = ( L + R ) >> 1;
	if ( div( seg[left(node)] * val ) ) 
		return query( left(node), L, M, val );
	return query( right(node), M + 1, R, (val * seg[ left(node) ]) % K ); 
}

void dfs( const int &u ){
	int x, y, v;
	// Apply all the changes
	for ( int i=0; i < (int)Y[u].size(); ++i ){
		y = Y[u][i];
		x = X[u][i];
		update( 1, 0, Q - 1, y, x % K );
	}
	// Get the answer for vertex u
	if ( A[u] % K )
		res[u] = query( 1, 0, Q - 1, A[u] % K ) + 1;
	else
		res[u] = 0;
	
	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		dfs( v );
	}	
	// Undo the changes
	for ( int i=0; i < (int)Y[u].size(); ++i ){
		y = Y[u][i];
		update( 1, 0, Q - 1, y, 1 % K );
	}
}

int main(){
	int p;
	int u, w;

	scanf("%d %d %d", &N, &K, &Q);

	for ( int i = 0; i < N; ++i )
		scanf("%d", A + i);
	
	for ( int i = 1; i < N; ++i ){
		scanf("%d", &p);
		--p;
		T[p].push_back(i);
	}

	build( 1, 0, Q - 1 );
	
	for ( int i = 0; i < Q; ++i ){
		scanf("%d %d", &u, &w);
		u--;
		Y[u].push_back( i );
		X[u].push_back( w );
	}

	dfs( 0 );
	// Print the answers
	printf("%d", res[0] );
	for ( int i = 1; i < N; ++i )
		printf(" %d", res[i] );
	puts("");
	return 0;
}

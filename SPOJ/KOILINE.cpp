#include<cstdio>
#include<climits>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int N;
int S[MAXN];
int res[MAXN];
priority_queue<int> H;

int seg[4*MAXN];
int lazy[4*MAXN];

inline int left(const int &x){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){ seg[node] = S[L]; return; }
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	seg[node] = min( seg[left(node)], seg[right(node)] );
}

void propagate( const int &node, const int &L, const int &M, const int &R ){
	int l = left(node);
	int r = right(node);
	seg[l] = (seg[l] < INT_MAX)? (seg[l] - lazy[node]):INT_MAX;
	seg[r] = (seg[r] < INT_MAX)? (seg[r] - lazy[node]):INT_MAX;
	if ( L < M ) lazy[l] += lazy[node];
	if ( M + 1 < R ) lazy[r] += lazy[node];
	lazy[node] = 0;
}

int query( const int &node, const int &L, const int &R ){
	if ( L == R ) return L;
	int M = ( L + R ) >> 1;
	if ( lazy[node] > 0 ) propagate( node, L, M, R );
	if ( seg[ right(node) ] == 0 ) return query( right(node), M + 1, R );
	return query( left(node), L, M );
}

void eliminate( const int &node, const int &L, const int &R, const int &p ){
	if ( L == R ){
		seg[node] = INT_MAX;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( lazy[node] > 0 ) propagate( node, L, M, R );	
	if ( p <= M ) eliminate( left(node), L, M, p );
	else eliminate( right(node), M + 1, R, p );
	seg[ node ] = min( seg[ left(node) ], seg[ right(node) ] );
}

void update( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R ){
		seg[node]--;
		lazy[node]++;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( lazy[node] > 0 ) propagate( node, L, M, R );	
	if ( r <= M ) update( left(node), L, M, l, r );
	else if ( l > M ) update( right(node), M + 1, R, l, r );
	else {
		update( left(node), L, M, l, M );
		update( right(node), M + 1, R, M + 1, r );
	}
	seg[ node ] = min( seg[ left(node) ], seg[ right(node) ] );
}

int main(){
	int h;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &h);
		H.push(h);
	}
	for ( int i=0; i < N; ++i ){
		scanf("%d", S + i);
		S[i] = i - S[i];
	}
	// build the min segtree
	build( 1, 0, N - 1 );
	int idx;
	for ( int i=0; i < N; ++i ){
		idx = query( 1, 0, N - 1 );
		res[idx] = H.top();
		H.pop();
		if ( idx + 1 < N )
			update( 1, 0, N - 1, idx + 1, N - 1 );
		eliminate( 1, 0, N - 1, idx );
	}
	for ( int i=0; i < N; ++i )
		printf("%d\n", res[i]);
	return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

int last[MAXN] = {0};

struct SegTree { 
	int seg[4*MAXN];

	inline int left( const int &x ){
		return x << 1;
	}

	inline int right( const int &x ){
		return ( x << 1 ) | 1;
	}

	void build( const int &node, const int &L, const int &R ){
		seg[node] = 0;
		if ( L == R ) return;
		int M = ( L  + R ) >> 1;
		build( left(node), L, M );
		build( right(node), M + 1, R );
	}

	void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
		seg[node] += v;
		if ( L == R ) return;
		int M = ( L + R ) >> 1;
		if ( p > M ) update( right(node), M + 1, R, p, v );
		else update( left(node), L, M, p, v );
	}

	int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
		if ( l == L && r == R ) return seg[node];
		int M = ( L + R ) >> 1;
		if ( r <= M ) return query( left(node), L, M, l, r );
		if ( l > M ) return  query( right(node), M + 1, R, l, r );
		return query( left(node), L, M, l, M ) + query( right(node), M + 1, R, M + 1, r );
	}
};

SegTree open, closed;

int main(){

	int N;
	int L, R;
	int l, r;
	scanf("%d", &N);

	open.build( 1, 0, 100000 );
	closed.build( 1, 0, 100000 );
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &L, &R);
		int a = open.query( 1, 0, 100000, 0, L - 1 );
		int b = closed.query( 1, 0, 100000, 0, L );
		l = a - b;
		r = open.query( 1, 0, 100000, 0, R - 1 ) - closed.query( 1, 0, 100000, 0, R );		
		l -= last[ L ];
		r -= last[ R ];
		printf("%d\n", l + r );
		last[L] += l, last[R] += r;
		open.update( 1, 0, 100000, L, 1 );
		closed.update( 1, 0, 100000, R, 1 );
	}
	return 0;
}


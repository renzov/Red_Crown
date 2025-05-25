#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 200005;
int P[MAXN];
int pos[MAXN];
int seg[4*MAXN];	// min segtree over pos[]
long long res = 0;
int N;

inline int left( const int &x ){ return x << 1; } 
inline int right( const int &x ){ return ( x << 1 ) | 1; }

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		seg[node] = pos[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	seg[node] = min( seg[ left(node) ], seg[ right(node) ] );
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return min( query( left(node), L, M, l, M ), query( right(node), M + 1, R, M + 1, r ) );
}

void solve( const int &u, const int &lvl, const int &L, const int &R ){
	//printf("root = %d - [ %d, %d ]\n", u, L, R);
	res += lvl;
	int v;
	if ( L < u ){	// reconstruct left subtree
		v = query( 1, 0, N - 1, L, u - 1 );
		v = P[v];
		//printf("left subtree root = %d\n", v);
		solve( v, lvl + 1, L, u - 1 );
	}
	if ( u < R ){	// reconstruct right subtree
		v = query( 1, 0, N - 1, u + 1, R );
		v = P[v];	// get the real element
		//printf("right subtree root = %d\n", v);		
		solve( v, lvl + 1, u + 1, R );
	}
}

int main(){
	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", P + i );
		P[i]--;
		pos[ P[i] ] = i;
	}
	build( 1, 0, N - 1 );	
	solve( P[0], 0, 0, N - 1 );
	printf("%lld\n", res);
	return 0;
}

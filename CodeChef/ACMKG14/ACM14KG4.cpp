#include<cstdio>
using namespace std;

const int MAXN = 100005;
int seg[4*5*MAXN];	// Length is 1 ... 5*N (then segtree is 4*Length) 
int P[MAXN];
int res[MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	seg[node] = R - L + 1;
	int M = ( L + R ) >> 1;
	if ( L != R ){
		build( left(node), L, M );
		build( right(node), M + 1, R );
	}
}

void mark( const int &node, const int &L, const int &R, const int &p ){
	if ( L == R ){	
		seg[node] = 0;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p <= M ) mark( left(node), L, M, p );
	else mark( right(node), M + 1, R, p );
	seg[node] = seg[left(node)] + seg[right(node)];
}

int query( int node, int L, int R, const int &l, const int &r ){
	int M;
	if ( l == L && r == R ){
		if ( seg[node] == 0 ) return -1;
		while ( L < R ){
			M = ( L + R ) >> 1;	
			if ( seg[left(node)] > 0 ){
				R = M;
				node = left(node);
			}
			else {
				L = M + 1;
				node = right(node);
			}
		}
		return L;
	}
	
	M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	
	int leftAns = query( left(node), L, M, l, M );
	if ( leftAns != -1 ) return leftAns;
	return query( right(node), M + 1, R, M + 1, r );
}

void process(){
	int N;
	scanf("%d", &N);
	build(1, 1, 5*N);
	// Mark invalid positions
	mark( 1, 1, 5*N, 5*N );	
	mark( 1, 1, 5*N, 5*N - 1 );

	for ( int i=0; i < N; ++i )
		scanf("%d", P + i );
	

	for ( int i=N - 1; i >= 0; --i ){
		res[i] = query( 1, 1, 5*N, P[i], 5*N );
		if ( res[i] == -1 ){
			res[i] = query( 1, 1, 5*N, 1, 5*N );
		}
		for ( int j=res[i] - 2; j <= res[i] + 2; ++j ){
			if ( j >= 1 && j <= 5*N )
				mark( 1, 1, 5*N, j );
		}
	}

	for ( int i=0; i < N; ++i ){
		if (i) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

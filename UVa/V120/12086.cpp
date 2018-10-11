#include<cstdio>
using namespace std;
const int MAXN = 200005;
int A[MAXN];
int seg[4*MAXN];
int N;

inline int left(const int &x){ return x << 1; }
inline int right(const int &x){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	if ( L==R ){
		seg[node] = A[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	seg[node] = seg[ left(node) ] + seg[ right(node) ];
}

void update( const int &node, const int &L, const int &R, const int &pos, const int &val ){
	if ( L == R ){ seg[node] = val; return; }
	int M = ( L + R ) >> 1;
	if ( pos <= M ) update( left(node), L, M, pos, val );
	else update( right(node), M + 1, R, pos, val );
	seg[node] = seg[left(node)] + seg[right(node)];
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R ) return seg[node];
	int M = (L + R) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return query( left(node), L, M, l, M ) + query( right(node), M + 1, R, M + 1, r );
}

void process(){
	char op[5];
	int x, y;
	for ( int i=0; i < N; ++i ) scanf("%d", A + i);
	build( 1, 0, N - 1 );
	while ( scanf("%s", op) && op[0] != 'E' ){
		scanf("%d %d", &x, &y);
		x--;
		if ( op[0] == 'M' ){
			y--;
			printf("%d\n", query( 1, 0, N - 1, x, y ));
		}	
		else {
			update( 1, 0, N - 1, x, y );	
		}
	}
}

int main(){
	int cases = 0;
	while ( scanf("%d", &N) && N ){
		if ( cases ) puts("");
		cases++;
		printf("Case %d:\n", cases);
		process();
	}
	return 0;
}

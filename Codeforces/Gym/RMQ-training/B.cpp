#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;

const int MAXN = 100000;

int segMin[4*(MAXN + 5)];
int segMax[4*(MAXN + 5)];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		segMin[node] = segMax[node] = (int)(1LL * L * L % 12345) + (int)(1LL * L * L * L % 23456);
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	segMin[node] = min( segMin[left(node)], segMin[right(node)] );
	segMax[node] = max( segMax[left(node)], segMax[right(node)] );
}

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){
		segMin[node] = segMax[node] = v;
		return;
	}

	int M = (L + R) >> 1;
	if ( p > M ) update( right(node), M + 1, R, p, v );
	else update( left(node), L, M, p, v );

	segMin[node] = min( segMin[left(node)], segMin[right(node)] );
	segMax[node] = max( segMax[left(node)], segMax[right(node)] );
}

pii query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( l == L && R == r )
		return pii( segMax[node], segMin[node] );
	
	int M = (L + R) >> 1;

	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );

	pii lp = query( left(node), L, M, l, M );
	pii rp = query( right(node), M + 1, R, M + 1, r );
	
	return pii( max( lp.first, rp.first ), min( lp.second, rp.second ) );
}

int main(){
	freopen( "rvq.in", "r", stdin );
	freopen( "rvq.out", "w", stdout );
	// build the segment trees
	build( 1, 1, MAXN );
	
	int K, X, Y;
	pii res;
	
	scanf("%d", &K);
	while ( K-- ){
		scanf("%d %d", &X, &Y);
		if ( X > 0 ){
			res = query( 1, 1, MAXN, X, Y );
			printf("%d\n", res.first - res.second);
		}
		else {
			X *= -1;
			update( 1, 1, MAXN, X, Y );
		}
	}
	return 0;
}

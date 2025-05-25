#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<long long, long long> pii;

const int MAXN = 200005;
int A[MAXN];

long long minSeg[4*MAXN];
long long sumSeg[4*MAXN];
long long lazy[4*MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void join( const int &node ){
	sumSeg[node] = sumSeg[left(node)] + sumSeg[right(node)];
	minSeg[node] = min( minSeg[left(node)], minSeg[right(node)] );
}

void build( const int &node, const int &L, const int &R ){
	if ( L == R ){
		minSeg[node] = sumSeg[node] = A[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L , M );
	build( right(node), M + 1, R );
	join( node );
}

void lazy_update(const int &node, const int &L, const int &R, const long long &D){
	sumSeg[node] += (( R - L  + 1 ) * D);
	minSeg[node] += D;
	lazy[node] += D;
}

void update( const int &node, const int &L, const int &R, const int &l, const int &r, const long long &D ){
	if ( L == l && r == R ){
		lazy_update( node, L, R, D );
		return;
	}
	int M = ( L + R ) >> 1;	
	if ( lazy[node] ){
		lazy_update( left(node), L, M, lazy[node] );
		lazy_update( right(node), M + 1, R, lazy[node] );
		lazy[node] = 0;
	}
	if ( r <= M ){
		update( left(node), L, M, l, r, D );
	}
	else if ( l > M ){	
		update( right(node), M + 1, R, l, r, D );
	}
	else {
		update( left(node), L, M, l, M, D );
		update( right(node), M + 1, R, M + 1, r, D );
	}
	join(node);
}

pii query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R )
		return pii( sumSeg[node], minSeg[node] );

	int M = (L + R) >> 1;
	if ( lazy[node] ){
		lazy_update( left(node), L, M, lazy[node] );
		lazy_update( right(node), M + 1, R, lazy[node] );
		lazy[node] = 0;
	}
	
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	pii lans = query( left(node), L, M, l, M );
	pii rans = query( right(node), M + 1, R, M + 1, r );
	return pii( lans.first + rans.first, min( lans.second, rans.second ) );
}

int main(){
	freopen("haybales.in", "r", stdin );
	freopen("haybales.out", "w", stdout );

	int N, Q;
	char op;
	int L, R;

	scanf("%d %d", &N, &Q);
	for ( int i = 0; i < N; ++i )
		scanf("%d", A + i );
	
	build(1, 0, N - 1);
	while ( Q-- ){
		scanf(" %c %d %d", &op, &L, &R);
		L--, R--;
		if ( op != 'P' ){
			pii ans = query( 1, 0, N - 1, L, R );
			printf("%lld\n", op == 'S'? ans.first:ans.second );
		}
		else {
			long long delta;
			scanf("%lld", &delta);
			update( 1, 0, N - 1, L, R, delta );
		}
	}
	return 0;
}

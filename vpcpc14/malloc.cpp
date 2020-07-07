#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 300005;

int longest[4*MAXN];
int prefix[4*MAXN];
int suffix[4*MAXN];
int used[4*MAXN];
int lazy[4*MAXN];

inline int left(const int &x){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

inline int empty( const int &node, const int &size ){
	longest[node] = prefix[node] = suffix[node] = size;
	used[node] = 0;
}

inline int full( const int &node, const int &size ){
	longest[node] = prefix[node] = suffix[node] = 0;
	used[node] = size; 
}

void build( const int &node, const int &L, const int &R ){
	empty( node, R - L + 1 );
	if ( L==R ) return;
	int M = (L + R) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
}

void propagate( const int &node, const int &L, const int &M, const int &R ){
	int l = left(node), r = right(node);
	if ( lazy[node] < 0 ){
		empty( l, M - L + 1 );
		empty( r, R - M );
	}
	else {
		full( l, M - L + 1 );
		full( r, R - M );
	}
	lazy[l] = lazy[r] = lazy[node];
	lazy[node] = 0;
}

int query1( const int &node, const int &L, const int &R, const int &size ){
	if ( longest[node] < size ) return -1;
	if ( size == (R - L + 1) )	return L;
	int M = (L + R) >> 1;
	if ( lazy[node] ) propagate( node, L, M, R );
	if ( longest[left(node)] >= size ) return query1( left(node), L, M, size );
	if ( suffix[left(node)] + prefix[right(node)] >= size ) return M - suffix[ left(node) ] + 1;
	return query1( right(node), M + 1, R, size );
}

int query2( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && R == r ) return used[node];
	int M = ( L + R ) >> 1;
	if ( lazy[node] ) propagate( node, L, M, R );
	if ( r <= M ) return query2( left(node), L, M, l, r );
	if ( l > M ) return query2( right(node), M + 1, R, l, r);
	return query2( left(node), L, M, l, M ) + query2( right(node), M + 1, R, M + 1, r );
}

void pushup( const int &node, const int &L, const int &M, const int &R ){
	used[node] = used[left(node)] + used[right(node)];
	longest[node] = max( suffix[left(node)] + prefix[ right(node) ], max( longest[left(node)], longest[right(node)] ) );
	prefix[node] = prefix[left(node)] == (M - L + 1)? ( M - L + 1 + prefix[right(node)] ):( prefix[left(node)] );
	suffix[node] = suffix[right(node)] == (R - M)? ( R - M + suffix[left(node)] ):( suffix[right(node)] );
}

void update2( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){
		if ( v < 0 ) empty( node, 1 );
		else full(node, 1);
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p <= M ) update2( left(node), L, M, p, v );
	else update2( right(node), M + 1, R, p, v );
	pushup( node, L, M, R );
}

void update( const int &node, const int &L, const int &R, const int &l, const int &r, const int &v ){
	if ( l == L && r == R ){
		if ( v < 0 ) empty( node, R - L + 1 );
		else full( node, R - L + 1 );
		lazy[node] = v;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( lazy[node] ) propagate( node, L, M, R );
	if ( r <= M ) update( left(node), L, M, l , r, v );
	else if ( l > M ) update( right(node), M + 1, R, l, r, v );
	else {
		update( left(node), L, M, l, M, v );
		update( right(node), M + 1, R, M + 1, r, v );
	}
	pushup(node, L, M, R);
}


int main(){
	int N, Q;
	scanf("%d %d", &N, &Q);
	build( 1, 0, N - 1 );
	int l, x, type;
	while ( Q-- ){
		scanf("%d", &type);
		if ( type == 1 ){
			scanf("%d", &l);
			x = query1( 1, 0, N - 1, l );
			if ( x != -1 )
				update( 1, 0, N - 1, x, x + l - 1, 1 );
			printf("%d\n", x);
		}
		else {
			scanf("%d %d", &x, &l);
			printf("%d\n", query2( 1, 0, N - 1, x, x + l - 1 ));
			update( 1, 0, N - 1, x, x + l - 1, -1 );
		}
	}
	return 0;
}

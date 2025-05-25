#include<cstdio>
using namespace std;

const int MAXN = 100005;

long long seg[4*MAXN];
long long lazy[4*MAXN];
bool mark[4*MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void push( const int &node, const int &L, const int &R ){
	int M = (L + R) >> 1;

	seg[left(node)] = lazy[node] * ( M - L + 1 );
	lazy[left(node)] = lazy[node];
	mark[left(node)] = true;

	seg[right(node)] = lazy[node] * ( R - M );
	lazy[right(node)] = lazy[node];
	mark[right(node)] = true;

	lazy[node] = 0;
	mark[node] = false;
}

void update( const int &node, const int &L, const int &R, const int &l, const int &r, const int &x ){
	if ( l == L && r == R ){
		seg[node] = 1LL * (R - L + 1) * x;
		lazy[node] = x;
		mark[node] = true;
		return;
	}

	if ( mark[node] ) push(node, L, R);
	
	int M = (L + R) >> 1;
	if ( r <= M ) update( left(node), L, M, l, r, x );
	else if ( l > M ) update( right(node), M + 1, R, l, r, x );
	else {
		update( left(node), L, M, l, M, x );
		update( right(node), M + 1, R, M + 1, r, x );
	}
	seg[node] = seg[left(node)] + seg[right(node)];
}

long long query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R ) return seg[node];
	if ( mark[node] ) push(node, L, R);

	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return query( left(node), L, M, l, M ) + query( right(node), M + 1, R, M + 1, r );
}

int main(){
	int N, Q;
	int x, l, r;
	char op;

	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);

	scanf("%d %d", &N, &Q);
	while ( Q-- ){
		scanf(" %c %d %d", &op, &l, &r);
		l--, r--;
		if ( op == 'A' ){
			scanf("%d", &x);
			update( 1, 0, N - 1, l, r, x );
		}
		else {
			printf("%lld\n", query( 1, 0, N - 1, l, r ) );
		}
	}
	return 0;
}

#include<cstdio>
using namespace std;
const int MAXSIZE = 100005;

int l[MAXSIZE];
int r[MAXSIZE];
int d[MAXSIZE];


inline int left(const int &x){ return x << 1; }
inline int right(const int &x){ return (x<<1)|1; }

struct segtree {
	long long A[4*MAXSIZE];
	long long lazy[4*MAXSIZE];

	void propagate( const int &node, const int &L, const int &M, const int &R ){
		long long v = lazy[node];
		lazy[ left(node) ] += v;
		lazy[ right(node) ] += v;
		A[left(node)] += v * (M - L + 1);
		A[right(node)] += v * ( R - M );
		lazy[node] = 0;
	}

	void add( const int &node, const int &L, const int &R, const int &l, const int &r, const long long &v ){
		if ( l == L && r == R ){
			if ( l != r ) lazy[node] += v;
			A[node] += (v * (R - L + 1));
			return;
		}
		int M = ( L + R ) >> 1;
		if ( lazy[node] ) propagate(node, L, M, R);
		if ( r <= M ) add( left(node), L, M, l, r, v );
		else if ( l > M ) add(right(node), M + 1, R, l, r, v );
		else {
			add(left(node), L, M, l, M, v );
			add(right(node), M + 1, R, M + 1, r, v );
		}
		A[node] += ( r - l + 1 )*v;
	}

	long long query( const int &node, const int &L, const int &R, const int &l, const int &r ){
		if ( l == L && r == R ) return A[node];
		int M = ( L + R ) >> 1;
		if (lazy[node]) propagate(node, L, M, R);
		if ( r <= M ) return query(left(node), L, M, l, r);
		if ( l > M ) return query(right(node), M + 1, R, l, r);
		return query(left(node), L, M, l, M) + query(right(node), M + 1, R, M + 1, r);
	}
	
} oper, array;

int main(){

	int N, M, K;
	int x, y;
	long long v;
	scanf("%d %d %d", &N, &M, &K);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &x);
		array.add( 1, 0, N - 1, i, i, (long long)x );
	}
	for ( int i=0; i < M; ++i ){ 
		scanf("%d %d %d", l + i, r + i, d + i); 
		l[i]--, r[i]--;
	}
	for ( int i=0; i < K; ++i ){
		scanf("%d %d", &x, &y);
		oper.add(1, 0, M - 1, x - 1, y - 1, 1LL );
	}
	for ( int i=0; i < M; ++i ){
		v = oper.query(1, 0, M - 1, i , i);
		if ( v > 0 ) array.add( 1, 0, N - 1, l[i], r[i], d[i]*v );
	}
	for ( int i=0; i < N; ++i ){
		v = array.query( 1, 0, N - 1, i, i );
		if (i) putchar(' ');
		printf("%I64d", v);
	}
	puts("");
	return 0;
}

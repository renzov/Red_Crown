#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
const int MAXN = 30005;

int N, Q;
int res[MAXN];
int f[MAXN] = {0};
int A[MAXN];
int B[MAXN];
int tree[MAXN];
int size;

struct Query {
	int l, r;
	int id;
	Query(){}
	bool operator<(const Query &other) const {
		int b1 = l/size;
		int b2 = other.l/size;
		if ( b1 != b2 ) return b1 < b2;
		return r < other.r;
	}
};

Query q[MAXN];

void update( int p, int v ){
	for( ; p < MAXN; tree[p] += v, p += p & -p) ;
}

int sum( int p ){
	int S = 0;
	for(; p > 0 ; S += tree[p], p -= p & -p) ;
	return S;
}

inline int sum( const int &a, const int &b ){
	return sum( b ) - sum( a - 1 );
}

int getAns(){
	if ( sum( N, N ) >= N ) return N;
	int L = 1, R = N;
	int M;
	while ( R - L > 1 ){
		M = ( L + R ) >> 1;
		if ( sum( M, N ) >= M )
			L = M;
		else 
			R = M;
	}
	return L;
}

void add( const int &x ){
	int idx = A[x];
	if ( f[idx] > 0 )
		update( f[idx], -1 );
	f[idx]++;
	update( f[idx], 1 );
}

void remove( const int &x ){
	int idx = A[x];
	assert( f[idx] > 0 );
	update( f[idx], -1 );
	f[idx]--;
	if ( f[idx] > 0 )
		update( f[idx], 1 );
}

int main(){
	int M;
	scanf("%d %d", &N, &Q);
	size = (int) sqrt(N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i );
		B[i] = A[i];
	}
	sort( B, B + N );
	M = unique( B, B + N ) - B;
	for ( int i=0; i < N; ++i ){
		A[i] = lower_bound(B, B + M, A[i]) - B;
	}
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].l--, q[i].r--;
		q[i].id = i;
	}
	sort( q, q + Q );

	int l = 0, r = -1;
	// Mo algorithm
	for ( int i=0; i < Q; ++i ){
		while ( l > q[i].l ){
			l--;
			add(l);
		}
		while ( r < q[i].r ){
			r++;
			add(r);
		}
		while ( l < q[i].l ){
			remove(l);
			l++;
		}
		while ( r > q[i].r ){
			remove(r);
			r--;
		}
		res[ q[i].id ] = getAns();
	}
	for ( int i=0; i < Q; ++i )
		printf("%d\n", res[i]);
	return 0;
}

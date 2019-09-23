#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;
int N;
pii A[MAXN];
int seg[4*MAXN];

inline int left(const int &x){ return x<<1; }
inline int right(const int &x){ return (x<<1)|1; }

bool cmp( const pii &a, const pii &b ){
	return ( a.first != b.first )? (a.first > b.first):(a.second > b.second);
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && R == r ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l , r );
	return 	query( left(node), L, M, l, M ) + 
			query( right(node), M + 1, R, M + 1, r );
}

void update( const int &node, const int &L, const int &R, const int &p ){
	if ( L == R ){ seg[node]++; return; }
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( left(node), L, M, p );
	else update( right(node), M + 1, R, p );
	seg[node]++;
}

int main(){
	int X;
	int v;
	int S = 0;

	scanf("%d %d", &N, &X);

	A[0] = pii( 0 , 0 );
	for ( int i=1;  i <= N; ++i ){
		scanf("%d", &v);
		if ( v < X ) S--;
		else S++;
		A[i] = pii( S, i );
	}

	sort( A, A + (N + 1), cmp );
	long long res = 0;
	int idx;
	for ( int i=0; i <= N; ++i ){
		idx = A[i].second;
		if ( idx < N )
			res += query( 1, 0, N, idx + 1, N );
		update( 1, 0, N, idx );
	}
	printf("%lld\n", res);
	return 0;
}

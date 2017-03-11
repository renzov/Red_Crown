#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 100005; 
const int MOD = 1000000009;
int N;
int sum[MAXN];
int ord[MAXN];
int idx[MAXN];
int seg[4*MAXN];

bool cmp( const int &a, const int &b ){
	return sum[a] < sum[b];
}

void build( int node, int L, int R ){
	seg[node] = 0;
	if ( L==R ) return;
	int M = ( L + R ) >> 1;
	build( node<<1, L, M );
	build( (node<<1)|1, M+1, R );
}

void update( int node, int L, int R, int p, int v ){
	if ( L==R ){ seg[node] += v; seg[node] %= MOD; return; }
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( node << 1, L, M, p, v );
	else update( (node<<1)|1, M+1, R, p, v );
	seg[ node ] = ( seg[ node<<1 ] + seg[ (node<<1)|1 ] ) % MOD;
}

int query( int node, int L, int R, int l, int r ){
	if ( L==l && R==r ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return ( query(node<<1, L,M,l,M) + query((node<<1)|1, M+1,R, M+1, r) )%MOD;
}

int main(){
	int x;
	scanf("%d", &N);
	sum[0] = 0;
	ord[0] = 0;
	for ( int i=1; i <= N ; ++i ){
		scanf("%d", &x);
		sum[i] = sum[i-1] + x;
		ord[i] = i;
	}
	sort( ord, ord + (N+1), cmp );
	int last = -INT_MAX;
	int size = 0;
	for ( int i=0; i <= N; ++i ){
		if ( last < sum[ ord[i] ] ){
			idx[ ord[i] ] = size++;
			last = sum[ ord[i] ];
		}
		else {
			idx[ ord[i] ] = size - 1;
		}
	}
	// Init DP
	build( 1, 0 , size-1 );	
	for ( int i=0; i <= N; ++i ){
		if ( sum[i] == 0 ){
			update( 1 , 0, size-1, idx[i], 1 );
			break;
		}
	}
	// dpi = dp(i) = # of partitions of subarray [0 ... i]
	int dpi;
	for ( int i=1; i <= N; ++i ){
		dpi = query( 1, 0, size-1, 0, idx[ i ] );
		update( 1, 0, size-1, idx[i], dpi );
	}
	printf("%d\n", dpi);
	return 0;
}

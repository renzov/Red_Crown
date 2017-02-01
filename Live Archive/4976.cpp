#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 200005;

int h[MAXN];
int s[MAXN];
int hs[MAXN];
int seg[ 4*MAXN ];
int S;

void build( int node, int L, int R ){
	seg[ node ] = 0;
	if ( L != R ){
		int M = ( L + R ) >> 1;
		build( node << 1, L , M );
		build( (node << 1)| 1, M + 1, R );
	}
}

void update(int node, int L, int R, int p, int val){
	if (seg[node] < val) seg[node] = val;	
	if ( L==R ) return;
	int M = (L+R) >> 1;
	if ( p <= M ) update( node << 1, L, M, p, val );
	else update( (node<<1)|1 , M+1, R, p, val );
}

int query( int node, int L,int R, int l, int r ){
	if ( L == l && r == R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return max( query(node<<1,L,M,l,M), query((node<<1)|1,M+1,R,M+1,r) );
}

int main(){
	int runs;
	int N;
	scanf("%d", &runs);
	while (runs--){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d", h + i);
			hs[i] = h[i];
		}
		sort( hs, hs + N );
		S = unique( hs, hs + N ) - hs;
		s[N-1] = 1;
		for ( int i=N-2; i >= 0 ; --i )
			s[i] = (h[i] < h[i+1])? (s[i+1] + 1):1; 		
		
		build( 1 , 0 , S-1 );
		int res = s[0];
		int pos = lower_bound( hs, hs + S, h[0] ) - hs;
		int e = 1;		
		update( 1, 0, S-1, pos, 1 );		
		
		for ( int i=1; i < N; ++i ){
			e = ( h[i] > h[i-1] )? ( e + 1 ):1;
			pos = lower_bound( hs, hs + S , h[i] ) - hs;
			if ( pos > 0 )			
				res = max( res, s[i] + query( 1 , 0, S-1, 0 , pos - 1 ) );
			else 
				res = max( res, s[i] );
			update( 1, 0, S-1, pos, e );
		}
		printf("%d\n", res);
	}
	return 0;
}

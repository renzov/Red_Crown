#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 50005;

int seg[4*MAXN];

void update( int node, int L,int R, int p, int val ){
	if ( seg[node] > val ) seg[node] = val;
	if ( L==R ) return;
	int M = ( L+R ) >> 1;
	if ( p <= M ) update( node << 1, L, M, p, val );
	else update( (node << 1) | 1, M+1, R, p, val );
}

int query( int node, int L,int R, int l, int r ){
	if ( L == l && r == R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node << 1, L, M, l, r );
	if ( l > M ) return query( (node << 1) | 1, M+1, R, l, r );
	return min( query(node << 1, L,M, l,M), query((node<<1)|1, M+1, R, M+1, r) );
}

int main(){
	int x,y;
	int runs;
	int res;
	int N,M;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		fill( seg, seg + 4*N, INT_MAX );
		update( 1 , 0, N-1, 0, 0 );
		while ( M-- ){
			scanf("%d %d", &x, &y);
			x--, y--;
			if ( (res = query( 1, 0, N-1, x, y-1)) != INT_MAX ){
				update( 1, 0, N-1, y, res + 1 );
			}
		}
		printf("%d\n", query(1, 0, N-1, N-1, N-1));
		if ( runs ) puts("");
	}
	return 0;
}


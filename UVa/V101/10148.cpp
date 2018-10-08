#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;

const int MAXN = 1024;
const int SHIFT = 10002;

int p[2*SHIFT + 5];
pii I[MAXN];
bool filled[2*SHIFT + 5];
int seg[8*SHIFT];
 
inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }
inline int find_set( const int &x ){ return x == p[x]? x:( p[x] = find_set( p[x] ) ); }


void build( const int &node, const int &L, const int &R ){
	if ( L == R ) {
		seg[node] = 0; return;
	}
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
	seg[node] = 0;
}

void update( const int &node, const int &L, const int &R, const int &pos ){
	if ( L == R ){
		seg[node] = 1; return;
	}
	int M = ( L + R ) >> 1;
	if ( pos <= M ) update( left(node), L, M, pos );
	else update( right(node), M + 1, R, pos );
	seg[node] = seg[left(node)] + seg[right(node)]; 
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && R == r ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return query( left(node), L, M, l, M ) + query( right(node), M + 1, R, M + 1, r );
}
 
int fill_up( const int &x, const int &k ){
	if ( k <= 0 ) return 0;
	if ( !filled[x] ){
		p[x] = p[x - 1];
		filled[x] = true;
		update( 1, 0, 2*SHIFT - 1 , x );
		return 1 + fill_up( x - 1, k - 1 );
	}
	else {
		int nx = find_set( x );
		return fill_up( nx , k );
	} 
}

void process(){
	int N, K;
	int l, r;
	int res = 0;
	// Set up the sets
	build( 1, 0, 2*SHIFT - 1 );
	for ( int i=0; i < 2*SHIFT; ++i ) 
		p[i] = i, filled[i] = false;
	int n = 0;
	scanf("%d %d", &K, &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &l, &r);
		if ( l > r ) swap(l , r);
 		if ( (r - l + 1) <= K ){
			res += fill_up( r + SHIFT , r - l + 1 - query( 1, 0, 2*SHIFT - 1, l + SHIFT, r + SHIFT ) );
		}
		else {
			I[n++] = pii( r + SHIFT, l + SHIFT);
		}
	}	
	sort( I, I + n );
	for ( int i=0; i < n; ++i ){
		res += fill_up( I[i].first, K - query( 1, 0, 2*SHIFT - 1, I[i].second, I[i].first ) );
	}
	printf("%d\n", res);
	for ( int i=0; i < 2*SHIFT; ++i )
		if ( filled[i] ) printf("%d\n", i - SHIFT);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		if ( runs ) puts("");
	}
	return 0;
}

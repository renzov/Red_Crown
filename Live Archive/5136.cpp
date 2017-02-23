#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cctype>

using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 100005;
const int MAXC = 1000005;
int N;
int X[MAXN];
int Y[MAXN];

// For rectangles
int Y1Rec[MAXN];
int Y2Rec[MAXN];

struct event {
	int x, idx, v;
	event(){}
	event(int xx, int i, int V){
		x = xx, idx = i, v = V;
	}
	bool operator<(const event &e) const {
		if ( x != e.x ) return x < e.x;
		return v < e.v;
	}
};

event E[ 2 * MAXN ];
int seg[ 8 * MAXC ];
int cnt[ 8 * MAXC ];

void correct( int node, int L, int R ){
	if ( cnt[node] > 0 ) seg[node] = R - L + 1;
	else {
		if ( L == R ) seg[node] = 0;
		else seg[node] = seg[node<<1] + seg[(node<<1)|1]; 
	}
}

void update( int node, int L, int R, int l, int r, int v ){
	if ( L == l && r == R ){
		cnt[node] += v;
		correct( node, L, R );
		return;
	}
	int M = ( L + R ) >> 1;
	if ( r <= M ) update( node<<1, L, M, l, r, v );
	else if ( l > M ) update( (node<<1)|1, M+1, R, l, r, v );
	else {
		update( node<<1, L, M, l, M, v );
		update( (node<<1)|1, M+1, R, M+1, r, v );
	}
	correct( node, L, R );
}

void build( int node, int L, int R ){
	seg[node] = cnt[node] = 0;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	build( node<<1, L, M );
	build( (node<<1)|1, M+1, R );
}

bool cover( int len ){
	// prepare rectangles
	int Xl = -len;
	int Xr = len;
	int Yr = len;
	int Yl = -len;

	int x1, x2, y1, y2;
	int M, e;
	e = M = 0;

	for ( int i=0; i < N; ++i ){
		x1 = max( Xl, X[i] - len );
		x2 = min( Xr, X[i] + len );
		y1 = max( Yl, Y[i] - len );
		y2 = min( Yr, Y[i] + len );
		// check for non empty intersection
		if ( x1 <= x2 && y1 <= y2 ){ // new rectangle
			Y1Rec[ M ] = y1 + len, Y2Rec[ M ] = y2 + len;
			E[e++] = event( x1, M, 1 );
			E[e++] = event( x2 + 1, M, -1 );
			M++;
		}
	}
	sort( E, E + e );
	// sweep line
	build( 1, 0, 2*len );
	long long area = 0LL;
	int x, idx;
	int lastX = E[0].x;
	for ( int i=0; i < e; ){
		x = E[i].x;
		if ( lastX < x ) area += 1LL*(x - lastX)*seg[1];
		do {
			idx = E[i].idx;
			update( 1, 0, 2*len, Y1Rec[idx], Y2Rec[idx], E[i].v );
			i++;
		}
		while ( i < e && E[i].x == x );
		lastX = x;
	}
	return area == (4LL*len*len + 4LL*len + 1LL); // area == (2*len + 1)^2
}

int main(){
	int L;	// max bound on coordinates
	int cases = 0;
	while ( scanf("%d", &N) && N >= 0 ){
		cases++;
		printf("Case %d: ", cases);
		L = 0;
		for ( int i=0; i < N; ++i ){ scanf("%d %d", X+i, Y+i); }
		if ( N == 0 ){ printf("never\n"); continue; }
		for ( int i=0; i < N; ++i ) L = max( L, max( abs(X[i]), abs(Y[i]) ) );
		if ( cover( L ) ){
			int l = 0; // No cover
			int r = L; // can be covered
			int m;
			while ( r - l > 1 ){
				m = ( l + r ) >> 1;
				if ( cover(m) ) r = m;
				else l = m;
			}
			printf("%d\n", r);
		}
		else {
			puts("never");
		}
	}
	return 0;
}

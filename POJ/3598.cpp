#include<cstdio>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef pair< pii, int > event;
const int MAXN = 100005;

int seg[4*MAXN] = {0};	// Max segtree

int N;					// Number of cars
int M;					// Max compressed value of Y[]
int X[MAXN];			// v[]
int Y[MAXN];			// w[]
int idx[MAXN];			// Compressed coordinate of Y
int valY[MAXN];			// Extra vector for compression
int res[MAXN];			// Value of the level
int ord[MAXN];			// order of the 

bool cmp( const int &i, const int &j ){
	return ( X[i] != X[j] )? ( X[i] > X[j] ):( Y[i] > Y[j] );
}

bool cmp2( const int &i, const int &j ){
	if ( res[i] != res[j] ) return res[i] < res[j];
	return ( X[i] != X[j] )? ( X[i] < X[j] ):( Y[i] < Y[j] );
}

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){ seg[node] = max( seg[node], v ); return; }
	
	int mid = ( L + R ) >> 1;
	
	if ( p <= mid ) update( node<<1, L , mid, p, v );
	else update( (node<<1)|1, mid + 1, R, p , v );

	seg[node] = max( seg[node<<1], seg[(node<<1)| 1] );
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L >= l && r >= R ) return seg[node];
	
	int mid = ( L + R ) >> 1;
	
	if ( r <= mid ) return query( node << 1, L , mid, l, r );
	if ( l > mid ) return query( (node<<1)|1, mid + 1, R, l, r );
	
	return max( query( node<<1, L, mid, l, mid ) ,  
				query( (node<<1)|1, mid + 1, R, mid + 1, r ) );
}

void compressY(){
	sort( valY, valY + N );
	M = unique( valY, valY + N ) - valY;
	for ( int i=0; i < N; ++i )
		idx[ i ] = lower_bound( valY, valY + M, Y[i] ) - valY;
}

int main(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", X + i, Y + i);
		valY[i] = Y[i];
		ord[i] = i;
	}
	compressY();	
	// order the events
	sort( ord, ord + N, cmp );
	int pos;
	int last = -1;	// Take care of "equal" cars

	// sweep line and calculation of res[]
	for ( int i=0; i < N; ++i ){
		pos = ord[i];
		if ( last >= 0 && X[pos] == X[last] && Y[pos] == Y[last] ){ 
			res[pos] = res[last];
		}
		else {
			res[ pos ] = query( 1, 0, M - 1, idx[ pos ], M - 1 ) + 1;
			update( 1, 0, M - 1, idx[pos], res[ pos ] );
		}
		last = pos;
	}
	// sort the answer
	for ( int i=0; i < N; ++i ) ord[i] = i;
	sort( ord, ord + N, cmp2 );
	

	for ( int i=0, j=0 ; j < N; ){
		
		while ( j < N && res[ ord[j] ] == res[ ord[i] ] ) j++;
		printf("%d:", j - i);
		while ( i < j ){
			printf(" (%d,%d)", X[ ord[i] ], Y[ ord[i] ]);
			i++;
		}
		puts("");
	}
	return 0;
}

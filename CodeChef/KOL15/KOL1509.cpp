#include<cstdio>
#include<algorithm>
using namespace std;
#define X first
#define Y second
typedef pair<int, int> point;

const int MAXN = 100005;

point P[2*MAXN];
int H[2*MAXN];
point O;
int A[MAXN];
int n; // Number of points

long long area2( const point &a, const point &b, const point &c ){
	return 1LL*(b.X-a.X)*(c.Y-a.Y) - 1LL*(c.X - a.X)*(b.Y - a.Y);
}

bool cmp( const point &p, const point &q ){
	long long a = area2( O, p, q );
	if ( a > 0 ) return true;
	if ( a < 0 ) return false;
	if ( p.X < q.X || (p.X == q.X && p.Y < q.Y) ) return true;
	return false;
}

long long convex_hull(){
	if ( n <= 2 ){
		return 0LL;
	}
	// Points are already sorted by X, and then Y
	O = P[0];
	// Sort by angle and apply Graham's algorithm
	sort( P+1, P+n, cmp );
	int size = 0;
	H[size++] = 0;
	H[size++] = 1;
	for ( int i=2; i < n; ++i ){
		while ( size >= 2 && area2( P[ H[size-2] ], P[ H[size-1] ], P[i] ) <= 0LL )
			size--;
		H[size++] = i;
	}
	long long res = 0;
	// Find the area
	if ( size <= 2 ) return 0LL;	
	for ( int i=2; i < size; ++i ){
		res += area2( O , P[ H[i-1] ] , P[ H[i] ] );
	}
	return res;
}

int main(){
	int runs;	
	int m, M;
	int N;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		if ( N > MAXN ) while(1);
		for ( int i=0; i < N; ++i ){ 
			scanf("%d", A + i);
			if ( A[i] < 1 || A[i] > 100000000 )
				while(1);		
		}
		M = m = A[0];
		n = 0;
		for ( int i=1; i < N; ++i ){
			P[n++] = point( m , A[i] );
			if ( M != m ){
				P[n++] = point( M , A[i] );
			}
			m = min( m , A[i] );
			M = max( M , A[i] );
		}
		// Delete repeated points
		sort( P, P + n );
		n = unique( P , P + n ) - P;
		// Find the convex hull and area
		long long res = convex_hull();
		printf("%lld\n", res);
	}
	return 0;
}

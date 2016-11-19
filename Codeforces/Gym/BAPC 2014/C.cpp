#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>

#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 1005;
point O;
point P[MAXN]; 
point H[2*MAXN];
int N;

int area2( const point &A, const point &B, const point &C ){
	return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y); 
}

int dist2( const point &A, const point &B ){
	return (A.X-B.X)*(A.X-B.X) + (A.Y-B.Y)*(A.Y-B.Y);
}

bool cmp( const point &A, const point &B ){
	int dir = area2( O , A, B );
	if ( dir > 0 ) return true;
	if ( dir < 0 ) return false;
	return dist2( O, A ) < dist2( O, B );
}

void convex_hull( int n ){
	int idx = min_element( P, P + n ) - P;
	if ( idx > 0 ) swap( P[0] , P[idx] );
	O = P[0];
	sort( P + 1 , P + n, cmp );
	H[ 0 ] = P[ 0 ];
	H[ 1 ] = P[ 1 ];
	N = 2;
	for ( int i=0; i < n; ++i ){
		while ( N > 1 && area2(H[N-2], H[N-1], P[i]) <= 0 )
			N--;
		H[ N++ ] = P[i];
	}
	// Duplicate the vertices
	for ( int i=0; i < N; ++i ) H[i+N] = H[i];
}

int ternary_search( int i, int j, int x, int y ){
	int m1 = (2*i + j) / 3;
	int m2 = (i + 2*j) / 3;
	if ( j - i < 3 ) return area2( H[x], H[m2] , H[y] );
	if ( area2( H[x], H[m1], H[y] ) > area2( H[x], H[m2], H[y]) )
		return ternary_search( i , m2, x, y );
	else 
		return ternary_search( m1, j, x, y );
}

void output( int x ){
	printf("%d", x>>1);
	if ( x&1 ) printf(".5");
	putchar('\n');
}

int main(){
	int n;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &n);
		for ( int i=0; i < n; ++i )
			scanf("%d %d", &P[i].X, &P[i].Y);
		convex_hull( n );
		
		if ( N == 2 ) output(0);
		else if ( N == 3 ) output( area2(H[0], H[1], H[2]) );
		else if ( N == 4 ) output( area2(H[0], H[1], H[2]) + area2(H[2], H[3], H[0]) );
		else {
			int res = 0;
			int a;
			for ( int i=0; i < N-2; ++i )
				for ( int j=i+2; j < N; ++j ){
					// Ternary search 1
					a = ternary_search( i , j, i, j );
					// Ternary search 2
					a += ternary_search( j , i + N , j, i + N );
					if ( res < a ) res = a;
				}
			output(res);
		}
	}
	return 0;
}

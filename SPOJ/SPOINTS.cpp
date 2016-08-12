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
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 105;
point A[MAXN];
point B[MAXN];
point P1[MAXN];
point P2[MAXN];

int H[MAXN];
int size;
point O;

int area2( const point &a, const point &b, const point &c ){
	int r = (b.X-a.X)*(c.Y-a.Y) - (c.X - a.X)*(b.Y - a.Y);
	if ( r > 0 ) return 1;
	if ( r < 0 ) return -1;
	return 0;
}

bool in_seg( const point &a, const point &b, const point &c ){
	return min(a.X,b.X) <= c.X && c.X <= max(a.X, b.X) &&
	       min(a.Y,b.Y) <= c.Y && c.Y <= max(a.Y, b.Y);
}

bool inter_seg( const point &a, const point &b, const point &c, const point &d ){
	int d1 = area2( c, d, a );
	int d2 = area2( c, d, b );
	int d3 = area2( a, b, c );
	int d4 = area2( a, b, d );
	if ( d1*d2 < 0 && d3*d4 < 0 ) return true;
	if ( d1 == 0 && in_seg(c,d,a) ) return true;
	if ( d2 == 0 && in_seg(c,d,b) ) return true;
	if ( d3 == 0 && in_seg(a,b,c) ) return true;
	if ( d4 == 0 && in_seg(a,b,d) ) return true;
	return false;
}

bool cmp( const point &p, const point &q ){
	int a = area2( O, p, q );
	if ( a > 0 ) return true;
	if ( a < 0 ) return false;
	if ( p.X < q.X || (p.X == q.X && p.Y < q.Y) ) return true;
	return false;
}

bool inside( const point &p, point P[], int s ){
	if ( s == 1 ) return false;
	if ( s == 2 ) return area2(P[0], P[1], p) == 0 && in_seg( P[0], P[1], p );
	int a;
	for ( int i=0; i < s; ++i ){
		a = area2( P[i], P[i+1], p );
		if ( a < 0 || (a == 0 && !in_seg(P[i], P[i+1], p)) )
			return false;
	}
	return true;
}

int convex_hull( point P[], int s, point R[] ){
	if ( s == 1 ){
		R[0] = P[0];
		return 1;
	}
	int idx = min_element( P, P + s ) - P;
	if (idx) swap( P[0], P[idx] );
	O = P[0];
	sort( P+1, P+s, cmp );
	
	size = 0;
	H[size++] = 0;
	H[size++] = 1;
	for ( int i=2; i < s; ++i ){
		while ( size >= 2 && area2( P[ H[size-2] ], P[ H[size-1] ], P[i] ) <= 0 )
			size--;
		H[size++] = i;
	}
	for ( int i=0; i < size; ++i ) R[i] = P[H[i]];
	R[size] = P[ H[0] ];
	return size;
}

int main(){
	int N, M;
	int n, m;

	while ( scanf("%d %d", &n, &m) && n && m ){
		for ( int i=0; i < n; ++i ) scanf("%d %d", &A[i].X, &A[i].Y);
		for ( int i=0; i < m; ++i ) scanf("%d %d", &B[i].X, &B[i].Y);
		N = convex_hull( A, n, P1 );
		M = convex_hull( B, m, P2 );
		bool ok = true;
		// Test point in polygon
		for ( int i=0; i < N && ok; ++i ) 
			if ( inside( P1[i], P2, M ) ) ok = false;
		
		for (int i=0; i < M && ok; ++i )
			if ( inside( P2[i], P1, N ) ) ok = false;
		// Test for segment intersection
		if (N > 1 && M > 1){ 
			for ( int i=0; i < N && ok; ++i )
				for ( int j=0; j < M && ok; ++j )
					if ( inter_seg( P1[i], P1[i+1], P2[j], P2[j+1] ) ) ok = false;
		}
		if (ok) puts("YES");
		else puts("NO");
	}
	return 0;
}


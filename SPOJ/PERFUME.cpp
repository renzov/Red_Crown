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
typedef pair< double , double > point;
const double EPS = 1e-6;
const int MAXN = 205;
point A[MAXN];
point P1[MAXN];

int H[MAXN];
int size;
point O;

int compare( const double &a, const double &b ){
	if ( fabs(a-b) < EPS ) return 0;
	if ( a < b ) return -1;
	return 1;
}

int area2( const point &a, const point &b, const point &c ){
	double r = (b.X-a.X)*(c.Y-a.Y) - (c.X - a.X)*(b.Y - a.Y);
	if (fabs(r) < EPS) return 0;
	if ( r > 0 ) return 1;
	return -1;
}

bool in_seg( const point &a, const point &b, const point &c ){
	return compare(c.X, min(a.X,b.X)) >= 0 && compare(c.X, max(a.X, b.X)) <= 0 &&
	       compare(c.Y, min(a.Y,b.Y)) >= 0 && compare(c.Y, max(a.Y, b.Y)) <= 0;
}

bool cmp( const point &p, const point &q ){
	int a = area2( O, p, q );
	if ( a > 0 ) return true;
	if ( a < 0 ) return false;
	if ( compare(p.X,q.X) < 0 || (compare(p.X,q.X) == 0 && compare(p.Y, q.Y) < 0) ) return true;
	return false;
}

bool inside( const point &p, point P[], int N ){
	if ( N == 1 ){
		return compare(p.X, P[0].X) == 0 && compare(p.Y, P[0].Y) == 0;
	}
	if ( N == 2 ){
		return area2( P[0], P[1], p ) == 0 && in_seg(P[0], P[1], p);
	}
	// Out of bounds
	if ( area2(P[0],P[1], p) < 0 || area2(P[0],P[N-1], p) > 0 ) return false;
	
	if ( area2(P[0], P[1], p) == 0 ) return in_seg( P[0], P[1], p );
	if ( area2(P[0], P[N-1], p) == 0 ) return in_seg(P[0], P[N-1], p);

	int l = 1;
	int r = N-1;
	int m, a;
	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		a = area2( P[0], P[m], p );
		if ( a > 0 ) l = m;
		else r = m;
	}
	a = area2( P[l], P[l+1] , p );
	return (a > 0) || (a == 0 && in_seg(P[l], P[l+1], p));
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
	int N, n, Q;
	point p;
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &n);
		for ( int i=0; i < n; ++i ) scanf("%lf %lf", &A[i].X, &A[i].Y);
		N = convex_hull( A, n, P1 );
		scanf("%d", &Q);
		while ( Q-- ){
			scanf("%lf %lf", &p.X, &p.Y);
			if ( inside(p, P1, N) ) puts("Yes");
			else puts("No");
		}
		if (runs) puts("");
	}
	return 0;
}



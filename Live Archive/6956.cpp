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
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 100005;
int N, n, m;
long long X[MAXN];
long long Y[MAXN];
long long X2[3*MAXN+6];
long long Y2[3*MAXN+6];
long long Xsum[3*MAXN + 6];
map<long long, long long> Ysum;


int main(){
	long long xpy_min, xpy_max, xmy_min, xmy_max;
	long long d;
	long long x, y;
	long long ymin, ymax;
	long long xmin, xmax;
	long long res;
	while ( scanf("%d", &N) != EOF ){
		for ( int i=0; i < N; ++i ) scanf("%lld %lld", &X[i], &Y[i]);
		scanf("%lld", &d);
		// initialize variables
		xpy_min = xmy_min = -1000000000LL;
		xpy_max = xmy_max = 2000000000LL;
		for ( int i=0; i < N; ++i ){
			xpy_min = max(xpy_min, X[i] + Y[i] - d);
			xpy_max = min(xpy_max, X[i] + Y[i] + d);
			xmy_min = max(xmy_min, X[i] - Y[i] - d);
			xmy_max = min(xmy_max, X[i] - Y[i] + d);
		}
		// check for viability
		if ( xpy_min > xpy_max || xmy_min > xmy_max ){
			puts("impossible");
			continue;
		}
		sort( X, X + N );
		sort( Y, Y + N );
		// Check for the case where median is inside feasible region
		x = X[N/2], y = Y[N/2];
		if ( (x+y) >= xpy_min && (x+y) <= xpy_max && (x-y) >= xmy_min && (x-y) <= xmy_max ){
			res = 0;
			for ( int i=0; i < N; ++i ) res += ( llabs(X[i]-x) + llabs(Y[i]-y) );
			printf("%lld\n", res);
			continue;
		}
		copy( X, X + N, X2 );
		copy( Y, Y + N, Y2 );
		m = n = N;
		// Adding border coord. of polytope
		X2[n++] = ( xmy_min + xpy_min + 1 ) / 2;
		X2[n++] = ( xmy_max + xpy_max ) / 2;
		Y2[m++] = ( xpy_min - xmy_max + 1 ) / 2;
		Y2[m++] = ( xpy_max - xmy_min ) / 2;
		// Adding candidate Y points
		for ( int i=0; i < (N+2); ++i ){
			ymin = max( X2[i] - xmy_max, xpy_min - X2[i] );
			ymax = min( X2[i] - xmy_min, xpy_max - X2[i] );
			if ( ymin <= ymax ){
				Y2[m++] = ymin;
				Y2[m++] = ymax;
			}
		}
		// Adding candidate X points
		for ( int i=0; i < (N+2); ++i ){
			xmin = max( xpy_min - Y2[i], xmy_min + Y2[i] );
			xmax = min( xpy_max - Y2[i], xmy_max + Y2[i] );
			if ( xmin <= xmax ){
				X2[n++] = xmin;
				X2[n++] = xmax;
			}
		}
		// Precalc sum abs(x - xi) + abs(y - yi) separately
		sort( X2, X2 + n );
		sort( Y2, Y2 + m );
		// Calculate |X - Xi| for all important X
		Xsum[0] = 0LL;
		for ( int i=0; i < N; ++i ){
			Xsum[0] += (X[i] - X2[0]);
		}
		for ( int i=1, j=0; i < n; ++i ){
			for ( ; j < N && X2[i] > X[j]; ++j );
			Xsum[i] = Xsum[i-1] + (j - (N-j) )*( X2[i] - X2[i-1] );
		}
		Ysum.clear();
		long long sum = 0;
		for ( int i=0; i < N; ++i ){
			sum += (Y[i] - Y2[0]);
		}
		Ysum[ Y2[0] ] = sum;
		for ( int i=1, j=0; i < m; ++i ){
			for ( ; j < N && Y2[i] > Y[j]; ++j );
			Ysum[ Y2[i] ] = Ysum[ Y2[i-1] ] + ( j - (N-j) )*( Y2[i] - Y2[i-1] );
		}
		// Calculate the answer
		res = 1LL << 60;
		for ( int i=0; i < n; ++i ){
			ymin = max( X2[i] - xmy_max, xpy_min - X2[i] );
			ymax = min( X2[i] - xmy_min, xpy_max - X2[i] );
			if ( ymin <= ymax ){
				if ( Ysum.count( ymin ) ) res = min( res, Xsum[i] + Ysum[ ymin ] );
				if ( Ysum.count( ymax ) ) res = min( res, Xsum[i] + Ysum[ ymax ] );
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}


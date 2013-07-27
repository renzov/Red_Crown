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

const double INF = 10e10;
const double PI = 2*acos(0);

struct point {
	int x,y;
	bool operator<(const point &that) const {
		return (x!=that.x)? (x < that.x):(y < that.y);
	}
};

int n,m;
point p[10];

double D[1<<10][10];
double L[1<<10];
double dp[1<<10];

inline double len( int i , int j ){
	return hypot( p[i].x - p[j].x , p[i].y - p[j].y );
}

inline double dist2(const point &a ,const point &b ){
	return hypot( a.x - b.x , a.y - b.y );
}

inline int areaS( point &a, point &b, point &c ){
	return (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y ); 
}

double perimeter( point *P , int size ){
	//Finding convex hull
	if ( size == 1 ){
		return 2*PI*m;
	}

	point lower[15];
	int L;
	lower[ 0 ] = P[ 0 ]; lower[ 1 ] = P[ 1 ];
	L = 2;
	
	for ( int i=2; i < size ; ++i ){
		while ( L > 1 && areaS( lower[ L - 2 ] , lower[ L - 1 ] , P[ i ] ) <= 0 )
			L--;
		lower[ L++ ] = P[i];
	}

	point upper[15];
	int U;
	upper[ 0 ] = P[ size - 1 ]; upper[ 1 ] = P[ size - 2 ];
	U = 2;

	for ( int i=size - 3; i >= 0 ; --i ){
		while ( U > 1 && areaS( upper[ U - 2 ] , upper[ U - 1 ] , P[i] ) <= 0 )
			U--;
		upper[ U++ ] = P[ i ];
	}
	for ( int i=1; i < U ; ++i ){
		lower[ L++ ] = upper[ i ];
	}

	double res = 2*PI*m;
	
	for ( int i=0; i < L-1; ++i )
		res += dist2( lower[i] , lower[i+1] );

	return res;
}

inline bool bit( int mask , int pos ){
	return ( mask >> pos ) & 1;
}

int main(){
	int runs = 0;	
	while ( scanf("%d %d",&n, &m) && n ){
		runs++;
		for ( int i=0; i<n; ++i )
			scanf("%d %d",&p[i].x,&p[i].y);
		sort ( p , p + n );

		for ( int mask = 1; mask < (1<<n) ; ++mask ){
			for ( int i = 0; i<n  ; ++i ){
				if ( bit(mask,i) ){ D[mask][i] = 0.0; continue; }
				D[mask][i] = INF;
				for ( int j=0; j < n; ++j ){
					if (bit(mask,j)) D[mask][i] = min(D[mask][i], len( i , j ) );
				}
			}
		}

		int size;
		point list[10];
		for ( int i=1; i < (1<<n); ++i ){
			size = 0;
			for ( int j=0; j < n; ++j ){
				if ( bit(i,j) ) list[ size++ ] = p[j];
			}
			L[i] = perimeter( list , size );
		}
		bool ok;
		
		dp[ 0 ] = 0.0;
		
		for ( int i=0; i < n; ++i )
			dp[ 1<<i ] = L[1<<i];

		for ( int i=1; i<(1<<n) ; ++i ){
			if ( __builtin_popcount( i ) == 1 ) continue;
			dp[ i ] = L[i];
			for ( int j=1; j < i ; ++j ){
				
				if ( (i & j) == j ){
					ok = true;
					for ( int k=0; ok && k < n; ++k ){
						if ( !bit(j,k) && bit(i,k) && (D[j][k] < m) ) ok = false;
					}
					if (ok) dp[ i ] = min( dp[i] , dp[ i ^ j ] + L[ j ] );
				}

			}
		}
		printf("Case %d: length = %0.2lf\n",runs,dp[(1<<n)-1]);
	}
	return 0;
}


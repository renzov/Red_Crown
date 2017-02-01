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
const int MAXN = 200;
const double INF = 1e8;
const double EPS = 1e-8;

int N;

int sgn( double x ){
	if ( abs(x) < EPS ) return 0;
	if ( x < 0 ) return -1;
	return 1;
}

struct point {
	double x,y;
	point(const int &X ,const int &Y ){
		x = X, y = Y;
	}
	point(){}

	bool operator <(const point &p) const {
		if (sgn(x - p.x) != 0) return x < p.x;
		return y < p.y;
	}

};

struct line{
	double m,b;
	line( const point &A, const point &B ){
		m = (A.y - B.y) / (A.x - B.x);
		b = A.y - A.x * m;
	}
	line(){}

	double distX( point &p ){
		double res;
		res = abs( p.y - (m * p.x + b) );
		return (res < EPS)? 0.0 : res;
	}

};

double cross(const point &a , const point &b , const point &c ){
	return (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y ); 
}

vector<int> up_hull( vector<point> P ){
	int res[MAXN];
	sort( P.begin() , P.end() );
	res[0] = 0; res[1] = 1;
	int m = 2;

	for ( int i=2; i < N; ++i ){
		while ( m > 1 && sgn( cross( P[ res[m-2] ] , P[ res[m-1] ] , P[i] ) ) > 0 ){
			m--;
		}
		res[m++] = i;
	}

	return vector<int>( res , res + m );
}

double D[MAXN][MAXN];
double dp[MAXN][MAXN];

double solve( int pos, int sec ){

	if ( sec == 1 ) return D[pos][N-1];

	if ( sgn(dp[pos][sec]) >= 0 ) return dp[pos][sec];

	double res = INF;
	double tmp;

	for ( int i = pos + 1; i < N ; ++i ){
		tmp = max( D[pos][i] , solve( i + 1 , sec - 1 ) );
		if ( tmp < res ) res = tmp;
	}
	return dp[pos][sec] = res;
}

int main(){

	int K;

	while ( scanf("%d %d",&N,&K) && N && K ){
		
		vector<point> P(N);
		
		for ( int i=0; i < N; ++i ){
			scanf("%lf %lf",&P[i].x,&P[i].y);
		}

		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j  ){
				dp[i][j] = -1;
				D[i][j] = INF;
			}

		vector<int> upper = up_hull( P );
			
		int M = upper.size();
		
		vector<line> L( M - 1 );

		for ( int i=0; i < (M - 1); ++i ){
			L[i] = line( P[ upper[i] ] , P[ upper[i+1] ] );
			D[ upper[i] ][ upper[i+1] ] = 0.0;
			for ( int j=upper[i] + 1; j < upper[i+1]; ++j ){
				D[ upper[i] ][ upper[i+1] ] = max( D[ upper[i] ][ upper[i+1] ] , L[i].distX(P[j]) );	
			}
		}

		for ( int i=0; i < (M - 1); ++i ){
			for ( int j=upper[i+1] ; j < N ; ++j ){
		
				if ( j != upper[i+1] ){
					D[ upper[i] ][ j ] = min( D[ upper[i] ][j] , max( D[ upper[i] ][ j - 1 ] , L[i].distX( P[j] ) ) );
				}

				for ( int k=upper[i] - 1; k >= 0 ; --k ){
					D[ k ][ j ] = min( D[k][j] , max( D[k+1][j] , L[i].distX( P[k] ) ) );
				}
			}
		}

		printf("%0.3lf\n",solve( 0 , K ) );

	}
	

	return 0;
}


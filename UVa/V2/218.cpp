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
const double EPS = 0.0001;
int n;

struct point{
	double x,y;
	point(){}
	point (double X,double Y){ x = X; y = Y; }
	bool operator<( const point &that ) const {
		if ( fabs( x - that.x ) > EPS ){
			return x < that.x;
		}
		else {
			return y < that.y;
		}
	}
};

inline double Dist( point &a , point &b ){
	return hypot( a.x - b.x , a.y - b.y );
}

double area2( point &a , point &b , point &c ){
	double A = (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y );
	if ( fabs( A ) < EPS ) A = 0.0;
	return A;
}

vector<point> monotone_chain( vector<point> &P ){

	sort( P.begin() , P.end() );
	
	point upper[n];
	upper[0] = P[0]; upper[1] = P[1];
	int U = 2;
	for ( int i=2; i < n; ++i ){
		while ( U > 1 && area2( upper[U-2] , upper[U-1] , P[i] ) > 0.0 ){
			U--;
		}
		upper[U++] = P[i];
	}
	point lower[n];
	lower[0] = P[n - 1]; lower[1] = P[n - 2];
	int L = 2; 
	for ( int i=n-3; i >= 0 ; --i ){
		while ( L > 1 && area2( lower[L-2] , lower[L-1] , P[i] ) > 0.0 ){
			L--;
		}
		lower[ L++ ] = P[i];
	}
	
	for ( int i=1; i < (L - 1) ; ++i ) upper[U++] = lower[i];

	return vector<point>(upper , upper + U);
}

int main(){
	int runs = 0;
	while ( scanf("%d",&n) && n ){
		runs++;
		if ( runs > 1 ) puts("");
		printf("Region #%d:\n",runs);

		vector<point> P(n);
		for ( int i=0; i < n; ++i )
			scanf("%lf %lf", &P[i].x , &P[i].y );
		
		vector<point> res = monotone_chain(P);
		
		double len = 0.0;

		for ( int i=0; i < res.size(); ++i ){
			printf("(%0.1lf,%0.1lf)-",res[i].x,res[i].y);
			len += Dist( res[i] , res[ ( i + 1 ) % res.size() ] );
		}
		printf("(%0.1lf,%0.1lf)\n",res[0].x,res[0].y);
		printf("Perimeter length = %0.2lf\n",len);
	}	
	return 0;
}


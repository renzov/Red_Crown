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

struct point{
	long long x,y;
	point(){}
	point(int X,int Y){ x = X, y = Y; }
	bool operator< ( const point &that ) const {
		return ( x != that.x )? (x < that.x) : (y < that.y);
	}
};


int areaSig( point &a, point &b, point &c ){
	long long t = (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y ); 
	if ( !t ) return 0;
	return ( t > 0 )? 1:-1;
}

vector<point> monotone_chain( vector<point> &P ){
	sort( all(P) );
	point lower[ P.size() + 2 ];
	lower[ 0 ] = P[ 0 ]; lower[1] = P[1];
	int L = 2;

	for ( int i=2; i < P.size(); ++i ){
		while ( L > 1 && areaSig( lower[L-2], lower[L-1] , P[i] ) <= 0LL )
			L--;
		lower[L++] = P[i];
	}

	point upper[ P.size() + 2 ];
	upper[ 0 ] = P[ P.size() - 1 ]; upper[1] = P[ P.size() - 2 ];
	int U = 2;

	for ( int i=P.size() - 3; i >= 0 ; --i ){
		while ( U > 1 && areaSig( upper[U-2] , upper[U-1], P[i] ) <= 0LL )
			U--;
		upper[U++] = P[i];
	}

	for ( int i=1; i < U ; ++i )
		lower[L++] = upper[i];

	return vector<point>(lower , lower + L);
}

int main(){

	int n;

	while ( cin >> n && n > 2 ){
		vector<point> P(n);
		for ( int i=0; i<n; ++i ){
			cin >> P[i].x >> P[i].y;
		}

		//for ( int i=0; i < n; ++i ) cout << P[i].x << " , " << P[i].y << endl;

		vector<point> hull = monotone_chain( P );

		long long X = 0;
		long long Y = 0;
		long long A = 0;
		long long tmp;
		for ( int i=0; i < hull.size() - 1; ++i ){
			tmp = (hull[i].x * hull[i+1].y - hull[i+1].x * hull[i].y);
			X += (hull[i].x + hull[i+1].x)*tmp;
			Y += (hull[i].y + hull[i+1].y)*tmp;
			A += tmp;
		}
		double cx = X / (3.0 * A);
		double cy = Y / (3.0 * A);
		printf("%0.3lf %0.3lf\n",cx,cy);
	}

	return 0;
}


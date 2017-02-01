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

struct point {
	int x,y;
	point(){}
	point(int X,int Y){ x = X, y = Y; }
	bool operator< ( const point &that ) const {
		return ( x != that.x )? (x < that.x) : (y < that.y);
	}
};

vector<point> read_points( int S ){
	int x1,x2,y1,y2;
	point R[ 4*S + 3 ];
	int s = 0;
	for ( int i=0; i < S; ++i ){
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		R[ s++ ] = point( x1 , y1 );
		R[ s++ ] = point( x1 , y2 );
		R[ s++ ] = point( x2 , y1 );
		R[ s++ ] = point( x2 , y2 );
	}
	return vector<point>( R , R + s );
}

int direction( point &a , point &b , point &c ){
	// returns: -1 , if its a left turn
	//			 1 , if its a right turn
	//			 0 , colinear
	int res = (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y );
	if ( res < 0 ) return -1;
	if ( res ) return 1;
	return 0;
}

vector<point> monotone_chain( vector<point> &P ){
	sort( all(P) );
	point upper[ P.size() + 2 ];
	point lower[ P.size() + 2 ];
	int N = 2;
	int M = 2;
	upper[0] = P[0]; upper[1] = P[1];
	lower[0] = P.back(); lower[1] = P[ P.size() - 2 ];
	//Construct upper hull
	for ( int i=2; i < P.size(); ++i ){
		while ( N > 1 && direction( upper[N-2] , upper[N-1] , P[i] ) <= 0 )
			N--;
		upper[N++] = P[i];
	}
	//Construct lower hull
	for ( int i=P.size() - 3; i >= 0 ; --i ){
		while ( M > 1 && direction( lower[M-2] , lower[M-1] , P[i] ) <= 0 )
			M--;
		lower[M++] = P[i];
	}
	
	for ( int i=1; i < M; ++i ) upper[N++] = lower[i];

	return vector<point>( upper , upper + N );

}

bool point_in_poly( vector<point> &P , point &p ){
	//Uses the winding number
	int wn = 0;
	for ( int i=0; i < (P.size() - 1); ++i ){
		if ( P[i].y <= p.y ){
			if ( P[i+1].y > p.y && direction( P[i] , P[i+1] , p ) > 0 )
				wn++;
		}
		else if ( P[i+1].y < p.y && direction( P[i] , P[i+1] , p ) < 0 ){
			wn--;
		}
	}
	return (wn != 0);
}

bool on_seg( point &a , point &b , point &c ){
	//Precond : points a , b , c are colinear
	return  (min( a.x , b.x ) <= c.x && max( a.x , b.x ) >= c.x) &&
			(min( a.y , b.y ) <= c.y && max( a.y , b.y ) >= c.y);	
}

bool intersect( point &X1 , point &X2 , point &Y1 , point &Y2 ){
	
	int d1 = direction( X1 , X2 , Y1 );
	int d2 = direction( X1 , X2 , Y2 );
	int d3 = direction( Y1 , Y2 , X1 );
	int d4 = direction( Y1 , Y2 , X2 );

	if ( d1*d2 < 0 && d3*d4 < 0 ) return true;
	if ( d1 == 0 && on_seg( X1 , X2 , Y1 ) ) return true;
	else if ( d2 == 0 && on_seg( X1 , X2 , Y2 ) ) return true;
	else if ( d3 == 0 && on_seg( Y1 , Y2 , X1 ) ) return true;
	else if ( d4 == 0 && on_seg( Y1 , Y2 , X2 ) ) return true;
	
	return false;
}

bool intersect( vector<point> &D, vector<point> &P ){
	//Check for point in polygon
	for ( int i=0; i < (D.size() - 1); ++i )
		if ( point_in_poly( P , D[i] ) ) return true;

	for ( int i=0; i < (P.size() - 1); ++i )
		if ( point_in_poly( D , P[i] ) ) return true;

	//Check for segment intersection
	for ( int i=0; i < (D.size() - 1); ++i )
		for ( int j = 0; j < (P.size() - 1); ++j )
			if ( intersect( D[i], D[i+1] , P[j] , P[j+1] ) )
				return true;
				
	return false;
}

int main(){
	int N,M;
	int runs = 0;
	while ( scanf("%d %d",&N,&M) && N ){
		runs++;
		vector<point> A;
		vector<point> B;
		
		A = read_points( N );
		B = read_points( M );
	
		vector<point> D = monotone_chain( A );
		vector<point> P = monotone_chain( B );
		
		if (runs > 1) puts("");
		printf("Case %d: ",runs);
		if ( intersect( D , P ) )
			puts("It is not possible to separate the two groups of vendors.");
		else 
			puts("It is possible to separate the two groups of vendors.");
	}
	return 0;
}


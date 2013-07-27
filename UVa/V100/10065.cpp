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


inline int areaSig( point &a, point &b, point &c ){
	return (b.x - a.x)*( c.y - a.y ) - ( c.x - a.x )*( b.y - a.y ); 
}

vector<point> monotone_chain( vector<point> &P ){

	sort( all(P) );

	point lower[ P.size() + 2 ];
	lower[0] = P[0]; lower[1] = P[1];
	int L = 2;

	for ( int i=2; i < P.size() ; ++i ){
		while ( L > 1 && areaSig( lower[L-2], lower[L-1] , P[i] ) <= 0 )
			L--;
		lower[L++] = P[i];
	}

	point upper[ P.size() + 2 ];
	upper[0] = P[ P.size() - 1 ]; upper[1] = P[ P.size() - 2 ];
	int U = 2;

	for ( int i=P.size() - 3; i>=0 ; --i ){
		while ( U > 1 && areaSig( upper[U-2] , upper[U-1] , P[i] ) <= 0 )
			U--;
		upper[U++] = P[i];
	}
	for ( int i=1; i < (U-1); ++i )
		lower[L++] = upper[i];
	return vector<point>(lower , lower + L);
}

int main(){

	int runs = 0;
	int n;
	while ( scanf("%d",&n) && n > 2 ){
		runs++;
		vector< point > P(n);
		for ( int i=0; i < n; ++i )
			scanf("%d %d",&P[i].x,&P[i].y);
		
		long long A1 = 0;
		for ( int i=0; i < n; ++i ){
			A1 += (P[i].x*P[(i+1)%n].y - P[(i+1)%n].x*P[i].y);
		}
		A1 = abs(A1);
		
		vector<point> H = monotone_chain(P);
		
		n = H.size();
		long long A2 = 0;
		for ( int i=0; i < n; ++i ){
			A2 += (H[i].x*H[(i+1)%n].y - H[(i+1)%n].x*H[i].y);
		}
		A2 = abs(A2);
		printf("Tile #%d\n",runs);
		printf("Wasted Space = %.2lf %%\n\n",((A2 - A1)*100.0)/A2);
	}
	return 0;
}


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
	bool operator<(const point &that) const {
		return (x == that.x)? (y < that.y):(x < that.x);
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

	for ( int i=2; i < P.size(); ++i ){
		while ( L > 1 && areaSig( lower[L-2] , lower[L-1] , P[i] ) <= 0 )
			L--;
		lower[ L++ ] = P[i];
	}

	point upper[ P.size() + 2 ];
	upper[0] = P[ P.size() - 1 ]; upper[1] = P[ P.size() - 2 ];
	int U = 2;

	for ( int i=P.size() - 3; i >= 0 ; --i ){
		while ( U > 1 && areaSig( upper[U-2] , upper[U-1] , P[i] ) <= 0 )
			U--;
		upper[U++] = P[i];
	}

	for ( int i=1; i < (U-1) ; ++i )
		lower[L++] = upper[i];

	return vector<point>(lower, lower + L);
}

int main(){
	int runs;
	int n;
	scanf("%d",&runs);
	printf("%d\n",runs);
	while ( runs-- ){
		scanf("%d",&n);
		vector<point> P(n);
		for ( int i=0; i < n; ++i )
			scanf("%d %d",&P[i].x,&P[i].y);
		
		if ( P[0].x == P.back().x && P[0].y == P.back().y )
			P.pop_back();
		
		vector<point> res = monotone_chain(P);
		
		int idx = 0;
		for ( int i=1; i < res.size(); ++i ){
			if ( res[i].y < res[idx].y || ( (res[i].y == res[idx].y) && (res[i].x < res[idx].x) ) )
				idx = i;
		}
		
		printf("%d\n",(int)res.size() + 1);
		n = res.size();
		for ( int i=0; i < res.size(); ++i ){
			printf("%d %d\n",res[ (idx + i)%n ].x, res[ (idx + i)%n ].y);
		}
		printf("%d %d\n",res[ idx ].x, res[ idx ].y);
		if ( runs ){ puts("-1"); scanf("%d",&n); }
	}
	return 0;
}


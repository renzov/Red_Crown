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

const double EPS = 0.00001;

int comp( double x,double y ){
	if ( fabs(x - y) < EPS ) return 0;
	if ( x < y ) return -1;
	return 1;
}

bool isletter( double *a ){
	if ( comp( a[2] , 125.0 ) < 0 || comp( a[2] , 290.0 ) > 0 ) return false;
	if ( comp( a[1] , 90.0 ) < 0 || comp( a[1] , 155.0 ) > 0 ) return false;
	if ( comp( a[0] , 0.25 ) < 0 || comp( a[0] , 7.0 ) > 0 ) return false;
	return true;
}

bool ispacket( double *a ){
	if ( comp( a[2] , 125.0 ) < 0 || comp( a[1] , 90.0 ) < 0 || comp(a[0] , 0.25) < 0 ) return false;
	if ( comp( a[2] , 380.0 ) > 0 || comp( a[1] , 300.0 ) > 0 || comp(a[0] , 50.0) > 0 ) return false;
	return true;
}

bool isparcel( double *a ){
	if ( comp( a[2] , 125.0 ) < 0 || comp( a[1] , 90.0 ) < 0 || comp(a[0] , 0.25) < 0 ) return false;
	if ( comp( a[2] + 2*(a[1] + a[0]) , 2100.0 ) > 0 ) return false;
	return true;
}

int main(){
	double a[3];
	while ( scanf("%lf %lf %lf",a,a+1,a+2) ){
		sort( a , a + 3 );
		if ( comp( a[0], 0.0 ) == 0 ) break;
		if ( isletter( a ) ) puts("letter");
		else if ( ispacket(a) ) puts("packet");
		else if ( isparcel(a) ) puts("parcel");
		else puts("not mailable");
	}
	return 0;
}


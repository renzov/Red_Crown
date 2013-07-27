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
const double INF = 10e10;
typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int main(){

	int n;
	double y1,y2,x1,x2;
	double x,y;

	while ( scanf("%d",&n) && n > 0 ){
		x1 = y1 = INF;
		x2 = y2 = -INF;
		for ( int i=0; i < n; ++i ){
			scanf("%lf %lf",&x,&y);
			x1 = min( x1 , x );
			x2 = max( x2 , x );
			y1 = min( y1 , y );
			y2 = max( y2 , y );
		}
		printf("%0.4lf\n",fabs(x1 - x2)*fabs(y1 - y2));
	}
	return 0;
}


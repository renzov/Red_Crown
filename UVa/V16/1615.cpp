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

const double EPS = 10e-8;

inline bool equal( double a, double b ){
	return fabs(a-b) < EPS;
}

int main(){
	int D,N;
	double L;
	double x,y;
	double width;

	while ( scanf("%lf %d %d", &L, &D, &N) != EOF ){
		vector< pair<double, double> > I;		
		for ( int i=0; i < N; ++i ){
			scanf("%lf %lf", &x, &y);
			width = sqrt( D*D - y*y );
			I.push_back( mp( min(x + width, L) , max(x - width, 0.0) ) );
		}
		sort( all(I) );
		int res = 1;
		double last = I[0].first;
		for ( int i=1; i < N; ++i ){
			if ( !equal(I[i].second, last) && I[i].second > last ){
				res++;
				last = I[i].first;
			}
		}
		printf("%d\n",res);
	}

	return 0;
}


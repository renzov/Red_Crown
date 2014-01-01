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
const double EPS = 1e-12;
const int MAXN = 25;

int main(){

	int n;
	long long a[MAXN];
	double x;

	while ( scanf("%d",&n) && n ){
		for ( int i=0; i < n; ++i ){
			scanf("%lf",&x);
			a[i] = (long long)floor( x * 1000.0 + EPS );
		}
		if ( n < 2 ) puts("NO");
		else {
			sort( a , a + n );
			long long s = a[0] + a[1];
			bool ok = a[1] == a[0];
			for ( int i=2; !ok && i < n ; ++i ){
				ok = s >= a[i];
				s += a[i];
			}
			if (ok) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}

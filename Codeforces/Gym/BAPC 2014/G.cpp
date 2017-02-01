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

long long inline eval( const long long &a, const long long &b, const long long &c ){
	return b*b + 4*a*c;
}

int main(){
	
	int runs;
	long long a1,b1,c1,a2,b2,c2;
	int res;
	int n;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &n);
		scanf("%lld %lld %lld",&a1, &b1, &c1);
		res = 1;
		for ( int i=1; i < n; ++i ){
			scanf("%lld %lld %lld", &a2, &b2, &c2);
			if ( eval(a1, b1, c1)*a2 < eval(a2, b2, c2)*a1  ){
				res = i+1;
				a1 = a2, b1 = b2, c1 = c2;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}


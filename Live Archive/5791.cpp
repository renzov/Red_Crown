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

const int MAXF = 100005;
int C[MAXF];
int F;

long long count_pack( const long long &size, const long long &sum  ){
	if ( size < 2 || sum % size ) return 0;
	long long m = ( C[0] - size - size / F) % size;
	long long small = 1LL << 60;
	long long left;
	for ( int i=0; i < F; ++i ){
		left = C[i] - size - size/F;
		if ( left < 0 || left % size != m ) return 0;
		if ( left < small ) small = left;
	}
	return small / size + 1;
}

long long solve ( const long long &sum, const int &g ){
	long long res = 0;
	for ( long long d=1; d*d <= g; ++d ){
		if ( g % d == 0 ){
			res += count_pack( d * F, sum );
			if ( g / d != d ) res += count_pack( g / d * F, sum );
		}
	}
	return res;
}

int main(){
	int g;
	while ( scanf("%d", &F) && F ){
		for ( int i=0; i < F; ++i )
			scanf("%d", C + i);
		
		long long sum = 0;
		g = C[0];
		
		for ( int i=0; i < F; ++i ){
			sum += C[i];
			g = __gcd( C[i] , g );
		}
		
		if ( sum % F == 0 )
			printf("%lld\n", solve( sum, g ));
		else 
			puts("0");
	}
	return 0;
}


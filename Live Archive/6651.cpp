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

int solve( const long long &zero, const long long &one, const long long &two ){
	long long diff = one < two? two - one:one - two;
	int inv = ( zero & 1 )? 2:1;
	int other = 3 - inv;
	if ( !one && !two ) return zero ? 2:0;
	if ( !one || !two ) return one > 2 || two > 2 ? other:0;
	if ( diff == 0 ) return inv;
	if ( diff <= 2 ) return ( inv == 1 )? 1 : 0;
	return 1;
}

int main(){
	int N;
	int runs;
	int cases = 0;
	long long L, B;

	scanf("%d", &runs);
	while ( runs-- ){
		
		long long zero = 0;
		long long one = 0;
		long long two = 0;

		scanf("%d", &N);
		while ( N-- ){
			scanf("%lld %lld", &L, &B);
			int mod = (int)( B % 3 );
			switch ( mod ){
				case 0 : zero += (B - 1)*(L - 1); break;
				case 1 : one += (B - 1)*(L - 1); break;
				case 2 : one += ((L - 1) / 2) * (B - 1); 
						 two += (L / 2) * (B - 1); break; 
			}		
		}
		int res = solve( zero, one, two );
		switch ( res ){
			case 0 : printf("Case %d: Draw\n", ++cases); break;
			case 1 : printf("Case %d: M\n", ++cases); break;
			case 2 : printf("Case %d: J\n", ++cases); break;
		}
	}
	return 0;
}


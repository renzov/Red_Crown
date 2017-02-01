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

const int MAXS = (1 << 16) + 5;

int N;
long long dp[MAXS];
int def[MAXS];
int M[20];

int main(){

	char s[20];

	int runs,cases = 0;
	scanf("%d",&runs);
	
	while ( runs-- ){
		cases++;
		scanf("%d",&N);

		for ( int i=0 ; i <= N ; ++i ){
			scanf("%s",s);
			M[i] = 0;
			for ( int j=0; s[j]; ++j ){
				if ( s[j] == '1' )
					M[i] |= ( 1 << j );
			}
		}
		def[0] = M[0];
		for ( int i=1; i < (1<<N) ; ++i ){
			dp[i] = 0;
			def[i] = M[0];
			for ( int j=0; j < N; ++j )
				if ( (i >> j)&1 ){
					def[i] |= M[j+1];
				}
		}

		dp[0] = 1;

		for ( int i=0; i < (1<<N) - 1; ++i ){
		
			if ( dp[i] > 0 ){
			
				for ( int j=0; j < N; ++j ){
					if ( !((i >> j)&1) && (def[ i ] >> j)&1 ){
						dp[ i | ( 1 << j ) ] += dp[i];
					}
				}

			}
		
		}
		printf("Case %d: %lld\n",cases,dp[(1<<N)-1]);
	}

	return 0;
}


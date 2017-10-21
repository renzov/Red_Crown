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
#include <climits>

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

int d[16];
bool dp[2][16][128];

int main(){
	int runs;
	scanf("%d", &runs);
	int sum;
	int N;
	while ( runs-- ){
		N = sum = 0;
		for ( int i=1; i < 10; ++i ){	
			scanf("%d", d+i);
			N += d[i];
			sum += i * d[i];
		}
		for ( int i=0; i < 11; ++i ){
			fill( dp[0][i] , dp[0][i] + 103, false );
			fill( dp[1][i] , dp[1][i] + 103, false );
		}
		dp[0][0][0] = true;
		int last = 0;
		for ( int i=1; i < 10; ++i ){
			for ( int j=0; j < d[i]; ++j ){
				
				for ( int k=0; k < 11; ++k )
					for ( int l=0; l < N; ++l ){
						if ( dp[last][k][l] ){
							dp[1-last][k][l] = true;
							dp[1-last][ (k + i)%11 ][ l + 1 ] = true;
						}
					}

				last = 1 - last;
			}
		}
		int mod = sum % 11;
		int m;
		int res = INT_MAX;
		int cnt;

		// Look for the best response
		for ( int i=0; i < 11; ++i ){
			for ( int j=1; j <= N; ++j ){
				if ( dp[last][i][j] ){ // There is a set of j elements whose sum is i (mod 11)
					m = ( i < 6 )? 2*i:(2*i - 11); 					
					if ( m == mod ){ // A candidate solution
						cnt = max( N - 2*j, 2*j - N );
						if ( cnt > 0 ) cnt--;
						res = min( res, cnt );
					}
				}
			}
		}
		printf("%d\n", ( res == INT_MAX )? -1:res + N );
	}
	return 0;
}


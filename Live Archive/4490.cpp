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
const int INF = 1000000;

int h[105];
int dp[2][102][1<<8][9];
int bits[1<<8] = {0};

void init(){
	for ( int i=1; i < (1<<8); ++i )
		bits[ i ] = __builtin_popcount(i);
}

int main(){

	int N,K;
	int runs = 0;
	int mask;

	init();

	while ( scanf("%d %d",&N,&K) && (N + K) ){
		runs++;
		mask = 0;
		for ( int i=1; i <= N; ++i ){
			scanf("%d",h+i);
			h[i] -= 25;
			mask |= ( 1 << h[i] ); 
		}
		
		//init
		for ( int j=0; j <= K; ++j )
			for ( int m = 0; m < ( 1 << 8 ); ++m )
				for ( int c = 0; c <= 8; ++c )
					dp[0][j][m][c] = INF;

		dp[0][0][0][8] = 0;

		int x = 0;
		int y = 1;

		for ( int i=1; i <= N ; ++i ){
			
			for ( int j=0; j <= K; ++j ){
				for ( int m=0; m < (1<<8); ++m ){
					for ( int c=0; c <= 8; ++c ){
						dp[y][j][m][c] = INF;
					}
				}
			}

			for ( int j=0; j < i && j <= K; ++j ){
				for ( int m=0; m < (1<<8); ++m ){
					for ( int c=0; c <= 8; ++c ){
						
						if ( dp[x][j][m][c] == INF ) continue;
						
						if ( j < K ){
							dp[y][j + 1][m][c] = min( dp[y][j+1][m][c] , dp[x][j][m][c] );
						}

						if ( h[i] == c ){
							dp[y][j][m][c] = min( dp[y][j][m][c] , dp[x][j][m][c] ); 
						}
						else {
						 	dp[y][j][ (1<<h[i]) | m ][ h[i] ] = min( dp[y][j][ (1<<h[i]) | m ][ h[i] ] , dp[x][j][m][c] + 1 ); 
						}

					}
				}
			}

			y = x;
			x = 1 - x;
		}

		int res = INF;

		for ( int j=0; j <= K; ++j ){
			for ( int m=0; m < (1<<8); ++m ){
				for ( int c=0; c <= 8; ++c ){
					if ( dp[x][j][m][c] < INF ){
						res = min( res , dp[x][j][m][c] + bits[ m ^ mask ] );
					}
				}
			}
		}
		printf("Case %d: %d\n\n",runs,res);
	}
	return 0;
}

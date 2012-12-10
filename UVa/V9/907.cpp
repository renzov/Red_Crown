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
int d[ 605 ][ 605 ];
int dp[ 605 ][ 400 ];

int main(){

	int N,K;

	while ( scanf("%d %d",&N,&K) == 2 ){
		for ( int i=0; i <= N; ++i ) scanf("%d",&d[i][i+1]);
		N++;
		for ( int k=2; k <= N; ++k){
			for ( int i=0; (i + k) <= N; ++i ){
				d[i][i + k] = d[i][i + k - 1] + d[i+k-1][i+k];
			}
		}

		dp[0][0] = 0;
		for ( int i=1; i <= N; ++i ){
			dp[i][1] = d[0][i];
		}
		K++;
		for ( int j=2; j <= K ; ++j ){
			for ( int i=j; i <= N ; ++i ){
				dp[i][j] = INT_MAX;
				for ( int k=j-1; k < i ; ++k ){
					dp[i][j] = min( dp[i][j] , max( dp[k][j-1] , d[k][i] ) );
				}
			}
		}
		printf("%d\n",dp[N][K]);
	}
	return 0;
}


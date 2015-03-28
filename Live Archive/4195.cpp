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
const int MAXN = 1005;

int V[MAXN];
int sum[MAXN][MAXN];
int SV[MAXN][MAXN];
int dp[MAXN][MAXN];

inline int Min(int x, int y){ return x < y? x:y; }

int main(){

	int N,M;

	while ( scanf("%d %d",&N,&M) && N ){
		for (int i=0; i < N; ++i) scanf("%d",V+i);
		/* Precalculation of strategic value */
		for ( int i=0; i < N; ++i ){
			sum[i][i] = V[i];
			SV[i][i] = 0;
			for ( int j=i+1; j < N ; ++j ){
				sum[i][j] = sum[i][j-1] + V[j];
				SV[i][j] = SV[i][j-1] + V[j] * sum[i][j-1];
			}
		}

		for ( int i=0; i < N; ++i ){	
			dp[i][0] = SV[0][i];
			for ( int j = 1; j <= M; ++j ){
				if ( j >= i ){
					dp[i][j] = 0;
					continue;
				}
				dp[i][j] = dp[i][j-1];
				for ( int k = i-1; k >= 0 && dp[i][j] > SV[k+1][i] ; --k ){
					dp[i][j] = Min( dp[i][j] , dp[k][j-1] + SV[k+1][i] );
				}
			}
		}
		printf("%d\n",dp[N-1][M]);
	}
	return 0;
}


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
const int MAXN = 505;

int R[MAXN][MAXN] = {0};
int C[MAXN][MAXN] = {0};

int dp[MAXN][MAXN] = {0};

int main(){
	int val;
	int N,M;
	while ( scanf("%d %d",&N,&M) && N && M ){
		for ( int i=1; i <= N; ++i )
			for ( int j=1; j <= M; ++j ){
				scanf("%d",&val);
				R[i][j] = R[i][j-1] + val;
			}
		for ( int i=1; i <= N; ++i )
			for ( int j=1; j <= M; ++j ){
				scanf("%d",&val);
				C[i][j] = C[i-1][j] + val;
			}
		
		for ( int i=1; i <= N; ++i )
			for ( int j=1; j <= M; ++j )
				dp[i][j] = max( R[i][j] + dp[i-1][j] , C[i][j] + dp[i][j-1] );

		printf("%d\n",dp[N][M]);
	}

	return 0;
}


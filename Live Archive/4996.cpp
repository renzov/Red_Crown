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

const int MAXN = 1000;

long long dp[MAXN + 5][2];

int main(){
	int runs;
	int n, x, y, z;

	scanf("%d", &runs);
	for ( int cases = 1; cases <= runs ; ++cases ){
		scanf("%d %d %d %d", &n, &x, &y, &z);
		
		dp[1][0] = 0;
		dp[1][1] = -(x/2);
		
		for ( int i=2; i <= n; ++i ){
			dp[i][0] = INT_MAX;
			dp[i][1] = INT_MAX;
			for ( int j=1; j < i; ++j ){
				dp[i][0] = min( dp[i][0] , max( dp[j][0] , dp[i-j][1] ) );
				dp[i][1] = min( dp[i][1] , max( dp[j][0] , dp[i-j][1] ) );
			}
			dp[i][0] += (y + x);
			dp[i][1] += z;
		}
		printf("Case %d: %lld\n", cases , dp[n][0] );
	}
	return 0;
}


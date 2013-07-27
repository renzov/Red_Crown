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

int dp[305][305];

int main(){
	
	dp[1][1] = 0;
	
	for ( int i=2; i <= 300 ; ++i )
		dp[i][1] = i-1; 

	for ( int i=2; i <= 300 ; ++i ){
		for (int j=2; j <= i ; ++j){
			dp[i][j] = INT_MAX;
			for ( int k = 1; k < j ; ++k ){
				dp[i][j] = min( dp[i][j] , dp[i][k] + dp[i][j - k] + 1 );
			}
		}
	}
	
	int n,m;

	while ( scanf("%d %d",&m,&n) == 2 ){
		if (m < n) swap( m , n );
		printf("%d\n",dp[m][n]);
	}

	return 0;
}


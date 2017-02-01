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

const int MAXN = 2005;
const int MAXD = 25;

int p[MAXN];
int sum[MAXN] = {0};
int N, D;

int dp[MAXN][MAXD];

inline int val( int x ){
	return ((x+5)/10)*10;
}

int main(){

	while ( scanf("%d %d", &N, &D) != EOF ){
		D = min( D, N - 1 );
		for ( int i=1; i <= N; ++i ){ 
			scanf("%d", p + i); 
			sum[i] = sum[i-1] + p[i];
			dp[i][0] = val(sum[i]);
		}
		for ( int j=1; j <= D; ++j ){
			for ( int i=j+1; i <= N; ++i ){
				dp[i][j] = dp[i][j-1];
				for ( int l=i-1; l >= j; --l ){
					dp[i][j] = min( dp[l][j-1] + val(sum[i] - sum[l]), dp[i][j] );
				}
			}
		}
		printf("%d\n", dp[N][D]);
	}
	return 0;
}


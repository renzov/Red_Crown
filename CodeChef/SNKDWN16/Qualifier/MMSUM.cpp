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

const int MAXN = 100006;

long long A[MAXN];
long long dp[MAXN][2];
int main(){
	int runs;
	int N;
	long long res;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ) scanf("%lld", A+i);
		dp[0][0] = A[0];
		dp[0][1] = -10000000000LL;
		for ( int i=1; i < N; ++i ){
			dp[i][0] = max( dp[i-1][0] + A[i], A[i] );
			dp[i][1] = max( dp[i-1][1] + A[i], dp[i-1][0] );
		}
		res = A[0];
		for ( int i=1; i < N; ++i ) res = max( res, max(dp[i][0], dp[i][1]) );
		printf("%lld\n", res);
	}
	return 0;
}


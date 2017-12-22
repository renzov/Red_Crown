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

const int MAXN = 128;
int A[MAXN];
long long dp[MAXN][MAXN];

int main(){
	int N, M;
	int runs;
	int cases = 0;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		for ( int i=0; i < N; ++i )
			scanf("%d", A+i );

		sort( A , A + N );
		for ( int i=0; i < N; ++i )
			dp[i][1] = A[i] - A[0];

		for ( int j=2; j <= M; ++j ){
			for ( int i=j-1; i < N; ++i ){
				dp[i][j] = LLONG_MAX;
				for ( int k=i-1; k >= j-2; --k ){
					dp[i][j] = min( dp[i][j] , dp[k][j-1] + ( A[i] - A[k+1] ) );
				}
			}
		}
		printf("Case #%d: %lld\n", ++cases, dp[N-1][M]);
	}
	return 0;
}


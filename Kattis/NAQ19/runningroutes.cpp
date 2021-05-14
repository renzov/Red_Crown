#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;

int N;
int M[MAXN][MAXN];
int dp[MAXN][MAXN];

int main(){
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			scanf("%d", M[i] + j);
	
	int l, r;

	for ( l=0; l < N; ++l ){
		r = l + 1;
		dp[l][r] = M[l][r % N];
	}
	
	for ( int len=2; len < N; ++len )
		for ( l=0; l < N; ++l ){
			r = l + len;
			dp[l][r] = dp[l + 1][r - 1] + M[l][r % N];
			for ( int m=l+1; m <= r - 1; ++m ){
				dp[l][r] = max( dp[l][r], dp[l][m] + dp[m + 1][r] );
				dp[l][r] = max( dp[l][r], dp[m][r] + dp[l][m - 1] );
			}
		}

	int res = 0;
	for ( l = 0; l < N; ++l )
		res = max( res, dp[ l ][ l + N - 1 ] );
	printf("%d\n", res);
	return 0;
}

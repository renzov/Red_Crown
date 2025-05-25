#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 505;

int dp[MAXN][MAXN];

int main(){
	int N, M;
	
	scanf("%d %d", &N, &M);
	if ( M < N ) swap( N, M );
	// N <= M
	for ( int j = 1; j <= M; ++j )
		dp[j][1] = dp[1][j] = j - 1;
	for ( int i = 2; i <= N; ++i )
		dp[i][i] = 0;

	for ( int i = 2; i <= N; ++i )
		for ( int j = i + 1; j <= M; ++j ){
			dp[i][j] = INT_MAX;
			// first try vertical cut
			for ( int k = 1; k < j; ++k )
				dp[i][j] = min( dp[i][j], dp[i][k] + dp[i][j - k] + 1 );
			// now try horizontal cut
			for ( int k = 1; k < i; ++k )
				dp[i][j] = min( dp[i][j], dp[k][j] + dp[i - k][j] + 1 );
	
			dp[j][i] = dp[i][j];
		}

	printf("%d\n", dp[N][M]);
	return 0;
}

#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 300005;

int N;
int T[MAXN];
int ord[3] = {0, 1, 2};
int dp[3][MAXN];

int solve(){

	dp[2][N - 1] = T[N - 1] == ord[2]? 1:0;
	dp[1][N - 1] = max( dp[2][N - 1], T[N - 1] == ord[1]? 1:0 );
	dp[0][N - 1] = max( dp[1][N - 1], T[N - 1] == ord[0]? 1:0 );

	for ( int i = N - 2; i >= 0; --i ){
		dp[2][i] = dp[2][i + 1] + ( T[i] == ord[2] ? 1:0 );
		dp[1][i] = max( dp[2][i] , dp[1][i + 1] + (T[i] == ord[1]? 1:0 ) );
		dp[0][i] = max( dp[1][i] , dp[0][i + 1] + (T[i] == ord[0]? 1:0 ) );
	}
	return dp[0][0];
}

int main(){

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d", T + i );
	
	int ans = INT_MIN;
	// Test every possible permutation of the tools
	do {
		ans = max( ans, solve() );	
	}
	while ( next_permutation( ord, ord + 3 ) );
	printf("%d\n", ans);
	return 0;
}

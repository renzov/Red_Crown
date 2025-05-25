#include<cstdio>
using namespace std;
const int MOD = 1000000007;
const int MAXN = 100005;

int dp[2][128];		// dp[i][j] = number of ways to fill array X[0 ... i ] such that the last 
int X[MAXN];		// element is j

int main(){
	int N, M;

	scanf("%d %d", &N, &M );
	for ( int i = 0; i < N; i++ )
		scanf("%d", X + i );

	int prev = 0;
	int act = 1;
	// Initialize the dp table
	if ( X[0] ){
		for ( int i = 1; i <= M; ++i )
			dp[prev][i] = (i == X[0])? 1:0;
	}	
	else {
		for ( int i = 1; i <= M; ++i )
			dp[prev][i] = 1;
	}
	
	if ( M == 1 ){
		puts("1");
	}
	else {	// M >= 2
		for ( int i = 1; i < N; ++i ){
			if ( !X[i] ){
				for ( int j = 1; j <= M; ++j ){
					dp[act][j] = dp[prev][j];
					dp[act][j] += dp[prev][j - 1], dp[act][j] %= MOD;
					dp[act][j] += dp[prev][j + 1], dp[act][j] %= MOD;
				}
			}
			else {
				for ( int j = 1; j <= M; ++j )
					if ( X[i] != j ) dp[act][j] = 0;
					else {
						dp[act][j] = dp[prev][j];
						dp[act][j] += dp[prev][j - 1], dp[act][j] %= MOD;
						dp[act][j] += dp[prev][j + 1], dp[act][j] %= MOD;
					}
			}
			act ^= 1;
			prev ^= 1;
		}
		int res = 0;
		if ( X[N - 1] ) res = dp[prev][ X[N - 1] ];
		else {
			for ( int j = 1; j <= M; ++j )
				res += dp[prev][j], res %= MOD;
		}
		printf("%d\n", res);
	}
	return 0;
}

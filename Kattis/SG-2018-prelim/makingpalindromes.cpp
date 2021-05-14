#include<cstdio>
using namespace std;
const int MAXN = 256;
const int MOD = 1000000007;

int N;
char S[MAXN];
long long dp[MAXN][MAXN][MAXN];
long long E[MAXN];
int main(){

	scanf("%d", &N);

	if ( N == 0 ){
		puts("1");
		return 0;
	}

	scanf("%s", S);

	// The empty substring
	E[0] = 1LL;
	for ( int k=1; k <= N; ++k ){
		E[k] = E[k - 1] * 26;
		E[k] %= MOD;	
	}	

	int j;
	for ( int len=1; len <= N; ++len ){
		for ( int i=0; (i + len - 1) < N; ++i ){
			j = i + len - 1;
			for ( int k=1; k <= N; ++k ){
				dp[i][j][k] = 0;
				if ( S[i] == S[j] ){
					if ( i + 1 <= j - 1 ){
						dp[i][j][k] = dp[i + 1][j - 1][k - 1] + 25LL * dp[i][j][k - 1];
						dp[i][j][k] %= MOD;
					}
					else {
						dp[i][j][k] = E[k - 1] + 25LL * dp[i][j][k - 1];
						dp[i][j][k] %= MOD;
					}
				}
				else {
					dp[i][j][k] = dp[i][j - 1][k - 1] + dp[i + 1][j][k - 1] + 24 * dp[i][j][k - 1];
					dp[i][j][k] %= MOD;
				}
			}
		}
	}
	printf("%lld\n", dp[0][N - 1][N]);
	return 0;
}

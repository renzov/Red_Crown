#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD = 1000000007;
const int MAXN = 50005;
const int MAXC = 305;
int dp[2][2][MAXC] = {0};	// dp[i][k][j] = # of sequences of size i where the last j elements have color k
int sz[2];

int main(){

	int N;
	int prev, act;
	scanf("%d %d %d", &N, sz, sz + 1 );

	prev = 0;
	act = 1;
	dp[prev][0][1] = dp[prev][1][1] = 1;
	for ( int i = 2; i <= N; ++i ){	
		// for each possible song type
		for ( int k = 0; k < 2; ++k ){
			fill( dp[act][k], dp[act][k] + (sz[k] + 1), 0 );
			// calculating dp[i][k][j] for j >= 2
			for ( int j = 2; j <= min(i, sz[k]); ++j ){
				dp[act][k][j] += dp[prev][k][j - 1];
				dp[act][k][j] %= MOD;
			}
			// calculating dp[i][k][1], a new run of songs
			for ( int j = 1; j <= min( i, sz[k ^ 1] ); ++j ){
				dp[act][k][1] += dp[prev][k ^ 1][j];
				dp[act][k][1] %= MOD;
			}
		}
		swap(act, prev);
	}
	// calculating the answer	
	int res = 0;
	for ( int k = 0; k < 2; ++k ){
		for ( int j = 1; j <= sz[k]; ++j ){
			res += dp[prev][k][j];
			res %= MOD;
		}
	} 
	printf("%d\n", res);
	return 0;
}

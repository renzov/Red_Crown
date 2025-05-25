#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 405;
int A[MAXN];
int M[MAXN][MAXN];	// M[i][j] = maximum in the subarray A[i ... j]
int S[MAXN][MAXN];	// S[i][j] = sum of the subarray A[i ... j]

int dp[2][MAXN];	// dp[i][j] = minimum wasted space using at most i parts in the subarray A[0 ... j]
int main(){
	freopen( "snakes.in", "r", stdin );
	freopen( "snakes.out", "w", stdout );

	int N, K;

	scanf("%d %d", &N, &K);
	for ( int i = 0; i < N; ++i )
		scanf("%d", A + i );

	// precalculate the maximum of every subarray
	for ( int i = 0; i < N; ++i ){
		S[i][i] = M[i][i] = A[i];
		for ( int j = i + 1; j < N; ++j ){
			M[i][j] = max( M[i][j - 1], A[j] );
			S[i][j] = S[i][j - 1] + A[j];
		}
	}
	
	int prev = 0;
	int act = 1;
	// initialize the dp
	for ( int j = 0; j < N; ++j )
		dp[prev][j] = M[0][j] * (j + 1) - S[0][j];
	
	for ( int k = 1; k <= K; ++k ){
		dp[act][0] = dp[prev][0];
		for ( int j = 1; j < N; ++j ){
			dp[act][j] = dp[prev][j];
			for ( int l = 0; l < j; ++l ){
				dp[act][j] = min( dp[act][j], dp[prev][l] + M[l + 1][j] * (j - l) - S[l + 1][j] );
			} 
		}
		prev ^= 1;
		act ^= 1;
	}
	printf("%d\n", dp[prev][N - 1]);
	return 0;
}

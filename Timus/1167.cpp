#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 505;

int S[MAXN];	// S[i] = prefix sum from 1 to i
int dp[MAXN][MAXN];

int main(){
	
	int N, K;
	int v;
	// input
	scanf("%d %d", &N, &K);
	for ( int i = 1; i <= N; ++i ){
		scanf("%d", &v);
		S[i] = S[i - 1] + v;
	}

	// base case: only 1 part
	for ( int i = 1; i <= N; ++i )
		dp[1][i] = S[i] * ( i - S[i] );
	
	int ones, zeros;
	for ( int k = 2; k <= K; ++k ){
		for ( int i = k; i <= N; ++i ){
			// calculating dp[k][i] = minimum partition with exactly k parts considering prefix 1 ... i
			dp[k][i] = INT_MAX;
			for ( int j = k; j <= i; ++j ){ // last part of the partition is [j, j + 1, ..., i]
				ones = S[i] - S[j - 1];
				zeros = i - j + 1 - ones;
				dp[k][i] = min( dp[k][i], dp[k - 1][j - 1] + ones * zeros );
			}
		}
	}
	printf("%d\n", dp[K][N]);
	return 0;
}

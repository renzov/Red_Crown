#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int N, M, K;
char S[MAXN];
int V[MAXN];
int sum[26][MAXN];
int W[26][26];

int dp[MAXN][26]; // dp[i][c] = min cost of converting string S[1 ... i] with last char being c 
int mindp[MAXN];	

int main(){
	freopen ("cowmbat.in", "r", stdin);
	freopen ("cowmbat.out", "w", stdout);	

	scanf("%d %d %d", &N, &M, &K);
	scanf("%s", &S[1]);

	for ( int i=1; i <= N; ++i )
		V[i] = S[i] - 'a';
	for ( int i=0;  i < M; ++i )
		for ( int j=0; j < M; ++j )
			scanf("%d", &W[i][j]);

	// floyd to get the minimum distances
	for ( int k=0; k < M; ++k )
		for ( int i=0; i < M; ++i )
			for ( int j=0; j < M; ++j )
				W[i][j] = min( W[i][j] , W[i][k] + W[k][j] );
	
	// computing preffix sums
	for ( int c=0; c < M; ++c ){
		sum[c][0] = 0;
		for ( int i = 1; i <= N; ++i )
			sum[c][i] = sum[c][i - 1] + W[ V[i] ][ c ];
	}
	
	for ( int i=0; i <= N; ++i ){
		mindp[i] = INT_MAX;
		for ( int j=0; j < M; ++j )
			dp[i][j] = INT_MAX;
	}

	mindp[0] = 0;
	for ( int i=1; i <= N; ++i ){
		mindp[i] = INT_MAX;
		for ( int j=0; j < M; ++j ){
			if ( dp[i - 1][j] < INT_MAX )
				dp[i][j] = dp[i - 1][j] + W[ V[i] ][j];
			if ( i >= K && mindp[i - K] < INT_MAX )
				dp[i][j] = min( dp[i][j] , mindp[i - K] + sum[j][i] - sum[j][i - K] );
			
			mindp[i] = min( mindp[i] , dp[i][j] );
		}
	}
	printf("%d\n", mindp[N]);
	return 0;
}

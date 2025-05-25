#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 200005;

int A[MAXN];
int dp[2][MAXN];	// dp[player][i] = min number of skips in array A[i ... N - 1] if we start with player
// player = 0 (you) and player 1 (friend) - makes easy dp calculations

void process(){
	int N; 

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%d", A + i );
	
	dp[0][N] = dp[1][N] = 0;
	dp[0][N - 1] = 0;
	dp[1][N - 1] = A[N - 1];

	for ( int i = N - 2; i >= 0; --i )
		for ( int p = 0; p < 2; ++p )
			dp[p][i] = min( A[i] * p + dp[p ^ 1][i + 1], ( A[i] + A[i + 1] ) * p + dp[ p ^ 1 ][i + 2] ); 

	printf("%d\n", dp[1][0]);
}

int main(){
	int T;
	scanf("%d", &T);
	while ( T-- )
		process();
	return 0;
}

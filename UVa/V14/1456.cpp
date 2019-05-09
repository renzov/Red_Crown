#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 128;
long long U[MAXN];
long long C[MAXN][MAXN];
long long dp[MAXN][MAXN];

void process(){
	int N, K;
	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i ) scanf("%lld", U + i);
	/* Optimality criteria */
	sort( U, U + N );
	reverse(U, U + N);
	/* Partial sums of U */
	for ( int i=0; i < N; ++i ){
		C[i][i] = U[i];
		for ( int j=i+1; j < N; ++j )
			C[i][j] = C[i][j-1] + U[j];
	}
	/* Try every possible partition */
	for ( int i=0; i < N; ++i )
		dp[i][1] = C[i][N - 1] * ( N - i );

	for ( int j=2; j <= K; ++j ){
		for ( int i=0; i <= N - j; ++i ){
			dp[i][j] = LLONG_MAX;
			for ( int k=i; k <= N - j; ++k ){
				dp[i][j] = min( dp[i][j] , dp[k+1][j-1] + C[i][N-1] * (k - i + 1) );
			}
		}
	}
	printf("%.4f\n", (double)dp[0][K]/C[0][N-1] );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

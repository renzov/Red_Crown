#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
int A[MAXN];
int dp[2][3][MAXN];		// dp[k][i][j] = max wins using at most k runs in array A[0 ... j] where current run uses i

int W[3][3] = { {0, 1, 0}, {0, 0, 1}, {1, 0, 0} };

int main(){
	freopen("hps.in", "r", stdin );
	freopen("hps.out", "w", stdout );

	int N, K;
	char c;

	scanf("%d %d", &N, &K);
	for ( int i = 0; i < N; ++i ){
		scanf(" %c", &c);
		if ( c == 'H' )
			A[i] = 0;
		else if ( c == 'S' )
			A[i] = 1;
		else 
			A[i] = 2;
	}

	// Initialize dp table
	for ( int i = 0; i < 3; ++i ){
		dp[0][i][0] = W[i][ A[0] ];
		for ( int j = 1; j < N; ++j )
			dp[0][i][j] = dp[0][i][j - 1] + W[ i ][ A[j] ];
	}

	int act = 1;
	int prev = 0;
	for ( int k = 1; k <= K; ++k ){
		for ( int i = 0; i < 3; ++i ){
			dp[act][i][0] = dp[prev][i][0];
			for ( int j = 1; j < N; ++j ){
				dp[act][i][j] = dp[prev][i][j];
				// continue the current run
				dp[act][i][j] = max( dp[act][i][j], dp[act][i][j - 1] + W[i][ A[j] ] );
				// create a new run
				dp[act][i][j] = max( dp[act][i][j], dp[prev][(i + 1) % 3][j - 1] + W[i][ A[j] ] );
				dp[act][i][j] = max( dp[act][i][j], dp[prev][(i + 2) % 3][j - 1] + W[i][ A[j] ] );	
			}
		}
		act ^= 1;
		prev ^= 1;
	}
	
	printf("%d\n", max( dp[prev][0][N - 1], max( dp[prev][1][N - 1], dp[prev][2][N - 1] ) ) );
	return 0;
}

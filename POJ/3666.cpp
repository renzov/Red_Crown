#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN = 2056;
int N;
int M;
int A[MAXN];
int V[MAXN];
int dp[MAXN][MAXN];

int solve(){	// Find the cost of a nondecreasing sequence	
	// Initialize dp
	dp[0][0] = abs( A[0] - V[0] );
	for ( int j=1; j < M; ++j )
		dp[0][j] = min( dp[0][j - 1] , abs( A[0] - V[j] ) );
	for ( int i=1;  i < N; ++i )
		dp[i][0] = dp[i - 1][0] + abs( A[i] - V[0] );

	for ( int i=1; i < N; ++i )
		for ( int j=1; j < M; ++j )
			dp[i][j] = min( dp[i][j - 1], dp[i-1][j] + abs( A[i] - V[ j ] ) );

	return dp[N - 1][M - 1];
}

int main(){
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
		V[i] = A[i];
	}
	sort( V, V + N );
	M = unique( V, V + N ) - V;
	int res = solve();
	// Transform the problem to the nonincreasing version
	reverse( V, V + M );
	for ( int i=0; i < M; ++i ) V[i] *= -1;
	for ( int i=0; i < N; ++i ) A[i] *= -1; 
	res = min( res , solve() );
	printf("%d\n", res);
	return 0;
}

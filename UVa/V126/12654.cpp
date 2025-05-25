#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 1024;

int N, C, T1, T2;
int D[2*MAXN];
int nxt[2*MAXN][2];
int dp[2*MAXN][2*MAXN];

void process(){
	// Read the input
	for ( int i = 0; i < N; ++i )
		scanf("%d", D + i );
	
	sort( D, D + N );
	N = unique( D, D + N ) - D;

	for ( int i = 0; i < N; ++i )
		D[i + N] = D[i] + C;
	
	// Now, we calculate the jumps
	for ( int i = 0; i < 2*N; ++i ){
		nxt[i][0] = upper_bound( D, D + 2*N, D[i] + T1 ) - D;
		nxt[i][1] = upper_bound( D, D + 2*N, D[i] + T2 ) - D;
	}
	
	for ( int i = 0; i < 2*N; ++i )
		dp[i][i] = min( T1, T2 );
	
	int j, k;

	for ( int len = 2; len <= N; ++len ){
		for ( int i = 0; i + len <= 2*N; ++i ){
			j = i + len - 1;
			// Test the first kind of patch
			k = nxt[i][0];
			if ( k > j )
				dp[i][j] = T1;
			else
				dp[i][j] = dp[k][j] + T1;
			// Test the second kind of patch
			k = nxt[i][1];
			if ( k > j )
				dp[i][j] = min( dp[i][j] , T2 );
			else 
				dp[i][j] = min( dp[i][j] , T2 + dp[k][j] );
		}
	}
	// Get the optimal solution
	int res = INT_MAX;
	for ( int i = 0; i < N; ++i )
		res = min( res, dp[i][i + N - 1] );
	
	printf("%d\n", res );
}

int main(){
	while ( scanf("%d %d %d %d", &N, &C, &T1, &T2) == 4 )
		process();
	return 0;
}

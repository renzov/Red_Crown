#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 1 << 5;
int dp[MAXN << 1][MAXN][MAXN] = {0};

void precalc(){
	// Init
	for ( int k = 1; k <= 50; ++k )
		for ( int i = 0; i <= 30; ++i )
			for ( int j = 0; j <= 30; ++j )
				dp[k][i][j] = INT_MAX;
	// Base case: row = 1 or column = 1
	for ( int k = 1; k <= 30; ++k ){
		dp[k][k][1] = dp[k][1][k] = 0;
		for ( int i = k + 1; i <= 30; ++i )
			dp[k][i][1] = dp[k][1][i] = 1;
	}

	for ( int k = 1; k <= 50; ++k )
		for ( int i = 2; i <= 30; ++i )
			for ( int j = 2; j <= 30; ++j ){
				
				if ( i * j < k ) continue;
				
				if ( i * j == k ) dp[k][i][j] = 0;
				else { 
					// horizontal cut
					for ( int r = 1; r < i; ++r ){
						// every possible way to distribute k pieces
						for ( int p = 0; p <= k; ++p ){
							if ( dp[p][r][j] < INT_MAX && dp[k - p][i - r][j] < INT_MAX ){
								dp[k][i][j] = min( dp[k][i][j], dp[p][r][j] + dp[k - p][i - r][j] + j * j );
							}
						}
					}
					// vertical cut
					for ( int c = 1; c < j; ++c ){
						// every possible way to distribute k pieces
						for ( int p = 0; p <= k; ++p ){
							if ( dp[p][i][c] < INT_MAX && dp[k - p][i][j - c] < INT_MAX ){
								dp[k][i][j] = min( dp[k][i][j], dp[p][i][c] + dp[k - p][i][j - c] + i * i );
							}
						}
					}
				}
			}
}

int main(){

	precalc(); 
	
	int t;
	int n, m, k;

	scanf("%d", &t);
	while ( t-- ){
		scanf("%d %d %d", &n, &m, &k);
		printf("%d\n", dp[k][n][m]);
	}
	return 0;
}

#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 1024;

int X[2 * MAXN];
int Y[2 * MAXN];
int dp[MAXN][MAXN][2];

int Dist( const int &i, const int &j ){
	return ( X[i] - X[j] ) * ( X[i] - X[j] ) + ( Y[i] - Y[j] ) * ( Y[i] - Y[j] );
}

int main(){
	
	int H, G;

	freopen( "checklist.in" , "r", stdin );
	freopen( "checklist.out", "w", stdout );

	scanf("%d %d", &H, &G);
	for ( int i = 0; i < H + G; ++i )
		scanf("%d %d", X + i, Y + i );
	
	// DP initialization
	dp[1][0][0] = 0;
	dp[1][0][1] = INT_MAX;
	for ( int j = 1; j <= G; ++j )
		dp[0][j][0] = dp[0][j][1] = INT_MAX;
	for ( int i = 2; i <= H; ++i ){
		dp[i][0][0] = dp[i - 1][0][0] + Dist( i - 1, i  - 2 );
		dp[i][0][1] = INT_MAX;
	}

	for ( int i = 1; i <= H; ++i )
		for ( int j = 1; j <= G; ++j ){
				dp[i][j][0] = INT_MAX;
				if ( dp[i - 1][j][0] < INT_MAX )
					dp[i][j][0] = min( dp[i][j][0], dp[i - 1][j][0] + Dist( i - 2, i - 1 ) );
				if ( dp[i - 1][j][1] < INT_MAX )
					dp[i][j][0] = min( dp[i][j][0], dp[i - 1][j][1] + Dist( i - 1, j - 1 + H ) );
				
				dp[i][j][1] = INT_MAX;
				if ( dp[i][j - 1][0] < INT_MAX )
					dp[i][j][1] = min( dp[i][j][1], dp[i][j - 1][0] + Dist( i - 1, j - 1 + H ) );
				if ( dp[i][j - 1][1] < INT_MAX )
					dp[i][j][1] = min( dp[i][j][1], dp[i][j - 1][1] + Dist( j - 2 + H, j - 1 + H ) );
			}

	printf("%d\n", dp[H][G][0]);
	return 0;
}

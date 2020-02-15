#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 305;

int dp[MAXN][MAXN];
int W[MAXN][MAXN][MAXN];

int main(){
	freopen ("pieaters.in", "r", stdin);
	freopen ("pieaters.out", "w", stdout);	

	int N, M;
	int w, l, r;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d %d", &w, &l, &r);
		l--, r--;
		for ( int i=l; i <= r; ++i )
			W[ l ][ r ][ i ] = max( W[l][r][i], w );
	}
	
	for ( int len=2; len <= N; ++len ){
		for ( int i=0; i + len <= N; ++i ){
			int j = i + len - 1;
			for ( int k=i; k <= j; ++k ){
				if ( k < j ) W[i][j][k] = max( W[i][j][k], W[i][j - 1][k] );
				if ( k > i ) W[i][j][k] = max( W[i][j][k], W[i + 1][j][k] );
			}
		}
	}

	int val;
	for ( int len=1; len <= N; ++len )
		for ( int i=0; i + len <= N; ++i ){
			int j = i + len - 1;
			for ( int k=i; k <= j; ++k ){
				val = W[i][j][k];
				if ( k > i ) val += dp[i][k - 1];
				if ( k < j ) val += dp[k + 1][j];
				dp[i][j] = max( dp[i][j], val );
			}
		}
	printf("%d\n", dp[0][N - 1]);
	return 0;
}

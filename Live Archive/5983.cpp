#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 505;
int dp[MAXN][MAXN];
int S[MAXN][MAXN];
int dx[] = {0, -1};
int dy[] = {-1, 0};
int main(){
	int R, C;
	int nh, nd;
	int ni, nj;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &R, &C);
		for ( int i=0; i < R; ++i )
			for ( int j=0; j < C; ++j ){
				scanf("%d", &S[i][j]);
				dp[i][j] = 10000000;
			}
		// dp[i][j] = minimal strength to get to cell (i,j)
		dp[R-1][C-1] = 1;
		for ( int i=R-1; i >= 0; --i )
			for ( int j=C-1; j >= 0; --j ){
				if ( dp[i][j] <= 0 ) dp[i][j] = 1;
				for ( int k=0; k < 2; ++k ){
					ni = i + dx[k];
					nj = j + dy[k];
					if ( ni < 0 || nj < 0 ) continue;
					dp[ni][nj] = min( dp[ni][nj], dp[i][j] - S[ni][nj] );
				}
			}
		printf("%d\n", dp[0][0]);
	}
	return 0;
}

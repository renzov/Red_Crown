#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 16;
const int MAXM = 10005;
int N, M;
int A[MAXN];
int dp[MAXN][MAXM];	// dp[i][j] = min cost of obtaining j using the tiles from 1 ... i

int main(){
	scanf("%d %d", &N, &M);
	for ( int i=1; i <= N; ++i )
		scanf("%d", A + i);

	// Initialize the dp
	dp[0][0] = 0;
	for ( int i=1; i <= M; ++i ) dp[0][i] = INT_MAX;

	for ( int i=1; i <= N; ++i ){
		for ( int j=0; j <= M; ++j ){
			dp[i][j] = INT_MAX;
			for ( int k=1; k*k <= j; ++k ){
				if ( dp[i - 1][j - k*k] < INT_MAX )
					dp[i][j] = min( dp[i][j] , dp[i - 1][j - k*k] + (A[i] - k)*(A[i] - k) );
			}
		}
	}
	if ( dp[N][M] < INT_MAX ) printf("%d\n", dp[N][M]);
	else puts("-1");
	return 0;
}

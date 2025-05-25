#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 5005;
char A[MAXN];
char B[MAXN];

int dp[MAXN][MAXN];

int main(){
	scanf("%s %s", (A + 1), (B + 1) );
	int N = strlen( A + 1 );
	int M = strlen( B + 1 );

	// base case -- when one string is empty
	for ( int i = 0; i <= N; ++i )
		dp[i][0] = i;
	for ( int j = 0; j <= M; ++j )
		dp[0][j] = j; 

	for ( int i = 1; i <= N; ++i )
		for ( int j = 1; j <= M; ++j ){
			dp[i][j] = dp[i - 1][j - 1] + ( A[i] != B[j] );
			dp[i][j] = min( dp[i][j], dp[i - 1][j] + 1 );
			dp[i][j] = min( dp[i][j], dp[i][j - 1] + 1 );
		}
	printf("%d\n", dp[N][M]);
	return 0;	
}

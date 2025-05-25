#include<cstdio>
using namespace std;

const int MAXN = 1024;
const int MOD = 1000000007;

char mat[MAXN][MAXN];
int dp[MAXN][MAXN];

int main(){
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		scanf("%s", mat[i] );
	
	dp[0][0] = (mat[0][0] != '*')? 1:0;

	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j ){
			if ( mat[i][j] == '*' ) continue;
			if ( i && mat[i - 1][j] != '*' ){
				dp[i][j] += dp[i - 1][j];
				dp[i][j] %= MOD;
			}
			if ( j && mat[i][j - 1] != '*' ){
				dp[i][j] += dp[i][j - 1];
				dp[i][j] %= MOD;
			}
		}
	printf("%d\n", dp[N - 1][N - 1]);
	return 0;
}

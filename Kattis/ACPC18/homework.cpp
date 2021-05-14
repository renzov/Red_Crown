#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 5005;

char S[2*MAXN];
char A[MAXN];
char B[MAXN];
bool dp[MAXN][MAXN];

int main(){
	int N, M;

	scanf("%s %s %s", S, A, B);
	N = strlen(A);
	M = strlen(B);
	// Initialize dp
	dp[0][0] = true;
	for ( int i=1; i <= N; ++i )
		dp[i][0] = (A[i - 1] == S[i - 1]) && dp[i - 1][0];
	for ( int j=1; j <= M; ++j )
		dp[0][j] = (B[j - 1] == S[j - 1]) && dp[0][j - 1];
	
	int k;
	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= M; ++j ){
			k = i + j;
			dp[i][j] = false;
			if ( A[i - 1] == S[k - 1] ){
				dp[i][j] |= dp[i - 1][j];
			}
			if ( B[j - 1] == S[k - 1] ){
				dp[i][j] |= dp[i][j - 1];
			}
		}
	
	puts( dp[N][M]? "yes":"no");
	return 0;
}

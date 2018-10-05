#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 65;
char S[MAXN];
long long dp[MAXN][MAXN];

int main(){
	int runs;
	int N;
	int j;
	
	scanf("%d", &runs);	
	while ( runs-- ){
		scanf("%s", S);
		N = strlen(S);
		for ( int i=0; i < N; ++i )
			for ( int j=i; j < N; ++j )
				dp[i][j] = 1;
		
		for ( int k=1; k < N; ++k )
			for ( int i=0; i + k < N; ++i ){
				j = i + k;
				dp[i][j] = dp[i][j - 1];
				if ( S[i] == S[j] ){
					for ( int l = i + 1; l < j; ++l )
						dp[i][j] += dp[l][j - 1];
					dp[i][j]++;
				}
			}
		
		//for ( int i=0; i < N; ++i )
		//	for ( int j=i; j < N; ++j )
		//		printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
		
		long long res = 0;
		for ( int i=0; i < N; ++i )
			res += dp[i][N - 1];
			
		printf("%lld\n", res);
	}
	return 0;
}

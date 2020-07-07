#include<cstdio>
using namespace std;

const int MAXN = 128;
long long dp[MAXN][MAXN];
int A[MAXN];

int main(){
	int N, K;

	for ( int i=1; i < MAXN; ++i )
		dp[i][1] = 1;

	while ( scanf("%d %d", &N, &K) && N && K ){
		for ( int i=1; i <= N; ++i )
			scanf("%d", A + i);
		
		for ( int j=2; j <= K; ++j ){
			for ( int i=1; i <= N; ++i ){
				dp[i][j] = 0;
				for ( int k=1; k < i; ++k ){
					if ( A[k] < A[i] )
						dp[i][j] += dp[k][j - 1];
				}
			}
		}
		long long res = 0;
		for ( int i=1; i <= N; ++i )
			res += dp[i][K];
		printf("%lld\n", res);
	}
	return 0;
}

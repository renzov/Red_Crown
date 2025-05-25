#include<cstdio>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 128;
const int MAXX = 1000005;

int C[MAXN];
int dp[MAXX];

int main(){
	int N, X, c;

	scanf("%d %d", &N, &X);
	for ( int i = 0; i < N; ++i )
		scanf("%d", C + i );
	sort( C, C + N );

	dp[0] = 1;
	for ( int j = 0; j < N; ++j ){
		c = C[j];
		for ( int i = c; i <= X; ++i ){
			dp[i] += dp[i - c];
			dp[i] %= MOD;
		}
	}
	printf("%d\n", dp[X]);
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int MOD = 1000000007;
const int SQRT = 316;
const int MAXN = 100000;
int dp[MAXN + 5][SQRT + 5] = {0};

void preprocess(){
	for ( int j=1; j <= SQRT; ++j ) dp[0][j] = 1;
	for ( int i=1; i <= MAXN; ++i )
		for ( int j=1; j <= SQRT; ++j ){
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			dp[i][j] %= MOD;
		}
}

void process(){
	int N, K;
	int sq;
	scanf("%d %d", &N, &K);
	sq = ( int ) sqrt( K );
	if ( (sq + 1)*(sq + 1) <= K ) sq++;
	if ( N == 1 ){
		puts("-1");
		return;
	}
	long long ans = 0;
	for ( int j=1; j <= sq; ++j ){
		ans += (1LL * dp[N - 2][j] * ( K/j - j + 1 ));
		ans %= MOD;
	}
	printf("%lld\n", ans);
}

int main(){
	int runs;
	preprocess();
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

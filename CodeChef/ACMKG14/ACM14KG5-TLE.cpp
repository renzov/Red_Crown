#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int MOD = 1000000007;
const int SQRT = 316;
int dp[SQRT + 5][2];
int sum[SQRT + 5][2];

void process(){
	int N, K;
	scanf("%d %d", &N, &K);
	if ( N == 1 ){
		puts("-1");
		return;
	}
	int sq = (int)sqrt(K);
	if ( (sq + 1)*(sq + 1) <= K )
		sq++;
	
	sum[sq][0] = dp[sq][0] = (K / sq) - sq + 1;
	for ( int i=sq - 1; i > 0; --i ){
		dp[i][0] = (K / i) - i + 1;
		dp[i][0] %= MOD;
		sum[i][0] = sum[i + 1][0] + dp[i][0];
		sum[i][0] %= MOD;
	}

	int act = 1;
	int prev = 0;
	for ( int i=N-1; i > 0; --i ){
		sum[sq][act] = dp[sq][act] = dp[sq][prev];
		for ( int j=sq - 1; j > 0; --j ){
			dp[j][act] = sum[j][prev];
			sum[j][act] = sum[j + 1][act] + dp[j][act];
			sum[j][act] %= MOD;
		}
		swap(act, prev);
	}
	printf("%d\n", dp[1][prev]);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

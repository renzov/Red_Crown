#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 200005;
long long A[MAXN];
long long S[MAXN];
long long dp[MAXN];
int best[MAXN];

int main(){

	int N, K;
	
	scanf("%d %d", &N, &K);

	for ( int i=1; i <= N; ++i ){
		scanf("%I64d", A + i );
		S[i] = S[i - 1] + A[i];
	}
	for ( int i=N-K+1; i > 0; --i ){
		if ( dp[i + 1] <= S[i+K-1] - S[i - 1] ){
			dp[i] = S[i + K - 1] - S[i - 1];
			best[i] = i;
		}
		else {
			dp[i] = dp[i + 1];
			best[i] = best[i + 1];
		}
	}
	long long res = -LLONG_MAX;
	int a, b;
	for ( int i=1; i <= (N - 2*K + 1); ++i ){
		if ( res < S[i + K - 1] - S[i - 1] + dp[i + K] ){
			a = i, b = best[i + K];
			res = S[i + K - 1] - S[ i - 1 ] + dp[i + K];
		}
	}
	printf("%d %d\n", a, b);
	return 0;
}

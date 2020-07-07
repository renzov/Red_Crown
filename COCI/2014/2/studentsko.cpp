#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 5005;
int A[MAXN];
int B[MAXN];
int V[MAXN];

int dp[MAXN];

int main(){
	int N, K;

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
		B[i] = A[i];
	}
	sort( B, B + N );
	int idx;
	for ( int i=0; i < N; ++i ){
		idx = lower_bound( B, B + N, A[i] ) - B;
		V[i] = idx / K;
	}

	dp[0] = 1;
	for ( int i=1; i < N; ++i ){
		dp[i] = 1;
		for ( int j=0; j < i; ++j ){
			if ( V[j] <= V[i] )
				dp[i] = max( dp[i], dp[j] + 1 );
		}
	}

	printf("%d\n", N - *max_element(dp, dp + N));
	return 0;
}

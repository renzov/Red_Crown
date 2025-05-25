#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
const int MAXV = 100005;

int W[MAXN];
int V[MAXN];
int dp[2][MAXV];

int main(){

	int N, X;

	scanf("%d %d", &N, &X);

	for ( int i = 0; i < N; ++i )
		scanf("%d", W + (i + 1) );
	for ( int i = 0; i < N; ++i )
		scanf("%d", V + (i + 1) );

	int act = 1;
	int prev = 0;

	for ( int j = 1; j <= N; ++j ){
		for ( int i = 1; i <= X; ++i ){
			dp[act][i] = dp[prev][i];
			if ( i >= W[j] )
				dp[act][i] = max( dp[act][i] , dp[prev][i - W[j]] + V[j] );
		}
		act ^= 1;
		prev ^= 1;
	}
	printf("%d\n", dp[prev][X]);
	return 0;
}

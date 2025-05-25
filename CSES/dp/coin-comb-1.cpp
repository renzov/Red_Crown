#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 128;
const int MAXX = 1000005;

int dp[MAXX];
int C[MAXN];

int main(){
	int N, X, c;

	scanf("%d %d", &N, &X);
	for ( int i = 0; i < N; ++i )
		scanf("%d", C + i);
	sort( C, C + N );
	
	dp[0] = 1;
	for ( int i = 1; i <= X; ++i ){
		for ( int j = 0; j < N && C[j] <= i; ++j ){
			c = C[j];
			dp[i] += dp[i - c];
			dp[i] %= MOD;
		}
	}
	printf("%d\n", dp[X]);
	return 0;
}

#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 10005;
int dp[MAXN];
int S[MAXN];

int main(){
	freopen ("teamwork.in", "r", stdin);
	freopen ("teamwork.out", "w", stdout);	

	int N, K;

	scanf("%d %d", &N, &K);
	for ( int i=1; i <= N; ++i )
		scanf("%d", S + i);

	int val, maxS;
	dp[0] = 0;
	for ( int i=1; i <= N; ++i ){
		val = -INT_MAX;
		maxS = S[i];
		for ( int j=i - 1; j >= 0 && i - j <= K ; --j ){
			val = max( val, dp[j] + maxS*(i - j) );
			maxS = max( maxS, S[j] );
		}
		dp[i] = val;
	}
	printf("%d\n", dp[N]);
	return 0;
}

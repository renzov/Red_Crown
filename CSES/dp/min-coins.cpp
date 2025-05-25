#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

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
	dp[0] = 0;

	for ( int i = 1; i <= X; ++i ){
		dp[i] = INT_MAX;
		for ( int j = 0; j < N && C[j] <= i; ++j ){
			c = C[j];
			if ( dp[i - c] < INT_MAX )
				dp[i] = min( dp[i], dp[i - c] + 1 );
			}
	}
	if ( dp[X] < INT_MAX )
		printf("%d\n", dp[X]);
	else
		puts("-1");
	return 0;
}

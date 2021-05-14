#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 5005;
const int MAXK = 1024;

int L[MAXN];
int N, K;
long long dp[MAXN][MAXK];	// dp[i][j] = min value obtained using L[i ... N - 1] , and already choosen j triples

void process(){
	scanf("%d %d", &K, &N);
	K += 8;
	for ( int i=0; i < N; ++i )
		scanf("%d", L + i);
	sort( L, L + N );

	// Initialization
	for ( int j=1; j <= K; ++j )
		dp[N-1][j] = dp[N - 2][j] = LLONG_MAX;
	for ( int i=0; i < N; ++i )
		dp[i][0] = 0; 
	// calculate dp
	int left;
	for ( int i=N - 3; i >= 0; --i ){
		for ( int j=1; j <= K; ++j ){
			left = N - i - 2 - 3*(j - 1);									// Number of sticks that were not chosen
			dp[i][j] = dp[i + 1][j]; 								// We do not choose to form a triple
			if ( left > 0 && dp[i + 2][j - 1] < LLONG_MAX ){		// We can form a triple
				dp[i][j] = min( dp[i][j] , (L[i] - L[i + 1])*(L[i] - L[i + 1]) + dp[i + 2][j - 1] );
			}
		}
	}
	printf("%lld\n", dp[0][K]);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

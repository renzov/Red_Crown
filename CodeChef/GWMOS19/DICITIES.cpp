#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 20;

int N, K, M;
int W[MAXN + 2][MAXN + 2];
long long sumSet[1 << MAXN];
long long cost[MAXN + 1][1 << MAXN];
long long dp[MAXN + 1][1 << MAXN];


inline bool in( const int &mask, const int &p ){
	return (mask >> p)&1;
}

void process(){
	long long total = 0LL;

	scanf("%d %d", &N, &K);
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j ){
			scanf("%d", W[i] + j );
			total += W[i][j];
		}

	total >>= 1;
	M = N - K; // Non special vertices

	sumSet[0] = 0LL;
	for ( int mask = 1; mask < (1 << M); ++mask ){
		sumSet[mask] = 0LL;
		for ( int i=K; i < (N - 1); ++i )	
			if ( in( mask, i - K ) )
				for ( int j=i + 1; j < N; ++j )
					if ( in( mask, j - K ) )
						sumSet[mask] += W[i][j];
	}

	for ( int mask = 0; mask < (1 << M); ++mask )
		for ( int i=0; i < K; ++i ){
			cost[i][mask] = sumSet[mask];
			for ( int j=K; j < N; ++j )
				if ( in( mask, j - K ) )
					cost[i][mask] += W[i][j];
		}

	// Initialize the dp table
	for ( int mask = 0; mask < (1 << M); ++mask )
		dp[0][mask] = cost[0][mask];

	for ( int i=1; i < K; ++i ){
		for ( int mask=0; mask < (1 << M); ++mask ){
			dp[i][mask] = 0LL;
			for ( int s = mask; ; s = (s - 1) & mask ){
				dp[i][mask] = max( dp[i][mask], dp[i - 1][mask ^ s] + cost[i][s] );
				if ( s == 0 ) break;
			}
		}
	}

	int all = (1 << M) - 1;
	printf("%lld\n", total - dp[K - 1][all]);
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}

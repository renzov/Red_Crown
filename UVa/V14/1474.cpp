#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 4005;
typedef pair< long long, int > elem;

int N, M;
long long dp[MAXN][MAXN];
elem A[MAXN];
elem B[MAXN];
bool op[MAXN][MAXN];
int sol[MAXN];
int sol2[MAXN];

void process(){
	for ( int i=1; i <= N; ++i ){
		scanf("%lld", &A[i].first );
		A[i].second = i;
	}

	scanf("%d", &M);
	for ( int i=1; i <= M; ++i ){
		scanf("%lld", &B[i].first );
		B[i].second = i;
	}

	sort( A + 1, A + (N + 1) );
	sort( B + 1, B + (M + 1) );

	dp[0][0] = 0;
	for ( int i=1; i <= N; ++i )
		dp[0][i] = LLONG_MAX;

	for ( int i=1; i <= M; ++i ){
		dp[i][i] = dp[i - 1][i - 1] + abs( A[i].first - B[i].first );
		op[i][i] = true;
		for ( int j=i + 1; j <= N; ++j ){
			if ( dp[i][j - 1] <= dp[i - 1][j - 1] ){
				dp[i][j] = dp[i][j - 1] + abs( A[j].first - B[i].first );
				op[i][j] = false;
			}
			else {
				dp[i][j] = dp[i - 1][j - 1] + abs( A[j].first - B[i].first );
				op[i][j] = true;
			}
		}
	}

	int cur = M;
	for ( int i=N; i >= 1; --i ){
		sol[i] = cur;
		if ( op[cur][i] ) cur--;
	}

	for ( int i=1; i <= N; ++i ){
		sol2[ A[i].second ] = B[ sol[i] ].second;
	}

	printf("%lld\n", dp[M][N]);
	for ( int i=1; i <= N; ++i ){
		if ( i > 1 ) putchar(' ');
		printf("%d", sol2[i]);
	}
	puts("");
}

int main(){
	while ( scanf("%d", &N) == 1 ){
		process();
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 5005;
const int MAXM = 100005;
int X[MAXN];
int W[MAXM];
int dp[MAXN];	// dp[i] = min cost of covering cows from i to N
int main(){
	int N, M, len;

	scanf("%d %d", &N, &M);
	
	for ( int i=0; i < N; ++i )
		scanf("%d", X + i );
	
	for ( int i=1; i <= M; ++i )
		scanf("%d", W + i);

	// Now we find W[i] = least cost using an umbrella of size AT LEAST i
	for ( int i=M-1; i > 0; --i )
		W[i] = min( W[i] , W[i + 1] );

	// Sort the X coordinates, it is not guaranteed that is sorted
	sort( X, X + N );
	// Initialize the dp
	dp[N] = 0;	
	for ( int i = N - 1; i >= 0; --i ){
		dp[i] = W[1] + dp[i + 1];
		for ( int j = i + 1; j < N; ++j ){
			len = X[j] - X[i] + 1;
			dp[i] = min( dp[i] , W[len] + dp[j + 1] );
		}
	}
	printf("%d\n", dp[0]);
	return 0;
}

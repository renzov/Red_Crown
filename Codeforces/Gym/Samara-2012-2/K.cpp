#include<cstdio>
using namespace std;
const int MAXN = 1000005;
int dp[MAXN];

int solve( const int &N ){
	if ( dp[N] ) return dp[N];	// state already calculated

	int d;
	dp[N] = 1;
	for ( d = 2; d <= N/d; ++d ){
		if ( N % d ) continue;
		if ( d * d == N )
			dp[N] += solve( d );
		else 
			dp[N] += ( solve( d ) + solve( N / d ) );
	}
	return dp[N];
}

int main(){
	int N;
	
	scanf("%d", &N);
	dp[1] = 1;
	printf("%d\n", solve(N) );

	return 0;
}

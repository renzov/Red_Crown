#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1 << 11;

int N;
int V[MAXN];
long long dp[MAXN][MAXN];

long long solve( const int &L, const int &R ){
	long long &res = dp[L][R];
	
	if ( res != -1 ) return res;
	long long t = L + (N - R);
	
	if ( t == N ) res = V[L] * t;
	else res = max( solve(L + 1, R) + t * V[L], solve( L, R - 1 ) + t * V[R] );
	
	return res;
}

int main(){

	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d", V + i );
	
	// Initialize dp table
	for ( int i=0; i < N; ++i )
		fill( dp[i], dp[i] + N, -1 );

	printf("%lld\n", solve( 0, N - 1 ) );
	return 0;
}

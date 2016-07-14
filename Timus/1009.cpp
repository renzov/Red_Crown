#include<cstdio>
#include<cstring>
using namespace std;

int N, K;
long long memo[20][2];

long long solve( int n, bool zero ){
	if ( !n ) return 1LL;
	if ( memo[n][zero] != -1 ) return memo[n][zero];
	memo[n][zero] = 0LL;
	if ( !zero ) memo[n][zero] += solve( n-1, true );
	memo[n][zero] += (K-1)*solve( n-1, false );
	return memo[n][zero];
}

int main(){
	scanf("%d %d", &N, &K);
	memset( memo, -1, sizeof(memo) );
	printf("%lld\n", solve(N, true));
	return 0;
}

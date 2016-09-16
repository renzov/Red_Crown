#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MOD = 1000000007;
const int SIZE = 11;
const int MAXN = 401;
bool palim[SIZE+1][1 << SIZE] = {0};
int dp[SIZE+1][MAXN][1 << SIZE];
int N, K;
int ALL;

void build_pal( int mask, int s ){
	if ( s > SIZE ) return;
	palim[s][mask] = true;
	build_pal( mask << 1 , s + 2 );
	build_pal( ((mask << 1) | 1) | ( 1 << (s + 1) ) , s + 2 );
}

int solve(int n, int mask){
	if ( n == 0 ) return palim[K][mask]? 0:1;
	if ( dp[K][n][mask] != -1 ) return dp[K][n][mask];
	int &res = dp[K][n][mask];
	res = 0;
	if ( palim[K][mask] ) return res;
	int mask2 = (( mask << 1 ) | 0);
	if ( !palim[K+1][mask2] && !palim[K][mask2 & ALL] ){ res += solve( n-1, mask2 & ALL ); res %= MOD; }
	mask2 = ((mask << 1) | 1);
	if ( !palim[K+1][mask2] && !palim[K][mask2 & ALL] ){ res += solve( n-1, mask2 & ALL ); res %= MOD; }
	return res;
}

int main(){
	build_pal( 0 , 1 );
	build_pal( 1 , 1 );
	build_pal( 3 , 2 );
	build_pal( 0 , 2 );

	memset(dp, -1, sizeof(dp));
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &K);
		ALL = (1 << K) - 1;		
		int res = 0;
		if ( K > N ){
			printf("%d\n", 1 << N);
			continue;
		}
		for ( int i=0; i < (1<<K); ++i ){
			res += solve( N - K, i );	
			res %= MOD;
		}	
		printf("%d\n", res);
	}
	return 0;
}

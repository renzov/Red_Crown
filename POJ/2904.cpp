#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[11][101][101];

int solve( int k , int l , int r ){
	if ( dp[k][l][r] != -1 ) return dp[k][l][r];
	int res = INT_MAX;
	int tmp;
	for ( int t=l; t <= r ; ++t ){
		tmp = -INT_MAX;
		if ( t > l ) tmp = max( tmp , solve(k-1,l,t-1) + t );
		if ( t < r ) tmp = max( tmp , solve(k , t+1 , r ) + t );
		res = min(res,tmp); 
	}
	return (dp[k][l][r] = res);
}

int main(){
	int runs;
	memset(dp,-1,sizeof(dp));
	for ( int i=1; i <= 100; ++i )
		for (int j=i; j <= 100; ++j ){
			dp[1][i][j] = ( ( j*(j+1) ) >> 1 ) - ((i*(i-1)) >> 1) ;
		}
	for ( int i=1; i <= 10; ++i ){
		for ( int j=1; j <= 100; ++j ){
			dp[i][j][j] = j;
		}
	}
	int K,M;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d",&K,&M);
		printf("%d\n",solve(K,1,M));
	}
	return 0;
}

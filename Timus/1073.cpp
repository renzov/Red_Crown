#include<cstdio>
#include<climits>
int dp[ 60005 ];

inline int min( int x,int y ){ return x<=y? x:y; }

int main(){
  int n;
  scanf("%d",&n);
  dp[1] = 1;
  dp[0] = 0;
  for ( int i = 2; i <= n; ++i ){
	 dp[i] = INT_MAX;
	 for ( int j=1; (j*j) <= i; ++j ){
		dp[i] = min( dp[i] , dp[i-(j*j)] + 1 );
	 }
  }
  printf("%d\n",dp[n]);
  return 0;
}
#include<cstdio>

long long dp[2][50];

int main(){
  int n,k;
  dp[0][0] = 1;
  dp[1][0] = 1;
  scanf("%d %d",&n,&k);
  for ( int i=1; i < n; ++i ){
	 dp[0][i] = 0;
	 dp[1][i] = 0;
	 dp[0][i] += ( dp[0][i-1] + dp[1][i-1] );
	 dp[1][i] += dp[0][i-1];
  }
  long long total = dp[0][n-1] + dp[1][n-1];
  if ( k > total ) puts("-1");
  else {
	 for ( int i=n-1; i >= 0 ; --i){
		if ( dp[0][i] < k ){
		  putchar('1');
		  k -= dp[0][i];
		}
		else {
		  putchar('0');
		}
	 }
	 putchar('\n');
  }
  return 0;
}
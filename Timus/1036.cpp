#include<cstdio>
int main(){
  long long dp[55][555] = {0};
  int n,s;
  scanf("%d %d",&n,&s);
  if ( s % 2 ) printf("0\n");
  else {
	 s >>= 1;
	 for ( int i=0; i < 10; ++i )
		dp[0][i] = 1;
	 for ( int i=1; i < n; ++i ){
		for ( int j=0; j <= s; ++j ){
		  for ( int k=0; k < 10; ++k ){
			 if ( k <= j ) dp[i][j] += dp[i-1][j-k];
		  }
		}
	 }
	 printf("%lld\n",dp[n-1][s]*dp[n-1][s]);
  }
  return 0;
}
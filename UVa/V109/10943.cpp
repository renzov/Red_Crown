#include<cstdio>

long long dp[105][105] = {0};
const long long MOD = 1000000;

int main(){
  for (int j=0; j <= 100; ++j){
	 dp[1][j] = 1;
  }
  for (int i=2; i <= 100; ++i){
	 for (int j=0; j <= 100; ++j){
		for (int k=0; k <= j; ++k)
		  dp[i][j] += dp[i-1][j-k];
		  dp[i][j] %= MOD;
	 }
  }
  
  int n,k;
  while (scanf("%d %d",&k,&n) && (n || k) ){
	 printf("%lld\n",dp[n][k]);
  }
  return 0;
}
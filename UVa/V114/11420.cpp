#include<cstdio>

unsigned long long dp[67][67][2] = {0};

int main(){
  dp[0][0][0] = 1;
  dp[0][0][1] = 1;
  for (int i=1;  i <= 65; ++i){
	 for (int j=0; j <= 65; ++j){
		dp[i][j][0] = dp[i-1][j][1];
		if (j >= 1) dp[i][j][0] += dp[i-1][j-1][0];
		dp[i][j][1] = dp[i-1][j][0] + dp[i-1][j][1];
	 }
  }
  int n,s;
  while (scanf("%d %d",&n,&s) && n > 0){
	 printf("%llu\n",dp[n][s][0]);
  }
  return 0;
}

#include<cstdio>

long long dp[72][72][72] = {0};

int main(){

  int n,t,p;
  int runs;
  
  for (int k=1; k <= 70; ++k){
		for (int j=k; j <= 70; ++j){
		  dp[1][j][k] = 1;
		}
  }

  for (int k=1; k <= 70; ++k){
	 for (int i=2; i <= 70; ++i){
		for (int j=1; j <= 70; ++j){
		  for (int l=k; l <= 70; ++l){
			 if (j >= l) dp[i][j][k] += dp[i-1][j-l][k];
		  }
		}
	 }
  }
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d %d",&n,&t,&p);
	 printf("%lld\n",dp[n][t][p]);
  }

  return 0;
}
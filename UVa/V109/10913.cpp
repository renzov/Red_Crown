#include<cstdio>
const INF = 999999999;
int M[80][80];
int dp[80][80][2];
int minNeg[80][80][2];

int main(){
  int n,k;
  while (scanf("%d %d",&n,&k) && (n || k)){
		for (int i=1; i <= n; ++i) for (int j=1; j <= n; ++j) scanf("%d",&M[i][j]);
		for (int i=1; i <= n; ++i) 
		  for (int j=1; j <= n; ++j){ 
			 dp[i][j][0] = dp[i][j][1] = -INF; 
			 minNeg[i][j][0] = minNeg[i][j][1] = INF; 
		  }
		for (int i=0; i <= n; ++i){
		  dp[0][i][0] = dp[0][i][1] = 0;
		  dp[i][0][0] = dp[i][0][1] = 0;
		  dp[i][n+1][0] = dp[i][n+1][1] = 0;
		  minNeg[0][i][0] = minNeg[0][i][1] = 0;
		  minNeg[i][0][0] = minNeg[i][0][1] = 0;
		  minNeg[i][n+1][0] = minNeg[i][n+1][1] = 0;
		}
		for (int i=1; i <= n; ++i){
		  
			 for (int j=1; j <= n; ++j){
				  
			 }
			 for (int j=n; j >= 1; --j){

			 }
		}
		if (dp[n][n][0] == -INF){
			 puts("impossible");
		}
		else printf("%d\n",dp[n][n][0]));
  }
  return 0;
}
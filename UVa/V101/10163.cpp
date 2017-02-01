#include<cstdio>
const int INF = 9999999;
int dp[32][102][1005];
int p[32] = {0};

inline int min(int a,int b){ return (a <= b)? a:b; }

int main(){
  int n,m;
  int res;
  int Max;
  while ( scanf("%d %d",&n,&m) && (n||m) ){
	 Max = 0;
	 for (int i=1; i <= m; ++i){ scanf("%d",p+i); Max = (Max < p[i])? p[i]:Max; }
	 for (int i=0; i <= m; ++i)
		for (int j=1; j <= n; ++j)
		  for (int k=0; k <= Max; ++k)
			 dp[i][j][k] = INF;
	 for (int i=0; i <= m; ++i)
		for (int j=0; j <= n; ++j)
		  dp[i][j][0] = 0;
	 for (int i=0; i <= m; ++i)
		for (int k=0; k <= Max; ++k)
		  dp[i][0][k] = 0;
	 for (int k=1; k <= Max; ++k )
		  for (int j=1; j <= n; ++j)
			 for (int i=1; i <= m; ++i){
				dp[i][j][k] = dp[i-1][j][k];
				if ( p[i] >= k ){
				  res = j - (p[i]/k);
				  if (res < 0) res = 0;
				  dp[i][j][k] = min( dp[i][j][k] , dp[i-1][res][k] + p[i] );
				}
			 }
	 for (int i=Max; i >= 0; --i){
		if (dp[m][n][i] < INF){
		  printf("%d %d\n",i,dp[m][n][i]);
		  break;
		}
	 }
  }
  return 0;
}
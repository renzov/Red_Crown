#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

int f[105];
int p[105];
int dp[105][10210];

int main(){
  int n,m;
  int t,w;
  while (scanf("%d %d",&m,&n) != EOF){
	 for (int i=0; i < n; ++i)
		scanf("%d %d",p+i,f+i);
	 t = m;
	 if ((m + 200) > 2000) t+=200;
	 for (int i=0; i <= n; ++i)
		for (int j=0; j <= t; ++j)
		  dp[i][j] = -INT_MAX;
	 dp[0][0] = 0;
	 for (int i=0; i < n; ++i){
		for (int j=0; j <= t; ++j){
			dp[i+1][j] = max( dp[i+1][j], dp[i][j]);
			if (dp[i][j] > -INT_MAX){
				w = p[i] + j;
				if ( w <= t ) dp[i+1][w] = max( dp[i+1][w] , dp[i][j] + f[i] );
		   }
		}
	 }
	 int best = 0;
	 for (int j=1; n > 0 && j <= t; ++j){
		dp[n][j] = max( dp[n][j] , dp[n-1][j] );
		if ((j <= m || j > 2000) && best < dp[n][j]) best = dp[n][j];
	 }
	 printf("%d\n",best);
  }
  return 0;
}
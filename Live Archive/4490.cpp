#include<cstdio>
#include<algorithm>
using namespace std;
const int INF = 10000;

int dp[105][105][8];

int main(){
  int N,K;
  int a[ 105 ];
  int i,j,k,l;
  int res;
  int cases = 0;

  while ( scanf("%d %d",&N,&K) && N ){
	 cases++;
	 for (i=1; i <= N; ++i){ scanf("%d",a+i); a[i]-=25; }
	 /* initialization */
	 for (i=1; i <= N ; ++i){
		for (k=0; k <= 7; ++k){
		  dp[i][0][k] = INF;
		  if ( a[i] == k ){
			 for (l=0; l <= 7; ++l){
				  if ( i > 1 )
					 dp[i][0][k] = min( dp[i][0][k] , dp[i-1][0][l] + ( l != a[i] ) );
				  else dp[i][0][k] = 1;
			 }
		  }
		}
	 }
	 
	 for (j=1; j <= K; ++j)
		for (k=0; k <= 7 ; ++k){
		  dp[1][j][k] = 0;
		}
	 
	 for (i=2; i <= N; ++i){
		for (j=1; j <= K; ++j){
		  for (k=0; k <= 7; ++k){
			 dp[i][j][k] = dp[i][j-1][k];
			 if ( j >= i ) dp[i][j][k] = 0;
			 else dp[i][j][k] = min( dp[i][j][k] , dp[i-1][j-1][k]  );
			 if ( a[i] == k ){
				for (l=0; l <= 7; ++l){
				  dp[i][j][k] = min( dp[i][j][k] , max(dp[i-1][j][l] + ( l != a[i] ),1) );
				}
			 }
			 printf("dp[%d][%d][%d] = %d\n",i,j,k,dp[i][j][k]);
		  }
		}
	 }
	 
	 res = INF;
	 for (k=0; k <= 7; ++k) res = min( res , dp[N][K][k] );
	 printf("Case %d: %d\n\n",cases,res);
  }
  return 0;
}
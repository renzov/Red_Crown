#include<cstdio>
#include<climits>
int len[10002];
int dp[2][105];

inline int min(int x,int y){ return x <= y ? x:y; }

int main(){
  int runs;
  int i,j;
  int x;
  int n,m;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&m);
	 scanf("%d",&n);
	 for (i=0; i<n; ++i) scanf("%d",len+i);
	 for (j=m-1; j >= 0; --j){
		if ( (len[n-1] + j - 1) >= m) dp[0][j] = INT_MAX;
		else dp[0][j] = (m - (len[n-1]+j))*(m-(len[n-1]+j));
	 }
	 x = 1;
	 for (i=n-2; i >= 0; --i){
		for (j=m-1; j >= 0; --j){
		  dp[x][j] = INT_MAX;
		  if ( (len[i] + j - 1) < m ){
			 dp[x][j] = (m - (len[i] + j))*(m - (len[i] + j)) + dp[1-x][0]; 
			 if ( (j + len[i] + 1) < m ) dp[x][j] = min( dp[x][j] , dp[1-x][j + len[i] + 1] );
		  }
		}
		x = 1 - x;
	 }
	 printf("%d\n",dp[1-x][0]);
  }
  return 0;
}
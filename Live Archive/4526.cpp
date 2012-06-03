#include<cstdio>
#include<climits>
#include<cstring>

int dp[2][205];
int s[1005];
int p[1005];
int d[1005];

inline int min(int a,int b){ return a<=b? a:b; }

int main(){
  int n,runs;
  int i,j,k;
  int x;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (i=1; i <= n; ++i) scanf("%d %d %d",p+i,s+i,d+i);
	 for (i=0; i <= 200; ++i) dp[0][i] = dp[1][i] = INT_MAX;
	 dp[0][0] = 0;
	 s[n+1] = 0;
	 s[0] = 0;
	 d[0] = 0;
 	 x = 1;
	 for (i=1; i <= n; ++i){
		for (j=0; j <= d[i+1]; ++j) dp[x][j] = INT_MAX;
		for (j=0; j <= d[i+1]; ++j){
		  for (k=0; k <= d[i]; ++k){
			 if ( dp[1-x][k] < INT_MAX && (j+d[i]-k) <= s[i] ){
				dp[x][j] = min( dp[x][j] , dp[1-x][k] + p[i]*(j+d[i]-k) );
			 }
		  }
		}
		x = 1 - x;
	 }
	 printf("%d\n",dp[1-x][0]);
  }
  return 0;
}
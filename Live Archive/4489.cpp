#include<cstdio>

int dp[2][502][52][2];

int h[305];
int s[305];
int p[305];

inline int max(int a,int b){ return a>=b? a:b; }

int main(){
  int n,a,b;
  int i,j,k;
  int x;
  int runs = 0;
  while ( scanf("%d %d %d",&a,&b,&n) && n ){
	 runs++;
	 for (i=0; i < n; ++i) scanf("%d %d %d",p+i,h+i,s+i);
	 for (i=0; i <= a; ++i)
		for (j=0; j <= b; ++j){
		  dp[0][i][j][0] = dp[0][i][j][1] = 0;
		}
	 x = 1;
	 for ( k = 0; k < n; ++k ){
		for ( i = 0; i <= a; ++i )
		  for ( j=0; j <= b; ++j ){
			 dp[x][i][j][0] = dp[x][i][j][1] = -1;
			 if ( i > 0 ){ dp[x][i][j][0] = max( dp[x][i-1][j][0] , dp[x][i][j][0] ); dp[x][i][j][1] = max( dp[x][i-1][j][1] , dp[x][i][j][1] ); }
			 if ( j > 0 ){ dp[x][i][j][0] = max( dp[x][i][j-1][0] , dp[x][i][j][0] ); dp[x][i][j][1] = max( dp[x][i][j-1][1] , dp[x][i][j][1] ); }
			 if ( s[k] ){
				/* Not using FREE */
				if ( p[k] <= i && dp[1-x][i-p[k]][j][0] >= 0 ) dp[x][i][j][0] = max( dp[x][i][j][0] , dp[1-x][i-p[k]][j][0] + h[k] );
				if ( p[k] <= j && dp[1-x][i][j-p[k]][0] >= 0 ) dp[x][i][j][0] = max( dp[x][i][j][0] , dp[1-x][i][j-p[k]][0] + h[k] );
				/* using FREE */
				if ( p[k] <= i && dp[1-x][i-p[k]][j][1] >= 0 ) dp[x][i][j][1] = max( dp[x][i][j][1] , dp[1-x][i-p[k]][j][1] + h[k] );
				if ( p[k] <= j && dp[1-x][i][j-p[k]][1] >= 0 ) dp[x][i][j][1] = max( dp[x][i][j][1] , dp[1-x][i][j-p[k]][1] + h[k] );
				if ( dp[1-x][i][j][0] >= 0 ) dp[x][i][j][1] = max( dp[x][i][j][1] , dp[1-x][i][j][0] + h[k] );
			 }
			 else {
				/* Not using FREE */
				dp[x][i][j][0] = max( dp[1-x][i][j][0] , dp[x][i][j][0] );
				if ( p[k] <= i && dp[1-x][i-p[k]][j][0] >= 0 ) dp[x][i][j][0] = max( dp[x][i][j][0] , dp[1-x][i-p[k]][j][0] + h[k] );
				if ( p[k] <= j && dp[1-x][i][j-p[k]][0] >= 0 ) dp[x][i][j][0] = max( dp[x][i][j][0] , dp[1-x][i][j-p[k]][0] + h[k]);
				/* using FREE */
				dp[x][i][j][1] = max( dp[1-x][i][j][1] , dp[x][i][j][1] );
				if ( p[k] <= i && dp[1-x][i-p[k]][j][1] >= 0 ) dp[x][i][j][1] = max( dp[x][i][j][1] , dp[1-x][i-p[k]][j][1] + h[k] );
				if ( p[k] <= j && dp[1-x][i][j-p[k]][1] >= 0 ) dp[x][i][j][1] = max( dp[x][i][j][1] , dp[1-x][i][j-p[k]][1] + h[k]);
				if ( dp[1-x][i][j][0] >= 0 ) dp[x][i][j][1] = max( dp[x][i][j][1] , dp[1-x][i][j][0] + h[k] );
			 }
			 
		  }
		x = 1 - x;
	 }
	 printf("Case %d: %d\n\n",runs,dp[1-x][a][b][1]);
  }
  return 0;
}
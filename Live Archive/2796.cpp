#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[2][366][366] = {0};
struct triple {
  int x,y,z;
  bool operator<(const triple &that) const {
	 if (y!=that.y) return y < that.y;
	 return x < that.x;
  }
};

triple a[1002];

int main(){

  int n;
  int i,j,k;
  while (scanf("%d",&n) && n){
	 for (i=1; i <= n; ++i)
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].z);
	 sort(a+1,a+n+1);
	 memset(dp,0,sizeof(dp));
	 int x = 1;
	 for (i=1; i <= n; ++i){
		for (j=1; j <= 365; ++j)
		  for (k=1; k <= 365; ++k){
			 dp[x][j][k] = max( dp[1-x][j][k] , dp[x][j][k-1]);
			 if (dp[x][j][k] < dp[x][j-1][k]) dp[x][j][k] = dp[x][j-1][k];
			 if ( j >= a[i].y && dp[x][j][k] < (dp[ 1 - x ][ a[i].x - 1 ][ k ] + a[i].z) )
				dp[x][j][k] = dp[ 1-x ][ a[i].x - 1 ][ k ] + a[i].z;
			 if (k >= a[i].y && dp[x][j][k] < (dp[ 1-x ][ j ][ a[i].x - 1 ] + a[i].z) )
				dp[x][j][k] = dp[ 1-x ][ j ][ a[i].x - 1 ] + a[i].z;
		  }
		x = 1 - x;
	 }
	 printf("%d\n",dp[1-x][365][365]);
  }

  return 0;
}
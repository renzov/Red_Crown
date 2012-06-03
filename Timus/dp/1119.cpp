#include<cstdio>
#include<cmath>
#include<set>
using namespace std;

float dp[1002][1002];
const float d = 100.0 * sqrt((float)2.0);
set< pair<int,int> > s;
int main(){
  int n,m;
  int k;
  int x,y;

  scanf("%d %d",&m,&n);
  for (int i=0; i <= n; ++i)
	 for (int j=0; j <= m; ++j)
		dp[i][j] = 10e10;
  scanf("%d",&k);
  
  for (int i=0; i < k; ++i){
	 scanf("%d %d",&x,&y);
	 x--,y--;
	 s.insert( make_pair(x,y) );
  }
  dp[0][0] = 0.0;
  for (int i=0; i <= n; ++i){
	 for (int j=0; j <= m; ++j){
		  if ((dp[i][j] + 100.0) < dp[i+1][j]){
			 dp[i+1][j] = dp[i][j] + 100.0; 
		  }
		  if ((dp[i][j] + 100.0) < dp[i][j+1]){
			 dp[i][j+1] = dp[i][j] + 100.0;
		  }
		  if (s.find( make_pair(j,i) ) != s.end() && ( (dp[i][j] + d) < dp[i+1][j+1] ) ){
			 dp[i+1][j+1] = dp[i][j] + d;
		  }
	 }
  }
  
  printf("%0.lf\n",dp[n][m]);
  return 0;

}
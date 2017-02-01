#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double INF = 10e10; 
const double EPS = 0.0001;
double C[100005];
int T[100005];

int t[105];
double dp[2][100005];

int main(){
  double res;
  int N,M;
  int x;
  while ( scanf("%d %d",&M,&N) && N ){
	 for ( int i=1; i <= M; ++i ) scanf("%d",t+i);
	 for ( int i=1; i <= N; ++i ){
		scanf("%d %lf",T+i,C+i);
		dp[0][i] = 0.0; dp[1][i] = INF;
	 }
	 dp[0][0] = 0.0;
	 dp[1][0] = INF;
	 x = 1;
	 for ( int i=1; i <= M; ++i ){
		for ( int j=1; j <= N; ++j){
		  dp[x][j] = dp[x][j-1];
		  if ( t[i] == T[j] && dp[1-x][j-1] < INF ){
			 dp[x][j] = min( dp[x][j] , dp[1-x][j-1] + C[j] );
		  }
		}
		x = 1 - x;
		if ( i < N ){
		  for ( int j=0; j <= N; ++j ) dp[x][j] = INF;
		}
	 }
	 if ( dp[1-x][N] < INF ){
		res = floor( dp[1-x][N]*100.0 + .5 )/100.0;
		printf("%0.2lf\n",res);
	 }
	 else {
		puts("Impossible");
	 }
  }
  return 0;
}
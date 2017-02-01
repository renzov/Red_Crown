#include<cstdio>

long long dp[ 11 ][ 2005 ];
int m;
int n;

long long solve( int init , int left ){
  if (left == 0) return 1;
  if (init > m) return 0;
  if (dp[ left ][ init ] != -1) return dp[left][init];
  dp[left][init] = 0;
  for (int i=init; i <= (m>>(left-1)); ++i){
		dp[left][init] += solve(i<<1,left-1);
  }
  return dp[left][init];
}

int main(){
  int runs;
  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
		scanf("%d %d",&n,&m);
		for (int i=1; i <= n; ++i){
		  for (int j=0; j <= m; ++j)
			 dp[i][j] = -1;
		}
		printf("Data set %d: %d %d %lld\n",k,n,m,solve(1,n));
  }
  return 0;
}
#include<cstdio>

long long dp[250][250] = {0};
long long res[250] = {0};

int main(){
  int x,y;
  res[1] = 1;
  for (int i=2;  i < 250; ++i){
	 for (int j=1; ; ++j){
		  x = i - 2*j;
		  if (x < j) break;
		  dp[i][j] = 0;
		  for (int k=j; ; ++k){
			 y = x - 2*k;
			 if (y < k) break;
			 dp[i][j] += dp[x][k];
		  }
		  dp[i][j]++; // j x j
		  if ( !(x & 1) && (x/2 >= j) ) dp[i][j]++; // j x/2 x/2 j
		  res[i] += dp[i][j];
	 }
	 res[i]++;
	 if ( !(i & 1) ){ res[i]++; }
  }  
  int n;
  while (scanf("%d",&n) && n){
	 printf("%d %lld\n",n,res[n]);
  }
  return 0;
}
#include<cstdio>
#include<climits>

int dp[10005];

inline int min(int a,int b){  return a<=b? a:b; }

int main(){
  dp[1] = 1;
  dp[0] = 0;
  for (int i=2; i <= 10000; ++i){
	 dp[i] = INT_MAX;
	 for (int j=1; j*j <= i; ++j)
		dp[i] = min(dp[i],dp[i-j*j] + 1);
  }
  int runs;
  int n;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 printf("%d\n",dp[n]);
  }
  return 0;
}
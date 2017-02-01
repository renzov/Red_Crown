#include<cstdio>
#include<cmath>
const int MOD = 1000000;
int dp[1000002];

int main(){
  dp[0] = 1;
  int a,b,c;
  for(int i=1; i<= 1000000; ++i){
	 a = i - sqrt(i);
	 b = log(i);
	 c = i * sin(i) * sin(i);
	 dp[i] = (dp[a] + dp[b] + dp[c]) % MOD; 
  }
  int n;
  while (scanf("%d",&n) && n >= 0){
		printf("%d\n",dp[n]);
  }
  return 0;
}
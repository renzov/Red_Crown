#include<cstdio>

long long dp[27][400][27] = {0};

int main(){

  for (int i=1; i <= 26; ++i) dp[1][i][i] = 1;
  for (int i=2; i <= 26; ++i)
	 for (int s=1; s <= 351; ++s)
		for (int c=1; c <= 26; ++c){
		  if ( (s - c) >= 0 ){
			 for (int k=c+1; k <= 26; ++k){
				dp[i][s][c] += dp[i-1][s-c][k];
			 }
		  }
		}
  int L,S;
  int runs = 0;
  while (scanf("%d %d",&L,&S) && L){
		runs++;
		if ( L > 26 || S > 351 ) printf("Case %d: 0\n",runs);
		else {
		  long long res = 0LL;
		  for (int i=1; i <= 26; ++i) res += dp[L][S][i];
		  printf("Case %d: %lld\n",runs,res);
		}
  }
  return 0;
}
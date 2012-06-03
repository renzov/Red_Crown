#include<cstdio>
#include<cstring>
long long dp[11][21];

inline int abs(int a){ return a<0? -a:a; }

int main(){
  int n,q;
  int w[202];
  int d,m;
  int a,b;
  int runs = 0;
  while (scanf("%d %d",&n,&q) && n){
	 runs++;
	 printf("SET %d:\n",runs);
	 for (int t=1; t <= n; ++t){
		scanf("%d",w+t);
	 }
	 for (int c=1; c <= q; ++c){
		scanf("%d %d",&d,&m);
		memset(dp,0,sizeof(dp));
		dp[0][0] = 1;
		for (int t=1; t <= n; ++t){
		  a = w[t];
		  if (a < 0){
			 b = abs(a);
			 a += ((b/d)*d);
			 if (a < 0) a+=d;
		  }
		  else {
			 a %= d;
		  }
		  for (int i=m-1; i >= 0; --i){
			 for (int j=0; j < d; ++j){
				if ( dp[i][j] > 0){ 
					 dp[i+1][(j+a)%d] += dp[i][j]; 
				}
			 }
		  }
		}
		printf("QUERY %d: %lld\n",c,dp[m][0]);
	 }
  }
  return 0;
}
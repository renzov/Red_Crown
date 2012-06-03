#include<cstdio>

int M[200][200];
int dp[200][200] = {0};

int main(){

  int runs;
  int n,tmp;
  
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		for (int i=1; i <= n; ++i){
		  for (int j=1; j <= n; ++j){
			 scanf("%d",&M[i][j]);
			 M[i + n][j + n] = M[i + n][j] = M[i][j + n] = M[i][j];
		  }
		}
		for (int i=1; i <= 2*n; ++i){
		  for (int j=1; j <= 2*n; ++j){
				dp[i][j] = M[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1]; 
		  }
		}
		/* Finding best ans */
		int best = -999999999;
		
		for (int i=1; i <= n; ++i){
			 for (int j=i; j < (i+n); ++j){
				  for (int k=1; k <= n; ++k){
						for (int l=k; l < (k+n); ++l){
							 tmp = dp[j][l] + dp[i-1][k-1] - dp[i-1][l] - dp[j][k-1];
							 if (tmp > best) best = tmp;
						}
				  }
			 }
		}
		
		printf("%d\n",best);

  }
  return 0;
}
#include<cstdio>
#include<climits>
#include<cmath>

int idx[15];
int L[15][105];
int dp[15][105];

inline int max(int a,int b){ return a>=b? a:b; }

int main(){
  int runs;
  int n,m;
  bool found;
  bool ok;

  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&n,&m);
	 ok = true;
	 for (int i=0; i < n; ++i){
		  found = false;
		  for (int j=1; j <= m; ++j){
			 scanf("%d",&L[i][j]);
			 if (!found && L[i][j] > 4){
				idx[i] = j; found = true;
			 }
		  }
		  if (!found) ok = false;
	 }

	 if (!ok){ puts("Peter, you shouldn't have played billiard that much."); continue; }

	 for (int i=0; i < n; ++i)
		for (int j=0; j <= m; ++j)
		  dp[i][j] = -INT_MAX;
	 
	 for (int j=0; j <= m; ++j){
		for (int k=idx[0]; k <= j && k <= m; ++k){
			 dp[0][j] = L[0][k];
		}
	 }

	 for (int i=1; i < n; ++i){
		for (int j=1; j <= m; ++j){
		  dp[i][j] = dp[i][j-1];
		  for (int k=idx[i]; k <= j && k <= m; ++k){
			 if (dp[i-1][j-k] > -INT_MAX){
				dp[i][j] = max( dp[i][j] , dp[i-1][j-k] + L[i][k] );
			 }
		  }
		}
	 }

	 if ( dp[n-1][m] == -INT_MAX ) puts("Peter, you shouldn't have played billiard that much.");
	 else {
		double res = (double)dp[n-1][m] / n;
		res = floor(res*100 + .5)/100;
		printf("Maximal possible average mark - %0.2lf.\n",res);
	 }
  }
  return 0;
}
#include<cstdio>

inline int max(int a,int b){
  return (a >= b)? a:b;
}

int basket;
int A[25] = {0};
int S[45][4] = {0};
int dp[45][45][45][45];
int n;
int ans;

int calcTaken(int a,int b,int c,int d){
  for (int i=1; i <= 20; ++i) A[i] = 0;

  for (int i=0; i < (n-a); ++i) A[ S[i][0] ]++; 
  for (int i=0; i < (n-b); ++i) A[ S[i][1] ]++;
  for (int i=0; i < (n-c); ++i) A[ S[i][2] ]++;
  for (int i=0; i < (n-d); ++i) A[ S[i][3] ]++;
  int take = 0;
  basket = 0;
  for (int i=1; i <= 20; ++i){
		take += (A[i] >> 1);
		basket += (A[i] & 1);
		if (basket > 5) return -1;
		A[i] &= 1;
  }
  return 1;
}

int main(){
  int take;
  while (scanf("%d",&n) && n){
		for (int i=0; i < n; ++i)
			 for (int j=0; j < 4; ++j)
				 scanf("%d",&S[i][j]); 
		for (int i=0; i <= n; ++i)
		  for (int j=0; j <= n; ++j)
			 for (int k=0; k <= n; ++k)
				for (int l=0; l <= n; ++l)
					 dp[i][j][k][l] = -1;
		dp[n][n][n][n] = 0;
		ans = 0;
		for (int i=n; i >= 0; --i)
		  for (int j=n; j >= 0; --j)
			 for (int k=n; k >= 0; --k)
				 for (int l=n; l >= 0; --l){
					 if (dp[i][j][k][l] == -1) continue;
					 if (ans < dp[i][j][k][l]) ans = dp[i][j][k][l];
					 take = calcTaken(i,j,k,l);
					 if (basket >= 5 || take == -1) continue;
					 if (i > 0){
						 dp[i-1][j][k][l] = max(dp[i-1][j][k][l],dp[i][j][k][l] + (A[ S[n - i][0] ] & 1));
					 }
					 if (j > 0){
						 dp[i][j-1][k][l] = max(dp[i][j-1][k][l],dp[i][j][k][l] + (A[ S[n - j][1] ] & 1));
					 }
					 if (k > 0){
						 dp[i][j][k-1][l] = max(dp[i][j][k-1][l],dp[i][j][k][l] + (A[ S[n - k][2] ] & 1));
					 }
					 if (l > 0){
						 dp[i][j][k][l-1] = max(dp[i][j][k][l-1],dp[i][j][k][l] + (A[ S[n - l][3] ] & 1));
					 }
				 }
		printf("%d\n",ans);
  }

  return 0;
}
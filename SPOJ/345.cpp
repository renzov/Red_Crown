#include<cstdio>
#include<climits>
int a[105] = {0};
int memo[105][105];

int solve(int l,int r){
  if (memo[l][r] != -1) return memo[l][r];
  if (l==r){
	 memo[l][l] = 0;
	 return memo[l][l];
  }
  int best = INT_MAX;
  int t1,t2;
  int c1,c2;
  int tmp;
  for (int i=l; i < r; ++i){
	 t1 = solve(l,i);
	 t2 = solve(i+1,r);
	 c1 = (a[i] - a[l-1])%100;
	 c2 = (a[r] - a[i])%100;
	 tmp = t1 + t2 + c1*c2;
	 if (tmp < best) best = tmp;
  }
  memo[l][r] = best;
  return memo[l][r];
}

int main(){

  int runs;
  int n;
  int x;
  while (scanf("%d",&n) == 1){
	 for (int i=1; i <= n; ++i){
		scanf("%d",&x);
		a[i] = a[i-1] + x;
	 }
	 for (int i=1; i <= n; ++i)
		for (int j=1; j <= n; ++j)
		  memo[i][j] = -1;
	 printf("%d\n",solve(1,n));
  }

  return 0;
}
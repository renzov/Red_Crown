#include<cstdio>
#include<climits>
int memo[255][255][255];
int f[255];

int solve(int l,int r,int h){
  if (memo[l][r][h] != -1) return memo[l][r][h];
  if (l==r) return memo[l][r][h] = f[l]*h;
  memo[l][r][h] = INT_MAX;
  int tmp,left,right;
  for (int i=l; i <= r; ++i){
	 left = i-1;
	 right = i+1;
	 tmp = h*f[i];
	 if (left >= l) tmp += solve(l,left,h+1);
	 if (right <= r) tmp += solve(right,r,h+1);
	 if (tmp < memo[l][r][h]) memo[l][r][h] = tmp;
  }
  return memo[l][r][h];
}

int main(){
  int n;
  while (scanf("%d",&n) != EOF){
		for (int i=0; i<n; ++i){
		  scanf("%d",f+i);
		}
		for (int i=0; i < n; ++i)
		  for (int j=0; j < n; ++j)
			 for (int k=0; k < n; ++k)
				memo[i][j][k] = -1;
		printf("%d\n",solve(0,n-1,0));
  }
  return 0;
}
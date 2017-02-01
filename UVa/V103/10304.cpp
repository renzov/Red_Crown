#include<cstdio>
#include<climits>
int memo[255][255];
int f[255];

int solve(int l,int r){
  if (memo[l][r] != -1) return memo[l][r];
  if (l==r) return memo[l][r] = 0;
  memo[l][r] = INT_MAX;
  
  int sum = 0;

  for ( int i=l; i<=r; ++i ){
  	sum += f[i];
  }

  int tmp,left,right;
  
  for (int i=l; i <= r; ++i){
	 left = i-1;
	 right = i+1;
	 tmp = sum - f[i];
	 if (left >= l) tmp += solve(l,left);
	 if (right <= r) tmp += solve(right,r);
	 if (tmp < memo[l][r]) memo[l][r] = tmp;
  }
  return memo[l][r];
}

int main(){
  int n;
  while (scanf("%d",&n) != EOF){
		for (int i=0; i<n; ++i){
		  scanf("%d",f+i);
		}
		for (int i=0; i < n; ++i)
		  for (int j=0; j < n; ++j)
				memo[i][j] = -1;
		printf("%d\n",solve(0,n-1));
  }
  return 0;
}

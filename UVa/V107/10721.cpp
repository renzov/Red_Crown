#include<cstdio>
#include<cstring>
long long memo[55][55][55];

long long solve(int n, int k,int m){
  if (n == 0 || k == 0) return k==0 && n==0;
  if (memo[n][k][m] != -1) return memo[n][k][m];
  memo[n][k][m] = 0LL;
  for (int i=1; i <= m && ((n - i) >= 0); ++i){
	 memo[n][k][m] += solve( n-i , k - 1 , m );
  }
  return memo[n][k][m];
}

int main(){
  int n,k,m;
  memset(memo,-1,sizeof(memo));
  while (scanf("%d %d %d",&n,&k,&m) == 3){
	 printf("%lld\n",solve(n,k,m));
  }

  return 0;
}
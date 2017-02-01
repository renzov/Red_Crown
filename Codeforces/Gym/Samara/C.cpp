#include<iostream>
#include<cstdio>
using namespace std;

const long long MOD = 1000000007;
long long dp[250][250] = {0};
int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n,m;
  scanf("%d %d",&n,&m);
  for ( int j=1; j <= m; ++j ) dp[1][j] = 1;
  for ( int i=2; i <= n; ++i ){
	 for ( int j=1; j <= m; ++j ){
		for ( int k=1; k < j; ++k )
		  dp[i][j] += dp[i-1][k];
		  dp[i][j] %= MOD; 
	 }
  }
  int res = 0;
  for ( int i=1; i <= m; ++i ){ res += dp[n][i]; res %= MOD; }
  cout << res << endl;
  return 0;
}
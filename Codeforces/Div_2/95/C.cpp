#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

long long memo[35][35];

long long comb(int n,int k){
  if (n==k) return 1;
  if (k==0) return 1;
  if ( memo[n][k] != -1 ) return memo[n][k];
  memo[n][k] = comb(n-1,k-1) + comb(n-1,k);
  return memo[n][k];
}

int main(){

  int n,m,t;
  memset(memo,-1,sizeof(memo));
  cin >> n >> m >> t;
  long long res = 0;
  for (int i=4; i <= min(t-1,n); ++i){
	 if ( m >= (t-i) ) res += comb( n , i ) * comb( m , t-i ); 
  }
  cout << res << endl;
  return 0;
}
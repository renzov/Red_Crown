#include<iostream>
#include<cstring>
using namespace std;
const int MOD = 1000000007;

long long memo[1005][1005];

long long solve(int l,int k){
  if ( k == 0 ) return 1;
  if ( l <= 0 ) return 0;
  if ( memo[l][k] != -1 ) return memo[l][k];
  long long res = 0;
  for ( int i=1; i < l-1; ++i ){
	 res += (l-i-1) * solve( i , k - 1 );
  }
  res %= MOD;
  return memo[l][k] = res;
}

int main(){
  int n,m,k;
  cin >> n >> m >> k;
  memset(memo,-1,sizeof(memo));
  cout << ( solve( n , k ) * solve( m , k ) ) % MOD << endl;
  return 0;
}
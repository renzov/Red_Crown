#include<cstdio>
#include<cstring>

long long memo[501][501];

long long solve( int cant , int last ){
  if ( cant == 0 ) return 1;
  if ( cant <= last ) return 0;
  if ( memo[cant][last] != -1 ) return memo[cant][last];
  memo[cant][last] = 0;
  for ( int i=last+1; i <= cant; ++i ){
	 memo[cant][last] += solve( cant-i , i );
  }
  return memo[cant][last];
}

int main(){
  int n;
  memset( memo, -1, sizeof(memo) );
  scanf("%d",&n);
  printf("%lld\n",solve(n,0)-1);
  return 0;
}
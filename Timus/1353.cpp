#include<cstdio>
#include<cstring>
int memo[11][90];

long long solve( int pos, int sum ){
  if ( pos == 9 ) return (sum==0);
  if ( memo[pos][sum] != -1 ) return memo[pos][sum];
  memo[pos][sum] = 0;
  for ( int i=0; i <= 9; ++i ){
	 if ( i <= sum ){
		memo[pos][sum] += solve( pos + 1 , sum - i );
	 }
	 else break;
  }
  return memo[pos][sum];
}

int main(){
  int s;
  scanf("%d",&s);
  long long res = 0;
  memset( memo , -1 , sizeof(memo) );
  res += solve( 0 , s );
  if ( s == 1 ) res++;
  printf("%lld\n",res);
  return 0;
}
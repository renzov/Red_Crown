#include<cstdio>
#include<cstring>
int memo[56][56][1541];
int n;
int solve( int pos, int prev, int sum ){
  if ( pos == n ) return (sum==0);
  if ( memo[pos][prev][sum] != -1 ) return memo[pos][prev][sum];
  memo[pos][prev][sum] = 0;
  if ( prev > 2 && (sum-prev) >= -2 ) memo[pos][prev][sum] += solve( pos + 1 , prev-2, sum - prev + 2 );
  if ( prev > 1 && (sum-prev) >= -1 ) memo[pos][prev][sum] += solve( pos + 1 , prev-1, sum - prev + 1 );
  if ( prev < n && (sum-prev) >= 1 ) memo[pos][prev][sum] += solve( pos + 1 , prev+1, sum - prev - 1 );
  if ( prev < (n-1) && (sum-prev) >= 2 ) memo[pos][prev][sum] += solve( pos + 1, prev+2, sum - prev - 2 );
  return memo[pos][prev][sum];
}

int main(){
  int s;
  scanf("%d",&n);
  s = ( n*(n+1) ) >> 1;
  memset(memo,-1,sizeof(memo));
  printf("%d\n",solve(1,1,s-1));
  return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF = 100000;
int memo[2][101][101];
int n,m;
int C[101];

int solve( int used, int left , int right ){
  if ( left >= right ) return 0;
  if ( (right - left) == 1 ) return 1 - used;
  if ( memo[used][left][right] != -1 ) return memo[used][left][right];
  int res = solve( 0 , left + 1 , right );
  int i;
  for ( i = left + 1; i < right; ++i ){
	 if ( C[left] == C[i] ){
		res = min( res , solve(0,left+1,i) + solve( 1 , i , right ) );
	 }
  }
  res += (1 - used);
  memo[used][left][right] = res;
  return res;
}

int main(){
  int runs,k,i;
  scanf("%d",&runs);
  for ( k=1; k<=runs; ++k ){
	 scanf("%d %d",&n,&m);
	 for ( i=0; i < n; ++i ) scanf("%d",C+i);
	 memset(memo,-1,sizeof(memo));
	 printf("Case %d: %d\n",k,solve(0,0,n));
  }
  return 0;
}
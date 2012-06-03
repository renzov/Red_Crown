#include<cstdio>
#include<algorithm>
using namespace std;
const int MOD = 100000000;
struct point{
  int x,y;
  bool operator<( const point &that ) const {
	 if ( y != that.y ) return y < that.y;
	 return x < that.x;
  } 
};

int n,m;
point p[105];
int dp[105][105];

bool intersect( int a, int b ){
  if ( p[a].x >= p[b].x && p[a].y <= p[b].y ) return false;
  if ( p[b].x >= p[a].x && p[b].y <= p[a].y ) return false;
  return min( p[a].y , p[b].y ) >= max( p[b].x , p[a].x );
}

int solve( int head, int last ){
  int k;
  if ( p[last].x == 0 ) return 1;
  if ( dp[head][last] != -1 ) return dp[head][last];
  dp[head][last] = 0;
  for ( k = last - 1; k >= 0; --k ){
	 if ( p[k].y < p[head].x && p[k].y >= p[last].x 
		  && p[k].x < p[last].x){
		dp[head][last] += solve( last , k );
		dp[head][last] %= MOD;
	 }
  }
  return dp[head][last];
}

int main(){
  int i,j;
  int res;
  while ( scanf("%d %d",&m,&n) && m ){
	 for (i=0; i < n; ++i){
		scanf("%d %d",&p[i].x,&p[i].y);
	 }
	 for (i=0; i < n; ++i)
		for (j=0; j < n; ++j) 
		  dp[i][j] = -1;
	 sort(p,p+n);
	 res = 0;
	 for (i=n-1; i >= 0; --i){
		if ( p[i].y == m ){
		  if ( p[i].x == 0 ) res = (res + 1)%MOD;
		  else {
			 for ( j = i-1; j >= 0; --j ){
				if ( intersect( i , j ) ){
				  res += solve( i , j );
				  res %= MOD;
				}
			 }
		  }
		}
	 }
	 printf("%d\n",res);
  }
  return 0;
}
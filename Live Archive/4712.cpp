#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct point{
  int x,y;
  bool operator<(const point &that) const {
	 if (y != that.y) return y < that.y;
	 return x > that.x;
  }
};

struct elem{
  int pos;
  int v;
  bool operator<(const elem &that) const {
	 return v < that.v;
  }
};

elem L[650];
point p[350];
int dp[2][650][650];

int main(){
  int m,last;
  int runs;
  int n;
  int l,r;
  int i,j,k;
  int x;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (i=0; i < n; ++i){
		scanf("%d %d",&p[i].x,&p[i].y);
		L[i<<1].v = p[i].x; L[i<<1].pos = -(i+1);
		L[(i<<1) + 1].v = p[i].y; L[(i<<1)+1].pos = (i+1);
	 }
	 sort(L,L+(n<<1));
	 last = L[0].v; m=0;
	 for (i=0; i < (n<<1); ++i){
		if (last != L[i].v){ m++; last = L[i].v; }
		if (L[i].pos < 0) p[ -L[i].pos - 1 ].x = m;
		else p[ L[i].pos - 1 ].y = m;
	 }
	 sort(p,p+n);
	 
	 memset(dp,0,sizeof(dp));
	 
	 x = 1;
	 for (i=0; i < n; ++i){
		for (k=1; k <= m; ++k)
		  for (j=0; (j+k) <= m ; ++j){
			 l = j; r = j+k;
			 dp[x][l][r] = dp[1-x][l][r];
			 if ( l <= p[i].x && p[i].y <= r ){
				dp[x][l][r] = max( dp[x][l][r] , dp[1-x][l][ p[i].x ] + dp[1-x][ p[i].x ][ p[i].y ] + 1 );
			 }
		  }
		x = 1 - x;
	 }
	 printf("%d\n",dp[1-x][0][m]);
  }
  return 0;
}
#include<cstdio>
#include<cstring>

long long dp[12][12][1<<11] = {0};
int p,q;
int w;
int m;

void solve( int i ){
  if ( i >= w ){
	 dp[w][m+1][q] += dp[w][m][p];
	 return;
  }
  if ( (p>>i) & 1 ){
	 solve(i+1);
	 return;
  }
  if ( (i+1) < w && !((p>>(i+1))&1) ){
	 solve(i+2);
  }
  if ( !((q>>i)&1) ){
	 q ^= (1<<i);
	 solve(i+1);
	 q ^= (1<<i);
  }
}

void precalc(){
  for ( w=2; w <= 11; ++w ){
	 dp[w][0][0] = 1;
	 for ( m = 0; m < 11; ++m ){
		for ( p=0; p < (1<<w); ++p ){
		  q = 0;
		  solve(0);
		}
	 }
  }
}

int main(){
  int h;
  precalc();
  while ( scanf("%d %d",&h,&w) && h ){
	 if ( w==1 ){
		printf("%d\n",1-(h%2));
	 }
	 else {
		printf("%lld\n",dp[w][h][0]);
	 }
  }
  return 0;
}
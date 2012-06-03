#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
bool has_sur[35];
int max_sur[35];
int max_sin[35];

void update( int val, int a , int b, int c ,int sur ){
  if ( sur ){
	 has_sur[val] = true;
	 max_sur[val] = max( max_sur[val], c );
  }
  else {
	 max_sin[val] = max( max_sin[val] , c );
  }
}

int init(){
  int r,m;
  fill( has_sur , has_sur + 31 , false );
  fill( max_sur , max_sur + 31 , -1 );
  fill( max_sin , max_sin + 31 , -1 );
  for ( int i=0; i <= 30; ++i ){
	 r = i%3;
	 if ( r == 0 ){
		m = i/3;
		update(i,m,m,m,false);
		if ( i >= 3 ){
		  m = (i-3)/3;
		  update(i,m,m+1,m+2,true);
		}
	 }
	 else if ( r == 1 ){
		m = (i-1)/3;
		update(i,m,m,m+1,false);
		if ( i >= 4 ){
		  m = (i-4)/3;
		  update(i,m,m+2,m+2,true);
		}
	 }
	 else if ( r == 2 ){
		  m = (i - 2)/3;
		  update( i , m , m+1 , m+1 , false );
		  update( i , m , m , m + 2 , true );
	 }
  }
}

int main(){
  init();
  int dp[105][105];
  // int dp[n][s] = max_cant de puntajes que son mayores o iguales a P tomando a los n primeros elementos con s suprising
  int P;
  int s,n;
  int v[105];
  int runs;
  scanf("%d",&runs);
  for ( int k=1; k<=runs; ++k ){
	 scanf("%d %d %d",&n,&s,&P);
	 for ( int i=1; i <= n; ++i ) scanf("%d",v+i);
	 //init dp
	 for ( int i=0; i <= n; ++i )
		for ( int j=0; j <= s; ++j )
			 dp[i][j] = -INT_MAX;
	 dp[0][0] = 0;
	 for ( int j=1; j <= s; ++j ){
		dp[0][j] = -INT_MAX;
	 }
	 for ( int i=1; i <= n; ++i ){
		dp[i][0] = dp[i-1][0];
		if ( (dp[i][0] > -INT_MAX) && max_sin[v[i]] >= P ) dp[i][0]++;
	 }
	 for ( int j=1; j <= s; ++j ){
		for ( int i=1; i <= n; ++i ){
		  dp[i][j] = -INT_MAX;
		  if ( has_sur[ v[i] ] ){
			 if ( max_sur[ v[i] ] < P ) {
				dp[i][j] = max( dp[i][j] , dp[i-1][j-1] ); }
			 else {
				dp[i][j] = max( dp[i][j] , dp[i-1][j-1] + 1); } 
		  }
		  if ( max_sin[ v[i] ] >= P ){
			 dp[i][j] = max( dp[i][j] , dp[i-1][j] + 1 );
		  }
		  else {
			 dp[i][j] = max( dp[i][j] , dp[i-1][j] );
		  }
		}
	 } 
	 printf("Case #%d: %d\n",k,dp[n][s]);
  }
  return 0;
}
#include<cstdio>
#include<cstring>

long long dp[1005][1<<4] = {0};
int row;
int state;
int next;

void search( int col ){
  if ( col == 4 ){
	 dp[ row+1 ][ next ] += dp[row][state];
	 return;
  }
  if ( (state >> col) & 1 ){ search( col + 1 ); return; }
  if ( (col + 1) < 4 && !( (state >> (col+1)) & 1 ) ){
	 search( col + 2 );
  }
  if (!( (next >> col) & 1 )){
	 next ^= ( 1 << col );
	 search( col + 1 );
	 next ^= ( 1 << col );
  }
}

int main(){
  dp[0][0] = 1;
  // Precalc
  for ( row=0; row < 1000 ; ++row ){
	 for ( state=0; state < 16; ++state ){
		next = 0;
		if ( dp[row][state] )
		  search( 0 );
	 }
  }
  int n;
  int runs;
  scanf("%d",&runs);
  for ( int k=1; k<=runs; ++k ){
	 scanf("%d",&n);
	 printf("%d %lld\n",k,dp[n][0]);
  }
  return 0;
}
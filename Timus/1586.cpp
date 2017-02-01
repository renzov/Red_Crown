#include<cstdio>
#include<cstring>
const int MAX = 1000;
const int MOD = 1000000009;

bool nsp[MAX] = {0};  
int m;
int prim[150];
int is_tp[MAX];

void sieve(){
  int i,j;
  memset( is_tp , -1 , sizeof(is_tp) );
  m = 0;
  for ( i=4; i < MAX; i+=2 ) nsp[i] = true;
  for ( i=3; i < MAX ; i += 2 ){
	 if ( !nsp[i] ){
		if ( i > 100 ){ is_tp[i] = m; prim[m++] = i; }
		for ( j=i*i ; j < MAX ; j += (2*i) )
		  nsp[j] = true;
	 }
  }
}

int adj[150][10];
int dp[150][10001];

int solve( int p , int left ){
  if ( left == 0 ) return 1;
  if ( dp[p][left] != -1 ) return dp[p][left];
  dp[p][left] = 0;
  for ( int j = 1; j < 10 ; j += 2 ){
	 if ( adj[p][j] != -1 ){
		dp[p][left] += solve( adj[p][j] , left - 1 );
		dp[p][left] %= MOD;
	 }
  }
  return dp[p][left];
}

int main(){
  sieve();
  memset( adj , -1, sizeof(adj) );
  int u , v;
  for ( int i=0; i < m; ++i ){
	 u = prim[i];
	 v = u - (100*(u/100));
	 for ( int j=1; j < 10; j+=2 ){
		if ( is_tp[ v*10 + j ] != -1 )
			 adj[ i ][ j ] = is_tp[ v*10 + j ];
	 }
  }
  int res = 0;
  int n;
  scanf("%d",&n);
  for ( int i=0; i < m; ++i )
	 for ( int j=1; j < n; ++j )
		  dp[i][j] = -1;
  for ( int i=0; i < m; ++i ){
	 res += solve( i , n-3 );
	 res %= MOD;
  }
  printf("%d\n",res);
  return 0;
}
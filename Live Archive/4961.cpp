#include<cstdio>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
#define forn(i,n) for ( int i=0; i < (int)(n); ++i) 
using namespace std;
const int INF = 1000000000;
int k;
char lst[27];
int idx[256];
int C[27][27];
int R[27][27];
char s[250];
int dp[250][250][27];

int solve(int m){
  int id;
  fill( &dp[0][0][0] , &dp[m-1][m-1][k] , INF );
  forn( i , m ){
	 id = idx[ s[i] ];
	 dp[i][i][ id ] = 0; 
  }
  for ( int len = 1; len < m ; len++ ){
	 for ( int i=0; (i+len) < m; ++i ){
		for ( int j=i; j < (i+len); ++j ){
		  for ( int a=0; a < k; ++a ){
			 for ( int b=0; b < k; ++b ){
				if ( dp[i][i+len][ R[a][b] ] > ( dp[i][j][a] + dp[j+1][i+len][b] + C[a][b] ) ){
				  dp[i][i+len][ R[a][b] ] = ( dp[i][j][a] + dp[j+1][i+len][b] + C[a][b] );
				}
			 }
		  }
		}
	 }
  }
}

int main(){
  int cases = 0;
  char c;
  int q;
  int m;
  int best, bidx;
  int res;
  while ( scanf("%d",&k) && k ){
	 cases++;
	 forn(i,k){ scanf(" %c",&c); lst[i] = c; idx[c] = i; }
	 forn(i,k)
		forn(j,k){
		  scanf("%d-%c",&C[i][j],&c);
		  R[i][j] = idx[ c ];
		}
	 scanf("%d",&q);
	 if ( cases > 1 ) puts(""); 
	 forn(i,q){
		scanf("%s",s);
		m = strlen(s);
		solve(m);
		best = INF;
		forn( j , k ){
		  if ( dp[0][m-1][j] < best ){ best = dp[0][m-1][j]; bidx = j; }
		}
		printf("%d-%c\n",best,lst[bidx]);
	 }
  }
  return 0;
}
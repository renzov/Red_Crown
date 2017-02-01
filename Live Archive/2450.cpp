#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const char GRAY = 2;
const char BLACK = 1;
const char WHITE = 0;
vector<int> G[101];
int n;
int nc;
bool A[101][101];
int d[ 101 ];
bool bip;
int cnt[101][2];
int comp[101];
int B[101];
int W[101];
int nw,nb;
char color[101];
bool dp[101][202];
char pre[101][202];

inline int abs(int x){ return x>=0? x:-x; }

void dfs( int u, int p, char c ){
  color[u] = c; cnt[nc][c]++; comp[u] = nc;
  int v;
  for ( int i=0; i < G[u].size() && bip; ++i ){
	 v = G[u][i];
	 if ( v != p ){
		if ( color[v] == GRAY ) dfs(v,u,1-c);
		else if ( color[v] == color[u] ) bip = false;
	 }
  }
}

void backtrack( int c, int s ){
  if ( c < 1 ) return;
  if ( pre[c][s] == BLACK ){
	 char col = ( cnt[c-1][BLACK] >= cnt[c-1][WHITE] )? BLACK:WHITE; //Black debe tener la mayor cantidad 
	 for ( int i=0; i < n; ++i ){
		if ( comp[i] == (c-1)){
		  if ( color[i] == col ){ 
			 B[ nb++ ] = i;
		  }
		  else {
			 W[ nw++ ] = i;
		  }
		}
	 }
	 backtrack( c-1 , s + d[c-1] );
  }
  else {
	 char col = ( cnt[c-1][WHITE] >= cnt[c-1][BLACK] )? WHITE:BLACK; //White debe tener la mayor cantidad
	 for ( int i=0; i < n; ++i ){
		if ( comp[i] == (c-1) ){
		  if ( color[i] == col ){
			 W[nw++] = i;
		  }
		  else {
			 B[nb++] = i;
		  }
		}
	 }
	 backtrack( c-1 , s - d[c-1] );
  }
}

int main(){  
  int runs;
  int v;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&n);
	 memset( A , 0 , sizeof(A) );
	 for ( int i=0; i < n; ++i ){
		while ( scanf("%d",&v) && v ){
		  v--; A[i][v] = true;
		}
	 }
	 for ( int i=0; i < n; ++i ){
		color[i] = GRAY;
		G[i].clear();
		for ( int j=0; j < n; ++j ){
		  if ( i != j  && ( !A[i][j] || !A[j][i] ) ){
			 G[i].push_back(j);
		  }
		}
	 }
	 nc = 0; bip = true;
	 for ( int i=0; i < n && bip; ++i ){
		if ( color[i] == GRAY ){
		  cnt[nc][0] = cnt[nc][1] = 0;
		  dfs( i , -1 , BLACK );
		  d[ nc ] = abs( cnt[nc][0] - cnt[nc][1] );
		  nc++;
		}
	 }
	 if ( !bip ){ 
		printf("No solution\n");
	 }
	 else {
		for ( int i=1; i <= nc; ++i )
		  for ( int j=0; j <= 200; ++j )
				dp[i][j] = false;
		dp[0][100] = true;
		for ( int i=0; i < nc; ++i ){
		  for (int j=0; j <= 200; ++j){
			 if ( dp[i][j] ){
				if ( !dp[i+1][j-d[i]] ){
				  dp[i+1][j-d[i]] = true; pre[i+1][j-d[i]] = BLACK;
				}
				if ( !dp[i+1][j+d[i]] ){
				  dp[i+1][j+d[i]] = true; pre[i+1][j+d[i]] = WHITE;
				}
			 }
		  }
		}
		int bj,best = 10000;
		for ( int i=0; i <= 200; ++i ){
		  if ( dp[nc][i] && abs(i-100) < best ){
			 best = abs(i-100); bj = i;
		  }
		}
		nw = nb = 0;
		backtrack( nc , bj );
		if ( nw == 0 || nb == 0 ){
		  printf("No solution\n"); continue;
		}
		printf("%d",nw);
		for ( int i=0; i < nw; ++i ) printf(" %d",W[i]+1); putchar('\n');
		printf("%d",nb);
		for ( int i=0; i < nb; ++i ) printf(" %d",B[i]+1); putchar('\n');
	 }
	 if ( runs ) putchar('\n');
  }
  return 0;
}
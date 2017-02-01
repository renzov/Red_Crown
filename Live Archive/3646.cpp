#include<cstdio>
#include<cstring>

int R[300];
int C[300];
char M[25][35];
char X[505];
char Y[505];
int dp[505][505];

inline int max(int x,int y){ return x >= y? x:y; }

int Distance( char a, char b){
  int dr,dc;
  dr = ( R[a] > R[b] ) ? (R[a] - R[b]) : (R[b] - R[a]);
  dc = ( C[a] > C[b] ) ? (C[a] - C[b]) : (C[b] - C[a]);
  return (dr > dc)? dr:dc;
}

int main(){

  int r;
  int c;
  int n,m;
  int i,j;
  int d;
  int TOP;
  
  while (scanf("%d",&r) == 1){
	 gets(M[0]);
	 for (i=0; i < r; ++i) gets(M[i]);
	 c = strlen( M[0] );
	 
	 for (i=0; i<r; ++i)
		for (j=0; j<c; ++j){
			 R[ M[i][j] ] = i;
			 C[ M[i][j] ] = j;
		}
	 
	 if ( r > c ) TOP = r - 1;
	 else TOP = c - 1;
	 
	 gets(X);
	 gets(Y);

	 n = strlen(X);
	 m = strlen(Y);
	 
	 for (i=0; i <= n; ++i){
		dp[i][0] = -(TOP + 1) * i ;
	 }
	 for (j=0; j <= m; ++j){
		 dp[0][j] = -(TOP + 1) * j;
	 }
	 
	 for (i=1; i <= n; ++i){ 
		for (j=1; j <= m; ++j){
		  if ( X[i-1] == Y[j-1] ){
			 dp[i][j] = dp[i-1][j-1] + TOP + 1;
		  }
		  else {
			 d = Distance( X[i-1] , Y[j-1] );
			 dp[i][j] = dp[i-1][j-1] + TOP + 1 - d;
		  }
		  dp[i][j] = max( dp[i][j] , dp[i-1][j] - TOP - 1 );
		  dp[i][j] = max( dp[i][j] , dp[i][j-1] - TOP - 1 );
		}
	 }
	 printf("%d\n",dp[n][m]);
  }

  return 0;
}
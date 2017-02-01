#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[505][505];
int M[505][505];
int pre[505][505];
char pal[505][505][505];
int n;
/*
  dp[i][j] = min numero de caracteres cambiados de la cadena [i...len] con a lo mas j particiones
*/
char s[505];
int Min_Ch( int a, int b ){
  int res = 0;
  int i = 0;
  int x = a; 
  int y = b;
  for ( int j=a; j <= b; ++j,++i ) pal[a][b][i] = s[j];
  pal[a][b][i] = '\0';
  i = 0;
  while ( a < b ){
	 if ( s[a] != s[b] ){ res++; pal[x][y][i] = s[b]; }
	 a++,b--;
	 i++;
  }
  return res;
}

void print_cuts( int i , int j ){
  if ( j == 1 ){ printf("%s",pal[i][n-1]); return; }
  if ( pre[i][j] < 0 ){ print_cuts(i,j-1); }
  else {
	 int t = pre[i][j];
	 printf("%s+",pal[i][t-1]);
	 print_cuts( t , j - 1 );
  }
}

int main(){
  int k;
  scanf("%s",s); n = strlen( s );
  scanf("%d",&k);
  for ( int i=0; i < n; ++i ){
	 M[i][i] = 0;
	 pal[i][i][0] = s[i];
	 pal[i][i][1] = '\0';
	 for ( int j = i+1; j < n; ++j ){
		M[i][j] = Min_Ch(i,j);
	 }
  }
  for ( int i=0; i < n; ++i ){
	 dp[i][1] = M[i][n-1];
  }
  for ( int j=2; j <= k; ++j ){
	 for ( int i=0; i < n; ++i ){
		dp[ i ][ j ] = dp[i][j-1];
		pre[i][j] = -1;
		for ( int t=i+1; t < n; ++t ){
		  if ( (M[i][t-1] + dp[t][j-1]) < dp[i][j] ){
			 dp[i][j] = M[i][t-1] + dp[t][j-1];
			 pre[i][j] = t;
		  }
		}
	 }
  }
  printf("%d\n",dp[0][k]);
  print_cuts( 0 , k ); puts("");
  return 0;
}
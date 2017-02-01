#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
char M[100][100];
int dp[100][100];
string S[100][100];
pair<int,int> move[55][55];
int n;
const int INF = 1000;

int solve(int x,int y){
  if ( x == y ){
	 S[x][y] = "";
	 return 0;
  }
  if ( dp[x][y] != -1 ) return dp[x][y];
  /* you can always use one move */
  dp[x][y] = 1;
  S[x][y] = "";
  S[x][y] = M[x][y];
  int i,j,tmp;
  string t;
  for (i=x+1; i < y ; ++i){
	 for (j=y-1; j >= i; --j){
		if ( M[x][i] == M[j][y] ){
		  tmp = 2 + solve( i , j );
		  t = S[i][j];
		  t = M[x][i] + t;
		  t = t + M[j][y];
		  if ( dp[x][y] < tmp ){ dp[x][y] = tmp; S[x][y] = t; }
		  else if ( dp[x][y] == tmp && S[x][y] > t ){
			 S[x][y] = t;
		  }
		}
	 }
  }
  return dp[x][y];
}

int main(){
  int runs;
  int i,j;
  int res;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (i=0; i < n; ++i){
		for (j=0; j < n; ++j){ dp[i][j] = -1; scanf(" %c",&M[i][j]); }
	 }
	 solve(0,n-1);
	 cout << S[0][n-1] << endl;
  }
  return 0;
}
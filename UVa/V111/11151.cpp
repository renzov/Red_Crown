#include<cstdio>
#include<cstring>
char X[1005];
char Y[1005];
int n;
int L[1005][1005];

inline int max(int a,int b){ return a >= b? a:b; }

int LCS(){
  for (int i=0; i <= n; ++i) L[0][i] = L[i][0] = 0;
  for (int i=1; i <= n; ++i)
	 for (int j=1; j <= n; ++j){
		if ( X[i-1] == Y[j-1] ) L[i][j] = L[i-1][j-1] + 1;
		else L[i][j] = max( L[i-1][j] , L[i][j-1] );
	 }
  return L[n][n];
}

int main(){

  int runs;
  scanf("%d",&runs);
  while (getchar()!='\n');
  while (runs--){
	 gets(X);
	 n = strlen(X);
	 for (int i=n-1,j=0; i >= 0; i--,j++) Y[j] = X[i];
	 printf("%d\n",LCS());
  }
  return 0;
}
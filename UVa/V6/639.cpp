#include<cstdio>

int best;
int color[5][5];
char M[5][5];
int n;

void backtrack(int r,int c,int col){
  if (r>=n){
	 if (best < col) best = col;
	 return;
  }
  if (M[r][c] == '.' && color[r][c] == 0){
	 color[r][c] = col + 1;
	 for(int i=c+1; i < n && color[r][i]==0 && M[r][i]=='.'; ++i){
		  color[r][i] = col + 1;
	 }
	 for(int i=c-1; i >= 0 && color[r][i]==0 && M[r][i]=='.'; --i){
		  color[r][i] = col + 1;
	 }
	 for(int i=r+1; i < n && color[i][c]==0 && M[i][c]=='.'; ++i){
		color[i][c] = col + 1;
	 }
	 for(int i=r-1; i >= 0 && color[i][c]==0 && M[i][c]=='.'; --i){
		color[i][c] = col + 1;
	 }
	 
	 backtrack(r + (c==(n-1)),(c+1)%n,col + 1);
	 
	 for(int i=c+1; i < n && color[r][i]==color[r][c] && M[r][i]=='.'; ++i){
		  color[r][i] = 0;
	 }
	 for(int i=c-1; i >= 0 && color[r][i]==color[r][c] && M[r][i]=='.'; --i){
		  color[r][i] = 0;
	 }
	 for(int i=r+1; i < n && color[i][c]==color[r][c] && M[i][c]=='.'; ++i){
		color[i][c] = 0;
	 }
	 for(int i=r-1; i >= 0 && color[i][c]==color[r][c] && M[i][c]=='.'; --i){
		color[i][c] = 0;
	 }
	 color[r][c] = 0;
  }
  backtrack(r + (c==(n-1)),(c+1)%n,col);
}

int main(){

  while (scanf("%d",&n) && n){
	 for (int i=0; i < n; ++i)
		scanf("%s",M[i]);
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  color[i][j] = 0;
	 best = 0;
	 backtrack(0,0,0);
	 printf("%d\n",best);
  }

  return 0;
}
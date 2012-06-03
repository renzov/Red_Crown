#include<cstdio>
int M[105][105];
int main(){
  int n;

  scanf("%d",&n);
  int cnt = 0;
  int x,y;
  
  for (int j=n-1; j >= 0; --j){
	 y = 0;
	 x = j;
	 while (x < n){
		M[y][x] = ++cnt;
		x++;
		y++;
	 }
  }
  for (int i=1; i < n; ++i){
	 x = 0;
	 y = i;
	 while (y < n){
		M[y][x] = ++cnt;
		y++;
		x++;
	 }
  }
  for (int i=0; i < n; ++i){
	 printf("%d",M[i][0]);
	 for (int j=1; j < n; ++j)
		printf(" %d",M[i][j]);
	 putchar('\n');
  }
  return 0;
}
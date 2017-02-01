#include<cstdio>

int M[105][105];

int main(){
  
  int n;
  scanf("%d",&n);
  for (int i=0; i < n; ++i)
	 for (int j=0; j < n; ++j)
		scanf("%d",&M[i][j]);
  
  int x,y;
  bool s = false;

  for (int i=0; i < n; ++i){
	 y = i;
	 x = 0;
	 while (y >= 0){
		if (s) putchar(' ');
		else s = true;
		printf("%d",M[y][x]);
		y--,x++;
	 }
  }
  for (int j=1; j < n; ++j){
	 y = n-1;
	 x = j;
	 while (x < n){
		printf(" %d",M[y][x]);
		x++;
		y--;
	 }
  }
  return 0;
}
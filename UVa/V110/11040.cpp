#include<cstdio>

int a[12][12];

int main(){
  int runs;
  scanf("%d",&runs);
  while (runs--){
	 for (int i=0; i < 9; i+=2){
		  for (int j=0; j <= i; j+=2)
				scanf("%d",&a[i][j]);
	 }
	 for (int i=1,j=0; i < 9; i+=2,j+=2){
		a[8][i] = (a[6][j] - a[8][i-1] - a[8][i+1])/2;
	 }
	 for (int i=7; i > 0; i--){
		  for (int j=0; j <= i; ++j)
			 a[i][j] = a[i+1][j] + a[i+1][j+1];
	 }
	 for (int i=0; i < 9; ++i){
		for (int j=0; j <= i; ++j){
			 if (j > 0) putchar(' ');
			 printf("%d",a[i][j]);
		}
		putchar('\n');
	 }
  }
  return 0;
}
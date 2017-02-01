#include<cstdio>
#include<cstring>
#include<climits>
const int MAX = 1025; 

int M[MAX][MAX] = {0};
int sum[MAX][MAX] = {0};

inline int sum_val(int x,int y){
  return (x<0 || y<0)? 0:sum[x][y];
}

int main(){

  int d;
  int runs;
  int n;
  int x,y,w;
  int best;
  int bx,by;
  int res;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&d);
	 scanf("%d",&n);
	 for (int i=0; i < n; ++i){
		scanf("%d %d %d",&x,&y,&w);
		M[x][y] = w;
	 }
	 
	 for (int i=0; i <= 1024; ++i){
		for (int j=0; j <= 1024; ++j){
		  sum[i][j] = M[i][j] + sum_val(i-1,j) + sum_val(i,j-1) - sum_val(i-1,j-1);
		}
	 }
	 
	 best = 0;
	 for (int i=0; i <= 1024; ++i){
		for (int j=0; j <= 1024; ++j){
		  x = i + 2*d;
		  y = j + 2*d;
		  if (x > 1024) x = 1024;
		  if (y > 1024) y = 1024;
		  res = sum_val( x , y ) + sum_val( i-1 , j-1 ) - sum_val( x , j - 1 ) - sum_val( i-1 , y );
		  if (res > best){
			 bx = i + d;
			 by = j + d;
			 best = res;
		  }
		}
	 }
	 
	 printf("%d %d %d\n",bx,by,best);
	 if (runs){
		  memset(M,0,sizeof(M));
	 }
  }

  return 0;
}
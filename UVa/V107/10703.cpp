#include<cstdio>
#include<algorithm>
using namespace std;
bool M[505][505];

int main(){
  int N,W,H;
  int x1,x2,y1,y2;

  while (scanf("%d %d %d",&W,&H,&N) && ( N || W || H )){
		for (int i=1; i  <= W; ++i)
		  for (int j=1; j <= H; ++j)
			 M[i][j] = true;

		for (int k=0; k < N; ++k){
		  scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		  if (x1 > x2) swap(x1,x2);
		  if (y1 > y2) swap(y1,y2);
		  for (int i=x1; i <= x2; ++i)
			 for (int j=y1; j <= y2; ++j)
				  M[i][j] = false;
		}
		
		int res = 0;
		for (int i=1; i  <= W; ++i)
		  for (int j=1; j <= H; ++j)
			 if (M[i][j]) res++;

		if (res == 0) puts("There is no empty spots.");
		else if (res == 1) puts("There is one empty spot.");
		else printf("There are %d empty spots.\n",res);

  }

  return 0;
}
#include<cstdio>
#include<climits>
using namespace std;

int TR[21][21];
int RH[21][21];
int HT[21][21];
int T[21];
int H[21];
int R[21];


int main(){
  int t,r,h;
  int best,bh,bt,br;
  int res;

  while (scanf("%d %d %d",&t,&r,&h) != EOF){
		for (int i=0; i < t; ++i){
			 scanf("%d",T + i);
			 for (int j=0; j < r; ++j){
				scanf("%d",&TR[i][j]);
			 }
		}
		for (int i=0; i < r; ++i){
			 scanf("%d",R + i);
			 for (int j=0; j < h; ++j){
				scanf("%d",&RH[i][j]);
			 }
		}
		for (int i=0; i < h; ++i){
			 scanf("%d",H + i);
			 for (int j=0; j < t; ++j){
				scanf("%d",&HT[i][j]);
			 }
		}
		best = INT_MAX;
		for (int i=0; i < t; ++i)
		  for (int j=0; j < r; ++j)
			 for (int k=0; k < h; ++k){
				  if (!TR[i][j] && !RH[j][k] && !HT[k][i]){
						res = T[i] + R[j] + H[k];
						if (best > res){
						  bt = i;
						  br = j;
						  bh = k;
						  best = res;
						}
				  }
			 }
		if (best < INT_MAX){
			 printf("%d %d %d:%d\n",bt,br,bh,best);
		}
		else {
			 printf("Don't get married!\n");
		}
  }

  return 0;
}
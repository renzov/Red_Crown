#include<cstdio>
#include<algorithm>
using namespace std;
int V[505][505] = {0};
int H[505][505] = {0};
int R,C;

long long solve( int r1, int c1,int r2,int c2 ){
  int i,j;
  long long val[ 505 ];
  long long sum[ 505 ];
  int k = 0;
  for ( i=c1; i <= c2; ++i ){
	 val[k] = V[r2][i] - V[r1-1][i];
	 sum[k] = (k? sum[k-1]:0) + val[k];
	 k++;
  }

  long long cost = 0;
  long long best;
  long long res;
 
  for ( i=0; i < k; ++i ){
	 cost += (i*val[i]);
  }
  best = cost;
  for ( i=1; i < k; ++i){
	 cost = cost - sum[k-1] + (sum[i-1]<<1LL);
	 if ( cost < best ) best = cost;
  }
  res = best;
  k = 0;
  for ( i=r1; i <= r2; ++i ){
	 val[k] = H[i][c2] - H[i][c1-1];
	 sum[k] = (k? sum[k-1]:0) + val[k];
	 k++;
  }
  cost = 0;
  for ( i=0; i<k; ++i ){
	 cost += (i*val[i]);
  }
  best = cost;
  for ( i=1; i < k; ++i){
	 cost = cost - sum[k-1] + (sum[i-1]<<1LL);
	 if ( cost < best ) best = cost;
  }
  res += best;
  return res;
}

int main(){
  int runs,k,i,j;
  int x1,x2,y1,y2;
  int v,Q;
  scanf("%d",&runs);
  for ( k=1; k <= runs; ++k ){
	 printf("Test Case %d:\n",k);
	 scanf("%d %d %d",&R,&C,&Q);
	 for ( i=1; i <= R; ++i )
		for ( j=1; j <= C; ++j ){
		  scanf("%d",&v);
		  V[i][j] = V[i-1][j] + v; H[i][j] = H[i][j-1] + v; 
		}
	 for ( i=1; i <= Q; ++i ){
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if ( x1 > x2 ) swap(x1,x2);
		if ( y1 > y2 ) swap(y1,y2);
		printf("%d %lld\n",i,solve(x1,y1,x2,y2));
	 }
	 putchar('\n');
  }
  return 0;
}
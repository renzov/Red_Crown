#include<cstdio>
#include<climits>

int G[505][505];

inline int min(int a,int b){ return a<=b? a:b; }

int main(){
  int n,b,q;
  int runs;
  int i,j,k;
  int u,v;
  int m,coin;

  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&b,&n);
	 for (i=0; i <= n; ++i)
		for (j=0; j <= n; ++j)
		  G[i][j] = INT_MAX;
	 scanf("%d",&q);
	 for (i=0; i < q; i++){
		scanf("%d",&v);
		G[0][v] = 0;
	 }
	 for (u=1; u <= n; ++u){
		scanf("%d",&m);
		for (j=0; j < m; ++j){
		  scanf("%d %d",&coin,&v);
		  if ( coin < G[u][v] ) G[u][v] = coin;
		}
	 }
	 G[0][0] = INT_MAX;
	 /* floyd warshall */
	 for (k=0; k <= n; ++k)
		for (i=0;  i <= n; ++i)
		  for (j=0; j <= n; ++j){
			 if ( G[i][k] < INT_MAX && G[k][j] < INT_MAX)
				G[i][j] = min( G[i][j] , G[i][k] + G[k][j] );
		  }
	 if ( G[0][0] >= INT_MAX ) printf("0\n");
	 else {
		int res = 0;
		int t = b;
		int a;
		while (t > G[0][0]){
		  a = (t / G[0][0]);
		  res += a;
		  t = ( t % G[0][0] ) + a; 
		}
		printf("%d\n",res);
	 }
  }

  return 0;
}
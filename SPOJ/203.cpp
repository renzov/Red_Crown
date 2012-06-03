#include<cstdio>
#include<cstring>
const int MAX = 300;
const int INF = 999999999;
int C[MAX][MAX];
int flow[MAX][MAX];
int q[MAX];
int pred[MAX];
int max_cap[MAX];
int n;

inline int min(int a,int b){
	 return (a < b)? a:b;
}

int max_flow(int s,int t){
  int f = 0;
  int qf,qt;
  int u,v;

  while ( 1 ){
	 qf = 0;
	 qt = 0;
	 /* finding an augmenting path with bfs */
	 q[ qt++ ] = s;
	 for (int i=0; i < n; ++i){ pred[i] = max_cap[i]= -1; }
	 max_cap[s] = INF;
	 while (qt > qf){
		  u = q[ qf++ ];
		  if (u==t) break;
		  for (v=0; v < n; ++v){
				if (max_cap[v] == -1 && (C[u][v] - flow[u][v] > 0)){	/* can push flow */
					 max_cap[v] = min( max_cap[u] , C[u][v] - flow[u][v] );
					 pred[v] = u;
					 q[ qt++ ] = v;
				}
		  }
	 }
	 if ( max_cap[t] == -1 ) break;
	 /* relax edges */
	 f += max_cap[t];
	 v = t;
	 while (v != s){
		  u = pred[v];
		  C[u][v] -= max_cap[t];
		  flow[u][v] += max_cap[t];
		  flow[v][u] -= max_cap[t];
		  v = u;
	 }
  }
  return f;
}

int main(){
  
  int runs;
  int m;
  int res;
  int v;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 /* inicialization of Cap Matrix  */
	 for (int i=0;i < n; ++i)
		for (int j=0; j < n; ++j){
		  C[i][j] = 0;
		  flow[i][j] = 0;
		}
	 for (int u=0; u < n-1; ++u){
		  scanf("%d",&m);
		  for (int j=0; j < m; ++j){
			 scanf("%d",&v);
			 v--;
			 C[u][v] = INF;
		  }
	 }
	 for (int i=0; i < n; ++i){
		if (C[0][i] == INF) C[0][i] = 1;
		if (C[i][n-1] == INF) C[i][n-1] = 1;
	 }
	 res = max_flow(0,n-1);
	 printf("%d\n",res);
  }
  return 0;
}
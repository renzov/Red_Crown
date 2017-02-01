#include<cstdio>
const int INF = 0x7FFFFFFF;
const int MAX = 530;
int st[12][30];
int N;

int C[MAX][MAX];
int flow[MAX][MAX];
int q[MAX];
int pred[MAX];
int max_cap[MAX];

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
	 for (int i=0; i < N; ++i){ pred[i] = max_cap[i]= -1; }
	 max_cap[s] = INF;
	 while (qt > qf && pred[t] == -1){
		  u = q[ qf++ ];
		  for (v=0; v < N; ++v){
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
		  flow[u][v] += max_cap[t];
		  flow[v][u] -= max_cap[t];
		  v = u;
	 }
  }
  return f;
}

int n,m;

inline int source(int i){
  return i*(2*(m+1));
}

inline int sink(int i){
  return i*(2*(m+1)) + 1;
}

inline int add_edge(int u,int v,int c){
  C[u][v] = c;
}

int out(int i,int j){
  return 2*(m+1)*i + 2 + j;
}

int in(int i,int j){
  return 2*(m+1)*i + 2 + m + j; 
}

int main(){

  int runs;
  int cases = 0;
  int k,type;

  scanf("%d",&runs);

  while (runs--){
		cases++;
		scanf("%d %d",&n,&m);

		for (int i=0; i < n; ++i)
			 for (int j=0; j < m; ++j){
				  st[i][j] = 0;
			 }

		for (int i=0; i < n; ++i){
			 scanf("%d",&k);
			 for (int j=0; j < k; ++j){
				  scanf("%d",&type);
				  st[i][type-1]++;
			 }
		}
		/* formamos la red */
		N = 2*(m+1)*n;
		
		for (int i=0; i < N; ++i){
		  for (int j=0; j < N; ++j)
			 flow[i][j] = C[i][j] = 0;
		}
		
		for (int i=0; i < n; ++i){
			 for (int j=0; j < m; ++j){
				  if (st[i][j] > 1){
						add_edge(source(i),out(i,j),st[i][j]-1);
				  }
				  else if (st[i][j] == 0){
						add_edge(in(i,j),sink(i),1);
				  }
			 }
			 if (i != 0){		
				  add_edge(sink(i),source(i),INF);
			 }
		}
		for (int i=0; i < n; ++i)
		  for (int j=0; j < n; ++j)
				if (i!=j){
				  for (k=0; k < m; ++k)
					 add_edge(out(i,k),in(j,k),1);
				}
		int res = 0;
		for (int i=0; i < m; ++i)
			 if (st[0][i]) res++;
		printf("Case #%d: %d\n",cases,res + max_flow(source(0),sink(0)));
  }

  return 0;
}
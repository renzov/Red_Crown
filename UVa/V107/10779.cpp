#include<cstdio>
const int INF = 0x7FFFFFFF;
const int MAX = 530;
int st[12][30];
int N;

inline int min(int a,int b){
	 return (a < b)? a:b;
}

int cap[MAX][MAX];

// flow network
int fnet[MAX][MAX];

// BFS
int q[MAX], qf, qb, prev[MAX];

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    
    int flow = 0;

    while( true )
    {
        // find an augmenting path
        for (int i=0; i < N; ++i) prev[i] = -1;
        qf = qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    prev[q[qb++] = v] = u;

        // see if we're done
        if( prev[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
			 if (bot > (cap[u][v] - fnet[u][v] + fnet[v][u]))
				bot = cap[u][v] - fnet[u][v] + fnet[v][u];

        // update the flow network
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

int n,m;

inline int source(int i){
  return i*(2*(m+1));
}

inline int sink(int i){
  return i*(2*(m+1)) + 1;
}

inline int add_edge(int u,int v,int c){
  cap[u][v] = c;
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
			 fnet[i][j] = cap[i][j] = 0;
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
		printf("Case #%d: %d\n",cases,res + fordFulkerson(N,source(0),sink(0)));
  }

  return 0;
}
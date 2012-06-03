#include<cstdio>
#include<climits>
using namespace std;

struct edge{
  int u,v,w;
  edge(){}
  edge( int U,  int V , int W ){ u = U; v = V; w = W; }
};
int d[505];
int pos[505][505];
int neg[505][505];
int n,k;
edge E[ 21000 ];

int main(){
  int u,v,w;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d %d",&n,&k);
	 for ( int i=1; i<=n; ++i )
		for ( int j=1; j <= n; ++j ){
		  pos[i][j] = -1; neg[i][j] = 1;
		}
	 for ( int i=0; i < k; ++i ){
		scanf("%d %d %d",&u,&v,&w);
		if ( w > 0 ){
		  if ( pos[v][u] < 0 || w < pos[v][u] ){
			 pos[v][u] = w; 
		  }
		}
		else {
		  if ( neg[u][v] > 0 || w < neg[u][v] ){
			 neg[u][v] = w;
		  }
		}
	 }
	 int m = 0;
	 for ( int i=1; i <= n; ++i ){
		E[m].u = 0; E[m].v = i; E[m].w = 0; m++;
	 }
	 for ( int i=1; i <= n; ++i ){
		for ( int j=1; j <= n; ++j ){
		  if ( pos[i][j] > 0 ){ E[m].u = i; E[m].v = j; E[m].w = pos[i][j]; m++; }
		  if ( neg[i][j] < 0 ){ E[m].u = i; E[m].v = j; E[m].w = neg[i][j]; m++; }
		}
	 }
	 for ( int i=1; i <= n; ++i ) d[i] = INT_MAX;
	 d[0] = 0;
	 for ( int i=1; i <= n; ++i ){
		for ( int j=0; j < m; ++j ){
		  u = E[j].u; v = E[j].v; w = E[j].w;
		  if ( d[u] < INT_MAX && ( (d[u]+w) < d[v] ) ){ d[v] = d[u] + w; }
		}
	 }
	 bool ok = true;
	 for ( int j=0; j < m && ok; ++j ){
		 u = E[j].u; v = E[j].v; w = E[j].w;
		 if ( d[u] < INT_MAX && ( (d[u]+w) < d[v] ) ){ ok = false; }
	 }
	 if ( ok ) puts("YES");
	 else puts("NO");
  }
  return 0;
}
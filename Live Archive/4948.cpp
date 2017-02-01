#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n;
bool G[505][505];
int indeg[505];
int d[505];
int f[505];
int ord[505];

void solve(){
  queue<int> q;
  memset( d , -1 , sizeof(int)*n );
  memset( f , 0 , sizeof(int)*n );
  for ( int i=0; i < n; ++i ){
	 if ( !indeg[i] ){ q.push(i); d[i] = 0; }
  }
  int u,v;
  int p=0;
  while ( !q.empty() ){
	 u = q.front(); q.pop();
	 f[ d[u] ]++;
	 ord[p++] = u;
	 for ( v=0; v < n; ++v )
		if ( v!=u && G[u][v] ){
		  indeg[v]--;
		  d[v] = max( d[v] , d[u] + 1 );
		  if ( !indeg[v] ) q.push( v );
		}
  }
  if ( p != n ) puts("IMPOSSIBLE");
  else {
	 for ( int i=0; i < n; ++i ){
		if ( i > 0 ) putchar(' ');
		if ( f[ d[ ord[i] ] ] > 1 ) putchar('?');
		else printf("%d",ord[i]+1);
	 }
	 putchar('\n');
  }
}

int main(){
  int u,v;
  int m;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&n);
	 for ( int i=0;  i<n; ++i ) for ( int j=0; j < n; ++j ) G[i][j] = false;
	 memset( indeg, 0 , sizeof(int)*n );
	 for ( int i=0; i < n; ++i ){
		scanf("%d",&u);
		u--;
		for ( v = 0; v < n ; ++v ){
		  if ( u != v && !G[v][u] ){ G[u][v] = true; indeg[v]++; }
		}
	 }
	 scanf("%d",&m);
	 for (int i=0; i < m; ++i){
		 scanf("%d %d",&u,&v);
		  u--,v--;
		  if ( G[u][v] ){
			 G[u][v] = false; G[v][u] = true;
			 indeg[v]--; indeg[u]++;
		  }
		  else {
			 G[u][v] = true; G[v][u] = false;
			 indeg[v]++; indeg[u]--;
		  }
	 }
	 solve();
  }
  return 0;
}
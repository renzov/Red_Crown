#include<cstdio>
#include<vector>
using namespace std;

vector<int> G[1025];
bool visited[1025];
bool no_use[1025];
int pre[1025];
bool T[1025];
int n;
int s,e;

void dfs( int u , int p, int dest ){
  visited[u] = true;
  int v;
  if ( u == dest ){
	 return;
  }
  for ( int i=0; i < G[u].size(); ++i ){
	 v = G[u][i];
	 if ( v == p || no_use[v] ) continue;
	 if ( !visited[v] ){ pre[v] = u; dfs(v,u,dest); } 
  }
}

int main(){
  int m;

  while ( scanf("%d %d",&s,&e) == 2 ){
	 scanf("%d",&n);
	 for ( int i=0; i < n; ++i ){
		scanf("%d",&m);
		G[i].resize(m);
		for ( int j=0; j < m; ++j ) scanf("%d",&G[i][j]);
	 }
	
	 for ( int i=0; i < n; ++i ) no_use[i] = visited[i] = false;
	 
	 dfs( s , -1 , e );
	 
	 if ( !visited[e] ){
		for ( int i=0; i < n; ++i ) puts("X");
		continue;
	 }
	 
	 int t;
	 
	 T[e] = T[s] = true;
	 for ( int i=0; i < n; ++i ){
		if ( i != s && i != e ){
		  for ( int j=0; j < n; ++j ){ no_use[j] = visited[j] = false; }
		  no_use[s] = true;
		  dfs( i , -1 , e );
		  if ( !visited[e] ){
			 T[i] = false;
		  }
		  else {
			 for ( int j=0; j < n; ++j ){ no_use[j] = visited[j] = false; }
			 t = e;
			 while ( t != i ){
				no_use[t] = true;
				t = pre[t];
			 }
			 dfs( i , -1 , s );
			 if ( !visited[s] ) T[i] = false;
			 else T[i] = true;
		  }
		}
	 }
	 
	 for ( int i=0; i < n; ++i ){
		if ( !T[i] ) puts("X");
		else {
		  bool first = true;
		  for ( int j=0; j < G[i].size(); ++j ){
			 if ( T[ G[i][j] ] ){
				if ( !first ) putchar(' ');
				printf("%d",G[i][j]);
				first = false;
			 }
		  }
		  puts("");
		}
	 }
	 
  }
  return 0;
}

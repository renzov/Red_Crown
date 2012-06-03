#include<cstdio>
#include<vector>
using namespace std;
const char WHITE = 0;
const char BLACK = 1;
const char GRAY = 2;

vector<int> G[2005];
char color[ 2005 ];
bool bipartite;

void dfs(int u,int p,char c){
  if ( color[u] == GRAY ){
	 color[u] = c;
  }
  else {
	 if (color[u] != c) bipartite = false;
	 return;
  }
  int v;
  for (int i=0; i < G[u].size() && bipartite; ++i){
	 v = G[u][i];
	 if (v != p) dfs( v , u , (c==WHITE)? BLACK:WHITE );
  }
}

int main(){

  int runs;
  int m,n;
  int u,v;
  int cases = 0;
  scanf("%d",&runs);
  while (runs--){
	 cases++;
	 scanf("%d %d",&n,&m);
	 for (int i=1; i <= n; ++i){ G[i].clear(); color[i] = GRAY; }
	 for (int i=0; i < m; ++i){
		scanf("%d %d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	 }
	 bipartite = true;
	 for (int i=1; i <= n && bipartite; ++i){
		if (color[i] == GRAY) dfs(i,-1,WHITE);
	 }
	 printf("Scenario #%d:\n",cases);
	 if (bipartite) puts("No suspicious bugs found!");
	 else puts("Suspicious bugs found!");
  }
  
  return 0;
}
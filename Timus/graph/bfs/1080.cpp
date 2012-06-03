#include<cstdio>
#include<list>
const char WHITE = 0;
const char BLACK = 1;
using namespace std;

char color[100];
list<int> G[100];
bool bipartite;

void dfs(int u,char c){
  color[u] = c;
  for (list<int>::iterator v = G[u].begin(); v != G[u].end() && bipartite; v++){
	 if (color[*v] == -1) dfs(*v,(char)(1-c));
	 else if (color[*v] == c) bipartite = false;
  }
}

int main(){
  int n;
  int v;
  scanf("%d",&n);
  for (int u=0; u < n; ++u){
	 color[u] = -1;
	 while (scanf("%d",&v) && v){
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	 }
  }
  bipartite = true;
  dfs(0,WHITE);
  if (bipartite){
	 for (int i=0; i < n; ++i){
		putchar('0' + color[i]);
	 }
	 putchar('\n');
  }
  else puts("-1");
  return 0;
}
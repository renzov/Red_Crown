#include<cstdio>
#include<vector>
using namespace std;
vector<int> G[10005];
bool visited[10005] = {0};
bool cycle = false;
int comp = 0;

void dfs(int x,int p){
  visited[x] = true;
  int v;
  for (int i=0; i < G[x].size() && !cycle; ++i){
		v = G[x][i];
		if (!visited[v]){ 
		  dfs(v,x); 
		}
		else if (v != p && visited[v]){
			 cycle = true;
		}
  }
}

int main(){
  int u,v;
  int n,m;
  scanf("%d %d",&n,&m);
  for (int i=0; i<m; ++i){
		scanf("%d %d",&u,&v);
		u--,v--;
		G[u].push_back(v);
		G[v].push_back(u);
  }
  cycle = false;
  for (int i=0; i < n && comp <= 1 && !cycle; ++i){
		if (!visited[i]){
			comp++;
			if (comp <= 1) dfs(i,-1);
		}
  }
  if (comp == 1 && !cycle) puts("YES");
  else puts("NO");
  return 0;
}
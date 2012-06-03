#include<cstdio>
#include<vector>
using namespace std;

vector<int> G[1000002];
int num[1000002];
int label[1000002];
int ord[1000002];
int n;
int last;
int number;
bool cycle;

void dfs(int u){
  num[u] = number++;
  int v;
  for (int i=0; i < G[u].size() && !cycle; ++i){
	 v = G[u][i];
	 if (num[v] == -1) dfs(v);
	 else if (label[v]==-1) cycle = true;
  }
  label[u] = last;
  ord[last--] = u + 1;
}

int main(){
  int m;
  int u,v;

  while (scanf("%d %d",&n,&m) && n){
	 for (int i=0; i < n; ++i){
		G[i].clear();
		num[i] = -1;
		label[i] = -1;
	 }
	 last = n-1;
	 number = 0;
	 for (int i=0; i<m; ++i){
		scanf("%d %d",&u,&v);
		u--,v--;
		G[u].push_back(v);
	 }
	 cycle = false;
	 for (int i=0; i<n && !cycle; ++i){
		if (num[i] == -1){
		  dfs(i);
		}
	 }
	 if (cycle) printf("IMPOSSIBLE\n");
	 else for (int i=0; i < n; ++i) printf("%d\n",ord[i]);
  }
  return 0;
}

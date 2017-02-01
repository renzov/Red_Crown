#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;
int n;
int longest;
bool cycle;

vector<bool> visited;
vector<char> type;
vector<int> d;
vector<int> total;
vector< vector<int> > G;

void dfs_1(int u){
  visited[u] = true;
  int v;
  for (int i=0; i < G[u].size() && !cycle; ++i){
		v = G[u][i];
		if (type[v] == 'a'){
		  if (visited[v]) cycle = true;
		  else dfs_1(v);
		}
  }
}

void dfs_2(int u){
  int v;
  
  for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if (total[v] < total[u] + d[v]){
			 total[v] = total[u] + d[v];
			 if (type[v] == 'a') dfs_2(v);
		}
  } 
}

int main(){
  int runs;
  int m;
  int u,v;
  int delay;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&delay);
	 scanf("%d",&n);
	 type.clear();
	 d.clear();
	 G.clear();
	 visited.clear();
	 total.clear();
	 type.resize(n);
	 d.resize(n);
	 G.resize(n);
	 visited.resize(n);
	 total.resize(n);
	 for (int i=0; i<n; ++i){
		  visited[i] = false;
		  total[i] = 0; 
		  scanf(" %c %d",&type[i],&d[i]);
		  if (type[i] != 'a') d[i] = 0;
	 }
	 scanf("%d",&m);
	 for (int i=0; i<m; ++i){
		  scanf("%d %d",&u,&v);
		  G[u].push_back(v);
	 }
	 cycle = false;
	 for (int i=0; i < n && !cycle; ++i){
		  if (type[i] == 'a' && !visited[i]){
				dfs_1(i);
		  }
	 }
	 if (cycle) puts("Circuit contains cycle.");
	 else {
		  for (int i=0; i < n; ++i) visited[i] = false;
		  for (int i=0; i < n; ++i){
				if (type[i]!='a'){
					 dfs_2(i);
				}
		  }
		  longest = *max_element(total.begin(),total.end());
		  if (longest > delay) puts("Clock period exceeded.");
		  else printf("Synchronous design. Maximum delay: %d.\n",longest);
	 }
  }
  return 0;
}
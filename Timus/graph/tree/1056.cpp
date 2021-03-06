#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> G[10002];
int d[10002];
int pred[10002];
int last;
int diameter;
int n;

void dfs(int u,int parent){
  int v;
  if (diameter < d[u]) diameter=d[u],last=u;
  for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if (v != parent){
		  d[v] = 1 + d[u];
		  pred[v] = u;
		  dfs(v,u);
		}
  }
}

int main(){

  int u,v;
  scanf("%d",&n);
  for (v=2; v <= n; ++v){
	 scanf("%d",&u);
	 G[u].push_back(v);
	 G[v].push_back(u);
  }

  if (n <= 2){
	 for (int i=1; i <= n; ++i){
		if (i > 1) putchar(' ');
		printf("%d",i);
	 }
	 putchar('\n');
	 return 0;
  }

  diameter = 0;
  d[1] = 0;
  pred[1] = -1;
  dfs(1,-1);
  diameter = 0;
  d[last] = 0;
  pred[last] = -1;
  dfs(last,-1);
 
  int m = (diameter + 1)/2;
  int dist;
  vector<int> res;
  u = last;
  while ( u != -1 ){
	 dist = max( d[u] , diameter - d[u] );
	 if (dist == m) res.push_back(u);
	 u = pred[u];
  }
  if (res.size() < 2){
	 printf("%d\n",res[0]);
  }
  else {
	 printf("%d %d\n",min(res[0],res[1]),max(res[0],res[1]));
  }
  return 0;
}
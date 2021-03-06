#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

vector<int> G[ 205 ];
char name[ 205 ][ 35 ];
int p[ 205 ][ 4 ];
bool visited[ 205 ];
int n;

bool win(int a,int b){
  int r = 0;
  if (p[a][0] > p[b][0]) r++;
  if (p[a][1] > p[b][1]) r++;
  if (p[a][2] > p[b][2]) r++;
  return r > 1;
}

bool bfs(int s){
  queue<int> q;
  for (int i=0; i < n; ++i) visited[i] = false;
  q.push(s);
  visited[s] = true;
  int u,v;
  int left = n-1;

  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if (!visited[v]){
			 visited[v] = true;
			 q.push(v);
			 left--;
		}
	 }
  }

  return (left == 0);
}

int main(){
	
  scanf("%d",&n);
  for (int i=0; i < n; ++i){
	 scanf("%s %d %d %d",name[i],&p[i][0],&p[i][1],&p[i][2]);
  }
  for (int i=0; i < n-1; ++i){
	 for (int j=i+1; j < n; ++j){
		if ( win(i,j) ) G[i].push_back(j);
		else if ( win(j,i) ) G[j].push_back(i);
	 }
  }
  for (int i=0; i < n; ++i)
	 if (bfs(i)) printf("%s\n",name[i]);
  return 0;
}
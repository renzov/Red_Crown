#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;

vector<int> G[3005];
int color[3005];
bool cycle = false;
bool in;
int center = 0;
vector<int> nodes;
int d[3005];

void dfs(int u,int p){
  int v;
  color[u] = 1;
  for (int i=0; i < G[u].size() && !cycle; ++i){
	 v = G[u][i];
	 if ( v != p ){
		if ( color[v] == 1 ){
		  //cycle found
		  cycle = true;
		  in = true;
		  center = v;
		}
		else if (color[v] == 0 ){
		  dfs(v,u);
		}
	 }
  }
  if ( in ){
	 nodes.push_back(u);
	 if ( center == u ) in = false;
  }
  color[u] = 2;
}

int main(){
  int n;
  cin >> n;
  int u,v;
  for (int i=0; i < n; ++i){
	 color[i] = 0;
	 cin >> u >> v;
	 u--,v--;
	 G[u].push_back( v );
	 G[v].push_back( u );
  }
  for (int i=0; i < n && !cycle; ++i){
	 if ( color[i] == 0 ) dfs(i,-1);
  }
  queue<int> q;
  memset(d,-1,sizeof(int)*n);
  for (int i=0; i < nodes.size(); ++i){
	 d[nodes[i]] = 0;
	 q.push( nodes[i] );
  }
  while( !q.empty() ){
	 u = q.front();
	 q.pop();
	 for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		if ( d[v] == -1 ){ q.push( v ); d[v] = d[u]+1;}
	 }
  }
  cout << d[0];
  for (int i=1;i < n; ++i){
	 cout << " " << d[i];
  }
  cout << endl;
  return 0;
}
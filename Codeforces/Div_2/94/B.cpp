#include<iostream>
#include<vector>
using namespace std;
int main(){

  int n,m;
  bool G[105][105] = {0};
  int deg[105] = {0};
  int u,v;
  cin >> n >> m;

  for (int i=0; i < m; ++i){
	 cin >> u >> v;
	 u--,v--;
	 if ( !G[u][v] ){ G[u][v]=G[v][u] = true;
		deg[u]++,deg[v]++;
	 }
  }
  vector<int> a;
  int res = 0;
  for (int i=0; i < n; ++i) if ( deg[i] == 1 ) a.push_back(i);
  while ( !a.empty() ){
	 res++;
	 for ( int i=0; i < a.size(); ++i ){
		u = a[i];
		deg[u]--;
		for (v=0; v < n; ++v){
		  if( G[u][v] ){
			 G[u][v] = G[v][u] = false;
			 deg[v]--;
		  }
		}
	 }
	 a.clear();
	 for (int i=0; i < n; ++i) if ( deg[i] == 1 ) a.push_back(i);
  }
  cout << res << endl;
  return 0;
}
#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
const int MAX = 100002;
int deg[MAX];
vector<int> G[MAX];
bool cycle;
bool visited[MAX];

void dfs(int u,int p){
  int i;
  int v;
  visited[u] = true;
  for (i=0; i < G[u].size(); ++i){
	 v = G[u][i];
	 if ( !visited[v] ) dfs(v,u);
	 else if ( p != v ) cycle = true;
  }
}

int main(){
  int n,k;
  int m;
  int u,v;
  int i;
  int nc;
  bool ok;
  int ng;
  while ( scanf("%d %d",&n,&k) && n ){
	 map<int,int> H;
	 set< pair<int,int> > edge;
	 m = 0;
	 while ( k-- ){
		scanf("%d %d",&u,&v);
		if ( u > v ) swap(u,v);
		if ( edge.find( make_pair(u,v) ) != edge.end() ) continue;
		edge.insert( make_pair(u,v) );
		if ( H.find( u ) == H.end() ){ visited[m]=false; deg[m]=0; G[m].clear(); H[u] = m++; }
		if ( H.find( v ) == H.end() ){ visited[m]=false; deg[m]=0; G[m].clear(); H[v] = m++; }
		u = H[u];
		v = H[v];
		G[u].push_back( v );
		G[v].push_back( u );
		deg[u]++,deg[v]++;
	 }
	 ok = true;
	 ng = 0;
	 /* Check degree constraint */
	 for (i=0; i<m && ok; ++i){
		ok = (deg[i] <= 2);
		if ( deg[i] < 2 ) ng++;
	 }
	 if ( !ok ){ puts("N"); continue; }
	 nc = 0;
	 for ( i = 0; i < m && nc < 2; ++i ){
		if ( !visited[i] ){
		  cycle = false;
		  dfs( i , -1 );
		  if ( cycle ) nc++;
		}
	 }
	 if ( nc > 1 ) puts("N");
	 else if ( nc == 1 ){
		if ( m == n && ng == 0) puts("Y");
		else puts("N");
	 }
	 else {
		puts("Y");
	 }
  }
  return 0;
}
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int n;
int indegree[1005] = { 0 };
vector<int> G[1005];
int ord[1005];
int pr[1005];

bool topsort(){
  int left = n;
  int p = 1;
  int u,v;
  priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > q;
  
  for (int i=1; i <= n; ++i){
	 if (indegree[i] == 0) q.push( make_pair( pr[i] , i ) );
  }
  while (!q.empty()){
	 u = q.top().second;
	 q.pop();
	 if ( u != ord[p] ) return false;
	 left--;
	 p++;
	 for( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		indegree[v]--;
		if (indegree[v] == 0) q.push( make_pair( pr[v] , v ) );
	 }
  }
  return (left == 0);
}

int main(){

  int m;
  int u,v;

  scanf("%d %d",&n,&m);
  for (int i=0; i < m; ++i){
	 scanf("%d %d",&u,&v);
	 G[u].push_back(v);
	 indegree[ v ]++;
  }
  for (int i=1; i <= n; ++i){
	 scanf("%d",ord + i);
	 pr[ ord[i] ] = i; 
  }
  if (topsort()) printf("YES\n");
  else printf("NO\n");
  return 0;
}
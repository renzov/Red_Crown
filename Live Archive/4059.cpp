#include<cstdio>
#include<vector>
using namespace std;
int n,m,t;
int d[1005];
vector<int> G[1005];
bool vis[1005];
bool pres[1005];
int odd;

void dfs(int u){
  vis[u] = true;
  int v;
  if ( d[u] & 1 ) odd++;
  for ( int i=0; i < G[u].size(); ++i ){
	 v = G[u][i];
	 if ( !vis[v] ) dfs(v);
  }
}

int main(){
  int u,v;
  int cnt;
  int nc;
  int cases = 0;
  while ( scanf("%d %d %d",&n,&m,&t) && n ){
	 cases++;
	 for ( int i=0; i < n; ++i ){ G[i].clear(); d[i] = 0; pres[i] = vis[i] = false; }
	 for ( int i=0; i < m; ++i ){
		scanf("%d %d",&u,&v); u--,v--;
		d[u]++,d[v]++;
		G[u].push_back(v); G[v].push_back(u);
		pres[u] = pres[v] = true;
	 }
	 nc = 0;
	 cnt = m;
	 for ( int i=0; i < n; ++i ){
		if ( !vis[i] && pres[i] ){
		  odd = 0;
		  dfs( i );
		  if ( odd > 2 ){
			 cnt += ( odd - 2 )/2;
		  }
		  nc++;
		}
	 }
	 if ( nc > 1 ) cnt += ( nc - 1 );
	 printf("Case %d: %d\n",cases,cnt*t);
  }
  return 0;
}
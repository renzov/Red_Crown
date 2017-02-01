#include<cstdio>
#include<bitset>
#include<vector>
#include<vector>
using namespace std;
bitset<102> reach[102][102];
bool visited[102][102];
bool can[102][102];
int T[102];
int n,t;
vector< int > G[102];
vector< int > C[102];

void init(){
  for (int i=0; i < n; ++i){
	 G[i].clear();
	 C[i].clear();
	 for ( int j=0; j <= t; ++j ){
		visited[i][j] = false;
		can[i][j] = false;
		reach[i][j].reset();
	 }
  }
}

void dfs( int u, int s ){
  visited[u][s] = true;
  int v;
  bitset< 102 > b;
  b.reset();

  if ( s == t ){
	 if ( u == (n-1) ){ reach[u][s].set(u); can[u][t] = true; }
	 return;
  }

  for ( int i=0; i < G[u].size(); ++i ){
	 v = G[u][i];
	 if ( T[s] == C[u][i] ){
		if ( !visited[v][s+1] ) dfs( v , s + 1 );
		if ( can[v][s+1] ) b |= reach[v][s+1];
		can[u][s] |= can[v][s+1]; 
	 }
  }
  if ( can[u][s] ) b.set(u);
  else b.reset();
  reach[u][s] = b;
}

int main(){
  int m;
  int u,v,w;
  int cases = 0;
  while ( scanf("%d %d",&n,&m) && n ){
	 init();
	 cases++;
	 for ( int i=0; i < m; ++i ){
		scanf("%d %d %d",&u,&v,&w);
		G[u].push_back(v); G[v].push_back(u);
		C[u].push_back(w); C[v].push_back(w);
	 }
	 scanf("%d",&t);
	 for ( int i=0; i < t; ++i ){
		scanf("%d",T+i);
	 }
	 dfs( 0 , 0 );
	 //if ( reach[0][0].count() == 1 ) printf("Tour %d: %d\n",cases,0);
	 printf("Tour %d: %d\n",cases,(int)reach[0][0].count());
  }

  return 0;
}
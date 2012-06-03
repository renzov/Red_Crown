#include<cstdio>
#include<vector>
using namespace std;
#define forn(i,n) for ( int i=0; i < (int)(n); ++i )
const int MAXN = 105;
int color[MAXN];
int LA[MAXN];
int RA[MAXN];
int n;
vector<int> G[MAXN];
bool SL[MAXN];
bool SR[MAXN];
bool vis[MAXN];

bool alternate( int u , int p ){
  int v;
  forn( i , G[u].size() ){
	 v = G[u][i];
	 if ( v==p || vis[v] ) continue;
	 if ( color[v] != color[u] && !vis[v]  ){
		if ( RA[v] < 0 || alternate( RA[v] , v ) ){
		  RA[v] = u; LA[u] = v;
		  return true;
		}
	 }
  }
  return false;
}

void dfs1( int u , int p , int c){
  color[u] = c;
  vis[u] = true;
  int v;
  forn( i , G[u].size() ){
	 v = G[u][i];
	 if ( v != p && !vis[v] ){
		dfs1( v, u , 1 - c );
	 }
  }
}

void dfs2( int u  ){
  if ( vis[u] ) return;
  vis[u] = true;
  SL[ u ] = true;
  int v;
  forn( i , G[u].size() ){
	 v = G[u][i];
	 if ( color[v] != color[u] && LA[u] != v ){
		SR[v] = true;
		if ( RA[v] >= 0 ) dfs2( RA[v] );
	 }
  }
}

int main(){
  int u,v;
    freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d",&n);
  forn(i,n-1){
	 scanf("%d %d",&u,&v); u--,v--;
	 G[u].push_back(v);
	 G[v].push_back(u);
  }
  fill( vis, vis + n, false );
  dfs1(0,-1,1);
  fill(LA,LA+n,-1);
  fill(RA,RA+n,-1);
  forn(i,n){
	 if ( color[i] == 1 ){ fill( vis, vis + n, false ); alternate( i , -1 ); }
  }
  fill(vis,vis+n,false);
  forn(i,n){
	 if ( color[i] == 1 && LA[i] < 0 )
		dfs2( i );
  }
  bool res[ MAXN ] = {0};
  forn(i,n){
	 if ( color[i] == 1 ){
		if ( !SL[i] ) res[i] = true;
	 }
	 else {
		if ( SR[i] ) res[i] = true;
	 }
  }
  forn(i,n){
	 if (i) putchar(' ');
	 if ( res[i] ) printf("1");
	 else printf("0");
  }
  puts("");
  return 0;
}
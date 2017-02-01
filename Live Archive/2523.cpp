#include<cstdio>
#include<vector>
#include<algorithm>
#define forn(i,n) for(int i=0; i < (int)(n); ++i)
using namespace std;
const int MAXN = 1000;
bool G[MAXN][MAXN];
bool vis[MAXN];
int LA[MAXN];
int RA[MAXN];
int n,m,k;

bool alternate(int u){
  forn(v,m){
	 if ( G[u][v] && !vis[v]){
		vis[v] = true;
		if ( RA[v] < 0 || alternate( RA[v] ) ){
		  LA[u] = v; RA[v] = u; return true; 
		}
	 }
  }
  return false;
}

int main(){
  int x,y,z;
  int res;
  while ( scanf("%d",&n) && n ){
	 scanf("%d %d",&m,&k);
	 forn(i,n){ LA[i] = -1; }
	 forn(i,m){ RA[i] = -1; }
	 forn(i,n) forn(j,m) G[i][j] = false;
	 forn(i,k){
		scanf("%d %d %d",&z,&x,&y);
		if ( x > 0 && x < n && y > 0 && y < m )
		  G[x][y] = true;
	 }
	 res = 0;
	 forn(i,n){
		fill(vis,vis+m,false);
		if ( alternate(i) ) res++;
	 }
	 printf("%d\n",res);
  }
  return 0;
}
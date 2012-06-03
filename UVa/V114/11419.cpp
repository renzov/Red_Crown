#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

#define forn(i,n) for(int i=0; i < (int)(n); ++i)
const int MAXN = 1010;
vector<int> G[MAXN];
bool vis[MAXN];
int LA[MAXN];
int RA[MAXN];
int R;

bool SL[MAXN];
bool SR[MAXN];
bool in[MAXN];

void dfs(int u){
  if ( in[u] ) return;
  in[u] = true;
  int v;
  SL[u] = true;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( !SR[v] ){
		 SR[v] = true;
		 if ( RA[v] >= 0 ) dfs(RA[v]);
	 }
  }
}

bool Alternate( int u ){
  int v;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( vis[v] ) continue;
	 vis[v] = true;
	 if( RA[v] < 0 || Alternate(RA[v]) ){
		LA[u] = v; RA[v] = u;
		return true;
	 }
  }
  return false;
}

int main(){
  int C,N;
  int r,c;
  int res;
  while ( scanf("%d %d %d",&R,&C,&N) && N ){
	 forn(i,R){ G[i].clear(); LA[i] = -1; SL[i] = false; in[i] = false; }
	 forn(i,C){ RA[i] = -1; SR[i] = false; }
	 forn(i,N){
		scanf("%d %d",&r,&c);
		r--,c--; G[r].push_back(c);
	 }
	 res = 0;
	 forn(i,R){
		fill(vis,vis+C,false);
		if ( Alternate(i) ) res++;
	 }
	 forn(i,R){
		if ( LA[i] < 0 ){
		  dfs(i);
		}
	 }
	 printf("%d",res);
	 forn(i,R){
		if ( !SL[i] ){ printf(" r%d",i+1); }
	 }
	 forn(i,C){
		if ( SR[i] ){ printf(" c%d",i+1); }
	 }
	 putchar('\n');
  }
  return 0;
}
#include<cstdio>
#include<vector>
#include<algorithm>
#define forn(i,n) for(int i=0; i < (int)(n); ++i)
using namespace std;
const int MAXN = 150;
int n;
bool vis[MAXN];
int LA[MAXN];
int RA[MAXN];
vector<int> G[MAXN];

bool Alternate_Path( int u ){
  int v;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( vis[v] ) continue;
	 vis[v] = true;
	 if ( RA[v] < 0 || Alternate_Path( RA[v] ) ){
		LA[u] = v; RA[v] = u;
		return true;
	 }
  }
  return false;
}

int main(){
  int m;
  int u,v;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&n);
	 scanf("%d",&m);
	 forn(i,n){ G[i].clear(); LA[i]=-1; RA[i]=-1; }
	 forn(i,m){
		scanf("%d %d",&u,&v);
		u--,v--;
		G[u].push_back(v);
	 }
	 int p = 0;
	 forn(i,n){
		fill(vis,vis+n,false);
		if ( Alternate_Path(i) ) p++;
	 }
	 printf("%d\n",n-p);
  }
  return 0;
}
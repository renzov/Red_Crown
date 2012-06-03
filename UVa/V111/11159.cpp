#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 102;
#define forn(i,n) for( int i=0; i < (int)(n); ++i )
vector<int> G[MAXN];
int a[MAXN];
int b[MAXN];
int RA[MAXN];
int LA[MAXN];
bool vis[MAXN];
int n,m;

bool alternate( int u ){
  int v;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( vis[v] ) continue;
	 vis[v] = true;
	 if ( RA[v] < 0 || alternate(RA[v]) ){
		LA[u] = v; RA[v] = u;
		return true;
	 }
  }
  return false;
}

int main(){
  int runs;
  scanf("%d",&runs);
  forn(k,runs){
	 scanf("%d",&n);
	 forn(i,n){ scanf("%d",a+i); a[i] = abs(a[i]); LA[i] = -1; G[i].clear(); }
	 scanf("%d",&m);
	 forn(i,m){ scanf("%d",b+i); b[i] = abs(b[i]); RA[i] = -1; }
	 forn(i,n){
		forn(j,m){
		  if ( a[i] ){
			 if ( b[j]%a[i] == 0 ) G[i].push_back(j);
 		  }
		  else if ( b[j] == 0 ) {
			  G[i].push_back(j);
		  }
		}
	 }
	 int res = 0;
	 forn(i,n){
		fill(vis,vis+m,false);
		if ( alternate(i) ) res++;
	 }
	 printf("Case %d: %d\n",k+1,res);
  }
  return 0;
}
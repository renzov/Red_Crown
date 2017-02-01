#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for( int i=0; i < (int)(n); ++i )
#define forab(i,a,b) for( int i=(int)(a); i < (int)(b) ; ++i )
const int MAXN = 501;
vector<int> G[MAXN];
bool vis[MAXN];
int LA[MAXN];
int RA[MAXN];
int n;

int d[MAXN];
int s[MAXN][2];
int e[MAXN][2];

int D( int i,int j ){
  return abs( s[i][0] - e[i][0] ) + abs( s[i][1] - e[i][1] )
			+ abs( s[j][0] - e[i][0] ) + abs( s[j][1] - e[i][1] );
}

bool Altertate_Path(int u){
  int v;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( vis[v] ) continue;
	 vis[v] = true;
	 if ( RA[v] < 0 || Altertate_Path(RA[v]) ){
		LA[u] = v; RA[v] = u; 
		return true;
	 }
  }
  return false;
}

int main(){
  int h,m;
  int runs;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&n);
	 forn(i,n){
		G[i].clear(); RA[i] = LA[i] = -1;
		scanf("%d:%d",&h,&m);
		d[i] = h*60 + m;
		scanf("%d %d %d %d",&s[i][0],&s[i][1],&e[i][0],&e[i][1]);
	 }
	 forn(i,n){
		forab(j,i+1,n){
		  if ( (d[i] + D( i , j )) < d[j]  ) 
			 G[i].push_back(j);
		}
	 }
	 int p = 0;
	 forn(i,n){
		fill(vis,vis+n,false);
		if ( Altertate_Path(i) ) p++;
	 }
	 printf("%d\n",n-p);
  }
  return 0;
}
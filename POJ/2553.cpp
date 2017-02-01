#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for( int i=0; i < (int)(n); ++i )
const int MAXN = 5002;
vector<int> G[MAXN];
bool in[MAXN];
int comp[MAXN];
int low[MAXN];
int number[MAXN];
int n;
int nc;
int num;
bool out[MAXN];
int S[MAXN];
int st;

void scc_tarjan( int u ){
  number[u] = low[u] = num++;
  S[st++] = u;
  in[u] = true;
  int v;
  forn(i,G[u].size()){
	 v = G[u][i];
	 if ( number[v] == -1 ){
		scc_tarjan(v);
		low[u] = min(low[u],low[v]);
	 }
	 else if (number[v] < number[u] && in[v]) {
		low[u] = min(low[u],number[v]);
	 }
  }
  // Inicio de componente fuertemente conexa
  if ( low[u] == number[u] ){
	 out[nc] = false;
	 while ( st > 0 && number[ S[ st-1 ] ] >= number[u] ){
			v = S[ st - 1 ]; st--;
			in[v] = false;
		   comp[v] = nc;
	 }
	 nc++;
  }
}

int main(){
  int m,u,v;
  while ( scanf("%d",&n) && n){
	 forn(i,n){ G[i].clear(); in[i] = false; number[i] = -1; }
	 scanf("%d",&m);
	 while (m--){
		scanf("%d %d",&u,&v);
		u--,v--;
		G[u].push_back(v);
	 }
	 st = nc = num = 0;
	 forn(i,n){
		if ( number[i] == -1 ){ 
		  scc_tarjan(i); 
		}
	 }
	 forn(i,n){
		forn(j,G[i].size()){
		  v = G[i][j];
		  if ( comp[v] != comp[i] ) out[ comp[i] ] = true;
		}
	 }
	 bool first = true;
	 forn(i,n){
		if ( !out[ comp[i] ] ){
		  if ( first ) first = false;
		  else putchar(' ');
		  printf("%d",i+1);
		}
	 }
	 puts("");
  }
  return 0;
}
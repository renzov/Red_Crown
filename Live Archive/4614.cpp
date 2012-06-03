#include<vector>
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MAXN = 50002;
int n;
vector<int> G[MAXN];
vector<int> C[MAXN];
long long f[MAXN];
long long W[MAXN];
long long T[MAXN];
long long S[MAXN];
long long best;
long long F;
int ns;
int sol[MAXN];
bool first;

void calc(int u,int parent){
  int v;
  T[u] = W[u] = 0;
  for ( int i=0; i < G[u].size(); ++i ){
	 v = G[u][i];
	 if ( v==parent ) continue;
	 calc(v,u);
	 T[u] += T[v];
	 W[u] += (W[v] + T[v]*C[u][i]);
  }
  T[u] += f[u];
  F += f[u];
}

void dfs( int u , int parent , int cost ){
  if ( parent != -1 ){
	 S[u] = S[parent] + (F - 2*T[u])*cost; 
  }
  else {
	 S[u] = W[u];
  }
  if ( first || best > S[u] ){ best = S[u]; ns = 0; sol[ns++] = u; first = false; }
  else if ( best == S[u] ) sol[ns++] = u;
  for ( int i=0; i < G[u].size(); ++i )
	 if ( G[u][i] != parent )
		dfs( G[u][i] , u , C[u][i] );
}

int main(){
  int u,v,w;
  int runs;
  int m;
  int root;
  scanf("%d",&runs);
  while ( runs-- ){
	 scanf("%d",&n);
	 for ( int i=0; i < n; ++i ){ G[i].clear(); C[i].clear(); f[i] = 0; }
	 for ( int i=0; i < n-1; ++i ){
		scanf("%d %d %d",&u,&v,&w);
		u--,v--;
		G[u].push_back(v); G[v].push_back(u);
		C[u].push_back(w); C[v].push_back(w);
	 }
	 scanf("%d",&m);
	 for ( int i=0; i < m; ++i ){
		 scanf("%d %d",&u,&w); 
		 u--;
		 f[u] = w;
	 }
	 F = 0;
	 calc(0,-1);
	 first = true;
	 ns = 0;
	 dfs(0,-1,0);
	 sort( sol , sol + ns );
	 printf("%lld\n",2LL*best);
	 for ( int i=0; i < ns; ++i ){
		if ( i > 0 ) putchar(' ');
		printf("%d",sol[i]+1);
	 }
	 putchar('\n');
  }
  return 0;
}
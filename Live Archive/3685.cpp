#include<cstdio>
#include<vector>
using namespace std;
const int INF = 10002;
vector<int> G[10002];
int dp[10002][2][2];
int n;

int solve(int u,int p,bool server,bool pserver){
  //puts("X");
  if ( G[u].size() == 1 && p != -1 ){
	 //puts("T");
	 if ( !server && !pserver ) return INF;
	 return server;
  }
  if ( dp[u][server][pserver] != -1 ){ return dp[u][server][pserver]; }
  int v,i;
  int best = INF;
  int tmp,sum,r1,r2;
  int m = G[u].size();
  if ( !server && !pserver ){
	 int L[m+1];
	 int R[m+1];
	 for (i=0; i < m; ++i){
		v = G[u][i];
		L[i] = (i > 0)? L[i-1]:0;
		if ( v == p ) continue;
		L[i] += solve( v , u , false, false );
		if ( L[i] > INF ) L[i] = INF;
	 }
	 for (i=m-1; i >= 0; --i){
		v = G[u][i];
		R[i] = (i < (m-1))? R[i+1]:0;
		if ( v == p ) continue;
		R[i] += solve( v  , u , false, false );
		if ( R[i] > INF ) R[i] = INF;
	 }
	 for (i=0; i < m; ++i){
		v = G[u][i];
		if ( v == p ) continue;
		tmp = solve( v , u , true, false );
		if ( i > 0 ) tmp += L[i-1];
		if ( i < (m-1) ) tmp += R[i+1];
		if ( tmp < best ) best = tmp;
	 }
	 dp[u][server][pserver] = best;
  }
  else if ( !server && pserver ){
	 sum = 0;
	 for (i=0; i < m; ++i){
		v = G[u][i];
		if (v==p) continue;
		r1 = solve(v,u,false,false);
		sum += r1;
		if (sum > INF) sum = INF;
	 }
	 dp[u][server][pserver] = sum;
  }
  else {
	 sum = 0;
	 for (i=0; i < m; ++i){
		v = G[u][i];
		if (v==p) continue;
		r1 = solve(v,u,true,true);
		r2 = solve(v,u,false,true);
		sum += ( r1 < r2 )? r1:r2;
		if (sum > INF) sum = INF;
	 }
	 dp[u][server][pserver] = 1  + sum;
  }
  if (dp[u][server][pserver] > INF) dp[u][server][pserver] = INF;
  //printf("dp[%d][%d][%d] = %d\n",u,server,pserver,dp[u][server][pserver]);
  return dp[u][server][pserver];
}

int main(){
  int i;
  int u,v;
  int zero = 0;
  scanf("%d",&n);
  while ( zero > -1 ){
	 for (i=0; i < n-1; ++i){
		dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = -1;
		scanf("%d %d",&u,&v);
		u--,v--;
		G[u].push_back(v);
		G[v].push_back(u);
	 }
	 dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = -1;
	 if (n == 1){
		printf("1\n");
	 }
	 else {
		solve(0,-1,false,false);
		solve(0,-1,true,false);
		if ( dp[0][0][0] < dp[0][1][0] ) printf("%d\n",dp[0][0][0]);
		else printf("%d\n",dp[0][1][0]);
	 }
	 scanf("%d",&zero);
	 if (zero > -1){ 
		scanf("%d",&n);
		for (i=0; i < n; ++i) G[i].clear();
	 }
  }
  return 0;
}
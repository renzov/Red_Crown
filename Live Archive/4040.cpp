#include<cstdio>
#include<map>
#include<climits>

using namespace std;
int G[105][5];
long long dp[105][25];
bool final[105];

int main(){
  int m;
  int runs;
  int n,l;
  int i,j,k;
  int u,v;
  long long res;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 map<int,int> hash;
	 hash[1] = 0;
	 m = 1;
	 for (i=0; i < n; ++i){
		scanf("%d",&u);
		if ( hash.find(u) == hash.end() ){ hash[u] = m++; }
		u = hash[u];
		for (j=0; j<3;++j){
		  scanf("%d",&v);
		  if ( hash.find(v) == hash.end() ){ hash[v] = m++; }
		  v = hash[v];
		  G[u][j] = v;
		}
		scanf("%d",&v);
		if (v) final[u] =  true;
		else final[u] = false;
	 }
	 scanf("%d",&l);
	 for (i=0; i < n; ++i)
		for (j=0; j <= l ; ++j){
		  dp[i][j] = 0;
		}
	 dp[0][0] = 1;
	 for (j=0; j < l; ++j){
		for (i=0; i<n; ++i){
		  for (k=0; k < 3; ++k){
			 v = G[i][k];
			 dp[v][j+1] += dp[i][j];
		  }
		}
	 }
	 res = 0;
	 for (i=0; i < n; ++i)
		if ( final[i] )
		  res += dp[i][l];
	 printf("%lld\n",res);
  }
  return 0;
}
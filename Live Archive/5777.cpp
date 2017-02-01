#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 100005;
int W[MAXN];
vector<int> T[MAXN];
int N,K;

void dfs(int u,int *best){
  int best_son[ K + 1 ];
  for (int i=0; i <= K; ++i) best_son[i] = best[i];
  for (int i=0; i < T[u].size(); ++i){
	 dfs( T[u][i] , best_son );
  }
  best[0] = 0;
  for (int i=K; i >= 1; --i){
	 best[i] = best_son[i];
	 if ( best[i - 1] >= 0 ){
		best[i] = max( best[i] , best[i-1] + W[u] );
	 }
  }
}

int main(){
	 int u;
	 int root;
	 while ( scanf("%d %d",&N,&K) && N && K ){
		for (int i=0; i < N; ++i){
		  T[i].clear();
		}
		for (int i=0; i<N; ++i){
		  scanf("%d %d",&u,W+i);
		  if ( u ) T[u-1].push_back( i );
		  else root = i;
		}
		int best[ K + 1 ];
		fill(best,best + K + 1, INT_MIN );
		dfs( root , best );
		if ( best[K] < 0 ) puts("0");
		else printf("%d\n",best[K]);
	 }
	 return 0;
}

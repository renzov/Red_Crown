#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int N, F;
vector<int> T[MAXN];
vector<int> W[MAXN];
int cost1[MAXN];
int cost2[MAXN];
int cnt[MAXN];
bool inF[MAXN];

void clean(){
	for ( int i=0; i < N; ++i ){
		inF[i] = false;
		T[i].clear();
		W[i].clear();
	}
}

void dfs( const int &u ){
	int v, w;
	int mx = 0;
	
	cnt[u] = inF[u]? 1:0;
	cost2[u] = cost1[u] = 0;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i], w = W[u][i];
		dfs(v);
		if ( cnt[v] > 0 ){
			cnt[u] += cnt[v];
			cost2[u] += (cost2[v] + w);
			mx = max( mx, cost2[v] + w - cost1[v] );
		}
	}
	cost1[u] = cost2[u] - mx; 
}

void process(){
	int u, v, w;

	for ( int i=1; i < N; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		T[u].push_back(v), W[u].push_back(w);
	}
	for ( int i=0; i < F; ++i ){
		scanf("%d", &u);
		u--;
		inF[u] = true;
	}
	dfs( 0 );
	printf("%d\n", cost1[0]);
}

int main(){
	while ( scanf("%d %d", &N, &F) == 2 ){
		process();
		clean();
	}
	return 0;
}

#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 1000005;
vector<int> T[MAXN];
int size[MAXN];
long long ans[MAXN];
int sons[MAXN];
int N;
void dfs( const int &u, const int &p ){
	int v;
	// Compute the size of the subtree
	size[u] = 1;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		dfs( v, u );
		size[u] += size[v];
	}
	
	//compute the answers
	int M = 0;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		sons[M++] = size[v];
	}
	if ( p != -1 ){
		sons[M++] = N - size[u];
	}
	for ( int i=0; i < M; ++i ){
		ans[u] += 1LL*sons[i]*( N - 1 - sons[i] );
		ans[u] += 2*sons[i];
	}
}


int main(){
	int u, v;

	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v), T[v].push_back(u);
	}
	dfs(0, -1);
	for ( int i=0; i < N; ++i )
		printf("%lld\n", ans[i]);
	return 0;
}

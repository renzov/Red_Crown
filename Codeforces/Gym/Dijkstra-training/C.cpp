#include<cstdio>
#include<climits>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int MAXN = 2005;

int N, M, s;
vector<int> G[MAXN];
vector<long long> W[MAXN];
bool in[MAXN];
int cnt[MAXN];
long long d[MAXN];
bool vis[MAXN];

void dfs( const int &u ){
	int v;
	vis[u] = true;
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( !vis[v] )
			dfs(v);
	}
}

int main(){
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);

	scanf("%d %d %d", &N, &M, &s);
	s--;
	
	int u, v;
	long long w;
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %lld", &u, &v, &w);
		u--, v--;
		G[u].push_back(v);
		W[u].push_back(w);
	}
	
	fill( d, d + N, LLONG_MAX );
	queue<int> Q;

	in[s] = true;
	Q.push(s);
	d[s] = 0;

	while ( !Q.empty() ){
		u = Q.front();
		Q.pop();
		in[u] = false;
		// relax
		for ( int i = 0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( d[u] + w < d[v] && cnt[v] < N ){
				d[v] = d[u] + w;
				if ( !in[v] ){
					cnt[v]++;	
					in[v] = true;
					Q.push(v);
				}
			}
		}
	}
	// we mark every vertex reachable from a negative cycle
	for ( int i = 0; i < N; ++i )
		if ( cnt[i] >= N && !vis[i] )
			dfs(i);	

	for ( int i = 0; i < N; ++i ){
		if ( d[i] == LLONG_MAX ) puts("*");
		else if ( vis[i] ) puts("-");
		else printf("%lld\n", d[i]);
	}
	return 0;
}

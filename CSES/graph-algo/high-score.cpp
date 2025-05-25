#include<cstdio>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 2505;

int N, M;
vector<int> G[MAXN];
vector<int> R[MAXN];
vector<int> W[MAXN];
long long d[MAXN];
int len[MAXN];

queue<int> q;
bool reach[MAXN];

void dfs( const int &u ){
	int v;
	for ( int i=0; i < (int)R[u].size(); ++i ){
		v = R[u][i];
		if ( !reach[v] ){
			reach[v] = true;
			dfs( v );
		}
	}
}

int main(){
	scanf("%d %d", &N, &M);

	int u, v, w;
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back( v );
		R[v].push_back( u );
		W[u].push_back( -w );
	}
	

	int s = 0, t = N - 1;
	// reachability in the reverse graph
	reach[t] = true;
	dfs(t);
	/* Initialize Bellman-Ford */
	fill( d, d + N, LLONG_MAX );
	q.push( s );
	d[s] = len[s] = 0;

	while ( !q.empty() ){
		u = q.front();
		q.pop();
		if ( len[u] >= N ) continue;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( d[u] + w < d[v] ){
				d[v] = d[u] + w;
				len[v] = len[u] + 1;
				q.push( v );
			}
		}
	}
	/* Check if we can reach a negative cycle from N - 1 */
	bool found = false;
	for ( int i=0; i < N; ++i )
		if ( len[i] >= N && reach[i] )
			found = true;

	if ( found ) puts("-1");
	else printf("%lld\n", -d[t]);
	return 0;
}

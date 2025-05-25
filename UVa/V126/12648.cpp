#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 505;

vector<int> G[MAXN];
int N, M, Q;
int rep[MAXN];		// id a vertex represents
int vertex[MAXN];	// the vertex associated to an id
int W[MAXN];
int t;
int timer[MAXN];
int ans[MAXN];

void dfs( const int &u ){
	int v;

	ans[u] = INT_MAX;
	timer[u] = t;
	//printf("DFS(%d)\n", u);
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		//printf("Visits %d\n", v);
		if ( timer[v] < t )
			dfs( v );
		ans[u] = min( ans[u], min( W[ rep[v] ], ans[v] ) );
	}
}

void process(){
	int u, v;

	for ( int i = 0; i < N; ++i ){
		scanf("%d", W + i );
		rep[i] = i;
		vertex[i] = i;
	}
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[v].push_back(u);	// add the reverse arc
	}
	fill( timer, timer + N, 0 );
	// Read the queries
	char opt;
	int vv, vu;
	for ( t = 1; t <= Q; ++t ){
		scanf(" %c", &opt);
		if ( opt == 'T' ){
			scanf("%d %d", &u, &v);
			u--, v--;
			vu = vertex[u];
			vv = vertex[v];
			rep[ vu ] = v;
			rep[ vv ] = u;
			swap( vertex[u], vertex[v] );
		}
		else {
			scanf("%d", &u );
			u--;
			dfs( vertex[u] );
			if ( ans[ vertex[u] ] == INT_MAX ) puts("*");
			else printf("%d\n", ans[ vertex[u] ] );
		}
	}
}

void clean(){
	for ( int i = 0; i < N; ++i )
		G[i].clear();
}

int main(){
	while ( scanf("%d %d %d", &N, &M, &Q) == 3 ){
		process();
		clean();
	}
	return 0;
}

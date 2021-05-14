#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXN = 500005;

vector<int> G[MAXN];
vector<int> W[MAXN];
int d[MAXN];
bool ok[MAXN];
int len[MAXN];
int best[MAXN];
int N, L, R;

inline int valid( const int &x ){
	return x >= L && x <= R;
}

void clean(){
	for ( int i=0; i < N; ++i ){
		G[i].clear();
		W[i].clear();
	}
}

void solve( const int &u ){
	int v;

	best[u] = ( d[u] )? INT_MAX:INT_MIN;

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( ok[v] ){ 
			solve( v );
			if ( d[u] ) best[u] = min( best[u], best[v] );
			else best[u] = max( best[u], best[v] );
		}
	}

	if ( best[u] == INT_MAX || best[u] == INT_MIN )
		best[u] = len[u];

}

void dfs( const int &u ){
	int v, w;

	ok[u] = valid( len[u] );

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		w = W[u][i];
		len[v] = len[u] + w;
		d[v] = d[u] ^ 1;
		dfs( v );
		ok[u] |= ok[v];
	}
}

void process(){
	int u, v, w;
	for ( int i=1; i < N; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(v); 
		W[u].push_back(w);
	}
	len[0] = 0;
	d[0] = 0;
	dfs( 0 );

	if ( ok[0] ){ 
		solve( 0 );
		printf("%d\n", best[0]);
	}
	else { 
		puts("Oh, my god!");
	}
}

int main(){
	while ( scanf("%d %d %d", &N, &L, &R) == 3 ){
		process();
		clean();
	}
	return 0;
}

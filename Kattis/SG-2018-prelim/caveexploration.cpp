#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 10005;
int N;
vector<int> G[MAXN];
int dfsnum[MAXN];
int low[MAXN];
int f[MAXN];
int num = 0;

inline int find_set( const int &u ){ return u == f[u]? u:( f[u] = find_set( f[u] ) ); }
inline void join( const int &u, const int &v ){ if ( u != v ) f[v] = u; }

bool dfs( const int &u, const int &p ){
	int v;

	low[u] = dfsnum[u] = num++;	
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ){
			if ( !dfs( v, u ) ) // If it is not a bridge
				join( find_set(u), find_set(v) );
			low[u] = min( low[u], low[v] );
		}
		else if ( dfsnum[v] < dfsnum[u] ){	// back-edge
			low[u] = min( low[u], dfsnum[v] );
			join( find_set(u) , find_set(v) );
		}
	}
	return low[u] == dfsnum[u];
}

int main(){
	int M;
	int u, v;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
	}
	for ( int i=0; i < N; ++i ){ 
		f[i] = i;
		low[i] = dfsnum[i] = -1;
	}
	dfs( 0, -1 );
	u = find_set( 0 );
	int res = 0;
	for ( int i=0; i < N; ++i )
		if ( find_set(i) == u ) res++;
	printf("%d\n", res);
	return 0;
}

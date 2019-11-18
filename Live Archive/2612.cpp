#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 1028;

int N;
vector<int> D[2*MAXN];
bool reach[2*MAXN];
int size[2*MAXN];
int pos[2*MAXN];
int f[2*MAXN];
int vis[2*MAXN];


inline int find_set( const int &x ){ return x==f[x]? x:(f[x] = find_set(f[x])); }
inline void union_set( const int &u, const int &v ){
	if ( u == v ) return;
	size[u] += size[v];
	pos[u] += pos[v];
	f[v] = u;
}

void dfs( const int &u ){
	int v;
	reach[u] = true;
	for ( int i=0; i < (int)D[u].size(); ++i ){
		v = D[u][i];
		if ( !reach[v] )
			dfs( v );
	}
}

void process(){
	char gar[20];
	int v;
	int u;

	for ( int i=0; i < 2*N; ++i  ){
		f[i] = i, size[i] = 1, pos[i] = ( i < N )? 1:0;
		vis[i] = false;
	}


	for ( u=0; u < N; ++u ){
		scanf("%s", gar);
		scanf("%d", &v); v--;
		scanf("%s", gar);
		scanf("%s", gar);
		if ( gar[0] == 't' ){
			D[u].push_back(v);
			D[u + N].push_back( v + N );
			union_set( find_set( u ), find_set( v ) );
			union_set( find_set( u + N ), find_set( v + N ) );
		}
		else {
			D[u].push_back( v + N );
			D[u + N].push_back( v );
			union_set( find_set( u ), find_set( v + N ) );
			union_set( find_set( u + N ), find_set( v ) );			
		}
	}

	bool ok = true;
	for ( int i=0; i < N && ok; ++i ){
		fill( reach, reach + 2*N, false );
		dfs( i );
		ok = !reach[i + N];
	}
	
	for ( int i=0; i < 2*N; ++i ){
		D[i].clear();
	}

	if ( !ok ){
		puts("Inconsistent");
		return;
	}
	int res = 0;

	for ( int i=0; i < N; ++i ){
		u = find_set( i );
		if ( vis[u] ) continue;
		res += max( pos[u], size[u] - pos[u] );
		vis[u] = true;
		u = find_set( i + N );
		vis[u] = true;
	}
	printf("%d\n", res);
}

int main(){

	while ( scanf("%d", &N) && N )
		process();

	return 0;
}

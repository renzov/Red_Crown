#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 200002;

vector<int> G[MAXN];
int color[MAXN];

int dfs( const int &u, const int &p ){
	int v;
	int sum = 1;
	for ( int i = 0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( color[v] == -1 ){
			color[v] = 1 - color[u];
			sum += dfs( v, u );
		}
	}
	return sum;
}

int main(){
	int N, M; 
	int u, v;
	scanf("%d %d", &N, &M);

	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back( v ), G[v].push_back( u );
	}
	fill( color, color + N, -1 );
	bool ok = true;
	for ( int i = 0; i < N && ok; ++i )
		if ( color[i] == -1 ){
			color[i] = 0;
			if ( dfs( i, -1 ) == 1 ) 
				ok = false;
		}
	if ( !ok ) puts("NIE");
	else {
		puts("TAK");
		for ( int i = 0; i < N; ++i )
			if ( color[i]  ) puts("K");
			else puts("S");
	}
	return 0;
}

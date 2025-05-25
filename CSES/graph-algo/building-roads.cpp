#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> G[MAXN];
int color[MAXN];
int rep[MAXN];

void dfs( const int &u ){
	int v;

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( color[v] == -1 ){
			color[v] = color[u];
			dfs( v );
		}
	}
}

int main(){
	int u, v;
	int N, M;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	
	int ncomp = 0;
	fill( color, color + N, -1 );
	for ( int i=0; i < N; ++i )
		if ( color[i] == -1 ){
			rep[ncomp] = i;
			color[i] = ncomp++;
			dfs( i );
		}
	printf("%d\n", ncomp - 1);
	for ( int i=1; i < ncomp; ++i )
		printf("%d %d\n", rep[i - 1] + 1, rep[i] + 1);
	return 0;
}

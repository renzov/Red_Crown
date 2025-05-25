#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

int N, M;
vector<int> G[MAXN];
int color[MAXN];
bool error;

void dfs( const int &u ){
	int v;
	int inv = 3 - color[u];

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( !color[v] ){
			color[v] = inv;
			dfs( v );
		} 
		else if ( color[v] != inv ) {
			error = true;
		}
	}
}

int main(){
	scanf("%d %d", &N, &M);
	
	int u, v;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	
	error = false;
	for ( int i=0; i < N; ++i )
		if ( !color[i] ){
			color[i] = 1;
			dfs(i);
		}

	if ( error ){ 
		puts("IMPOSSIBLE");
	}
	else {
		printf("%d", color[0]);
		for ( int i=1; i < N; ++i )
			printf(" %d", color[i]);
		puts("");
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
const int MAXN = 256;
vector< vector<int> > cycles;
vector<int> G[MAXN];
int num, top;
int dfsnum[MAXN];
int S[MAXN];
int pos[MAXN];

void dfs( const int &u, const int &p ){
	dfsnum[u] = num++;
	// Push u into stack
	pos[u] = top;
	S[top++] = u;
	
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ){
			dfs( v, u );
		}
		else if ( dfsnum[v] < dfsnum[u] ){	// back edge
			vector<int> C;	// Retrieve cycle
			assert( pos[v] != -1 );
			for ( int j=pos[v]; j < top; ++j )
				C.push_back( S[j] );
			cycles.push_back(C);
		}
	}
	// Pop u from stack
	top--;
	pos[u] = -1;
}

int main(){
	int N, M;
	int u, v;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	fill( dfsnum, dfsnum + N, -1 );
	num = top = 0;
	for ( int i=0; i < N; ++i )
		if ( dfsnum[i] == -1 )
			dfs( i, -1 );

	printf("%d\n", (int)cycles.size());
	for ( int i=0; i < cycles.size(); ++i ){
		printf("%d", (int)cycles[i].size() );
		for ( int j=0; j < (int)cycles[i].size(); ++j )
			printf(" %d", cycles[i][j] + 1);
		puts("");
	}
	return 0;
}

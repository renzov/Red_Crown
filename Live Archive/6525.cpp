#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
const int MAXN = 128;

int N;
int n, m;
char T[MAXN][MAXN];
int R[MAXN][MAXN];
int C[MAXN][MAXN];

vector<int> G[MAXN*MAXN];
bool vis[MAXN*MAXN];
int match[MAXN*MAXN];

bool alt_path( const int &u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( match[v] == -1 || alt_path( match[v] ) ){
			match[v] = u;
			return true;
		}
	}
	return false;
}

void process(){
	for ( int i=0; i < N; ++i )
		scanf("%s", T[i]);
	n = 0;
	m = 0;
	// Mark in row order
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < N; ++j ){
			if ( T[i][j] == '.' ){
				if ( j && T[i][j - 1] == '.' )
					R[i][j] = R[i][j - 1];
				else 
					R[i][j] = n++;
			}
		}
	}
	// Mark in column order
	for ( int j=0;  j < N; ++j ){
		for ( int i=0; i < N; ++i ){
			if ( T[i][j] == '.' ){
				if ( i && T[i-1][j] == '.' )
					C[i][j] = C[i-1][j];
				else
					C[i][j] = m++;
			}
		}
	}
	// Add the edges in the bipartite graph
	int u, v;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			if ( T[i][j] == '.' ){
				u = R[i][j];
				v = C[i][j];
				G[u].push_back(v);
			}
	// Find a maximum matching in G
	int res = 0;
	fill( match, match + m, -1 ); 
	for ( int i=0; i < n; ++i ){
		fill( vis, vis + n, false );
		if ( alt_path( i ) ) res++;
	}
	printf("%d\n", res);
	// Clean memory
	for ( int i=0; i < n; ++i )
		G[i].clear();
}

int main(){
	while ( scanf("%d", &N) == 1 )
		process();
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<cassert>
using namespace std;
const int MAXM = 1505;

int N, M;
int t;
int vis[MAXM];
int match[MAXM];
vector<int> G[MAXM];

vector<int> D[2*MAXM];
int dfsnum[2*MAXM];
int low[2*MAXM];
int num = 0;
int in[2*MAXM];
stack<int> S;
int c = 0;
int comp[2*MAXM];

char adj[MAXM][MAXM];

void dfs( const int &u ){
	dfsnum[u] = low[u] = num++;
	S.push( u );
	in[u] = true;

	int v;
	for ( int i=0; i < (int) D[u].size(); ++i ){
		v = D[u][i];
		if ( dfsnum[v] == -1 ){
			dfs( v );
			low[ u ] = min( low[u], low[v] );
		}
		else if ( in[v] ){ // back arc
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	
	if ( low[u] == dfsnum[u] ){ // strongly connected component found
		c++;
		do {
			v = S.top();
			S.pop();
			in[v] = false;
			comp[v] = c;
		}
		while ( v != u );
	}
}

bool alt_path( const int &u ){
	if ( vis[u] == t ) return false;
	vis[u] = t;
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

int main(){

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%s", adj[i] );
		for ( int j=0; j < M; ++j ){
			if ( adj[i][j] == '1' ){ 
				G[i].push_back( j );
			}
		}
	}	
	// Complete the graph
	for ( int i=N; i < M; ++i )
		for ( int j=0; j < M; ++j )
			adj[i][j] = '1';
	
	fill( match, match + M, -1 );
	t = 0;
	int res = 0; // size of a max. matching between N and M
	for ( int i=0; i < N; ++i ){
		t++;
		if ( alt_path(i) )
			res++;
	}
	
	if ( res < N ){ // No matching convering N
		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < M; ++j ) 
				putchar('1');
			puts("");
		}
	}
	else {
		// Complete the matching if needed
		int nxt = N;	
		for ( int i=0; i < M; ++i )
			if ( match[i] == -1 )
				match[i] = nxt++;
		// First construct the alt-path digraph
		int u, v;
		for ( u = 0; u < M; ++u ){
			for ( v = 0; v < M; ++v ){
				if ( adj[u][v] == '1' ){ 
					if ( match[v] != u )
						D[ u ].push_back( match[v] );		
				}
			}
		}
		// Find the strongly connected components in D
		fill( dfsnum, dfsnum + M, -1 );
		for ( u = 0; u < M; ++u ){
			if ( dfsnum[u] == -1 )
				dfs( u );
		}
		// Finally print the answer
		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < M; ++j ){
				if ( adj[i][j] == '1' && (match[j] == i || comp[i] == comp[ match[j] ]) )
					putchar('0');
				else
					putchar('1');
			}
			puts("");
		}
	}
	return 0;
}


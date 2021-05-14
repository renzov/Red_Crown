#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
int N, M;
int V;
vector<int> G[MAXN << 1];
// Variables for strongly connected components
int num;
int C;
int comp[MAXN << 1];
bool in[MAXN << 1];
int low[MAXN << 1];
int dfsnum[MAXN << 1];
stack<int> S;

void clean(){
	for ( int i=0; i < V; ++i )
		G[i].clear();
	
	while ( !S.empty() )
		S.pop();
}

inline int neg( const int &x ){
	return (x <= N)? (x + N + 1):(x - N - 1); 
}

inline int variable( const int &x ){
	return ( x < 0 )? (N + 1 - x):x;
}

void dfs( const int &u ){
	int v;
	
	dfsnum[u] = low[u] = num++;
	S.push(u);
	in[u] = true;
	
	for ( int i=0;  i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			dfs( v );
			low[u] = min( low[v], low[u] );
		}
		else if ( in[v] ){ // if it is not a cross arc
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	
	if ( low[u] == dfsnum[u] ){ // New strongly connected component found
		do {
			v = S.top();
			S.pop();
			in[v] = false;
			comp[v] = C;
		}
		while ( v != u );
		C++;
	}
}

void add_clause( const int &p, const int &q ){ // (p or q)
	G[ neg(p) ].push_back( q );	//printf("%d -> %d\n", neg(p), q);
	G[ neg(q) ].push_back( p ); //printf("%d -> %d\n", neg(q), p);
}

void process(){
	int x,  y;
	
	V = 2*N + 2;	// Number of vertices in the implication graph
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &x, &y);
		add_clause( variable(x), variable(y) );
	}
	add_clause( 0, 1 );	 		// x_0 or x_1
	add_clause( N + 1, 1 );	 	// !x_0 or x_1
	// Initialize
	C = num = 0;
	fill( dfsnum, dfsnum + V, -1 );
	fill( in, in + V, false );
	// Find strongly connected components
	for ( int i=0; i < V; ++i )
		if ( dfsnum[i] == -1 ) dfs( i );
	
	// Check if it is satisfiable
	bool ok = true;
	for ( int i=0; i <= N && ok; ++i )
		ok &= (comp[i] != comp[i + N + 1]);
	
	puts( ok? "yes":"no" );
	clean();
}

int main(){
	while ( scanf("%d %d", &N, &M) == 2 )
		process();

	return 0;
}

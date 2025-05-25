#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 100005;
const int LOG = 19;
typedef pair<int, int> edge;

int N, M, Q;
edge E[MAXN];
char res[MAXN];
vector<int> G[MAXN];
vector<int> T[MAXN];

int P[MAXN][LOG];
int L[MAXN];
int up[MAXN];
int X[MAXN], Y[MAXN]; 

int f[MAXN]; // for merging edges
int dfsnum[MAXN];
int low[MAXN];
int num;


inline int find_set( const int &u ){
	return u == f[u]? u:( f[u] = find_set( f[u] ) ); 
}

inline int nxt( const int &e, const int &u ){
	return E[e].first == u? E[e].second:E[e].first;
}

int lca( int u, int v ){
	if ( L[u] > L[v] ) swap( u, v );
	if ( u == v ) return u;
	for ( int i=LOG - 1; i >= 0; --i )
		if ( L[v] - (1 << i) >= L[u] ){
			v = P[v][i];
		}
	if ( u == v ) return u;
	for ( int i=LOG - 1; i >= 0; --i ){
		if ( P[u][i] != -1 && P[u][i] != P[v][i] )
			u = P[u][i], v = P[v][i];
	}
	return P[u][0];
}

void dfs( const int &u, const int &p ){
	int v, e;
	dfsnum[ u ] = low[ u ] = num++;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		e = G[u][i];
		v = nxt( e, u );
		if ( e == p ) continue;
		if ( dfsnum[v] == -1 ){
			dfs( v, e );
			low[u] = min( low[u], low[v] );
		}
		else {	// back edge
			low[u] = min( low[u], dfsnum[v] );
		}
		if ( low[v] <= dfsnum[u] ){	// Not a bridge
			int ru = find_set( u );
			int rv = find_set( v );
			if ( ru != rv ){ 
				if ( dfsnum[ru] < dfsnum[rv] )
					f[ rv ] = ru;
				else 
					f[ ru ] = rv;
			}
			res[ e ] = 'B';	
		}
	}
}

void level( const int &u ){
	int e;
	int v;	
	for ( int i=0; i < (int)T[u].size(); ++i ){
		e = T[u][i];
		v = nxt( e, u );
		L[v] = L[u] + 1;
		level( v );
	}
}

void merge( int u, int v, const int &d ){
	int e;
	int rx, ry;
	while ( L[u] > L[v] ){
		e = up[ u ];
		rx = find_set( E[e].first );
		ry = find_set( E[e].second );
		if ( rx == u ){
			res[ e ] = ( d > 0 )? 'R':'L';
			f[ rx ] = ry;
			u = ry;	
		}
		else {
			res[ e ] = ( d > 0 )? 'L':'R'; 
			f[ ry ] = rx;
			u = rx;
		}
	}
}

int main(){
	int u, v, w;

	scanf("%d %d", &N, &M);

	fill( res, res + M, '-' );

	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		E[i].first = u, E[i].second = v;
		if ( u == v ){
			res[i] = 'B';
			continue;
		}
		G[u].push_back( i ), G[v].push_back( i );
	}
	
	for ( int i=0; i < N; ++i ) f[i] = i;

	fill( dfsnum, dfsnum + N, -1 );
	num = 0;
	for ( int i=0; i < N; ++i )
		if ( dfsnum[i] == -1 )
			dfs( i, -1 );
	// Initialize for LCA computation
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < LOG; ++j )
			P[i][j] = -1;
	fill( up, up + N, -1 );
	// Create a tree from the bridges
	for ( int i=0; i < M; ++i ){
		u = E[i].first, v = E[i].second;
		u = find_set( u ), v = find_set( v );	
		if ( u != v ){
			E[i].first = u, E[i].second = v;
			if ( dfsnum[u] < dfsnum[v] ){ 
				T[u].push_back( i );
				P[v][0] = u;
				up[ v ] = i;	// edge to go up in the tree
			}
			else { 
				T[v].push_back( i ); 
				up[ u ] = i;	// edge to go up in the tree
				P[u][0] = v;
			}
		}
	}
	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d", X + i, Y + i);
		X[i]--, Y[i]--;
		X[i] = find_set( X[i] );
		Y[i] = find_set( Y[i] );
	}
	// Find the level of each vertex
	for ( int i=0; i < N; ++i ){
		if ( find_set( i ) == i && P[i][0] == -1 ){
			L[i] = 0;
			level( i );
		}
	}
	// Binary lifting
	for ( int j=1; j < LOG; ++j )
		for ( int i=0; i < N; ++i ){
			if ( P[i][j - 1] != -1 )
				P[i][j] = P[ P[i][j - 1] ][j -  1]; 
		}

	for ( int i=0; i < Q; ++i ){
		u = X[i], v = Y[i];
		w = lca( u, v );
		// Look for the sets containing these vertices
		u = find_set( u );
		v = find_set( v );
		w = find_set( w );
		if ( u != w ) merge( u, w, 1 );
		if ( v != w ) merge( v, w, -1 );
	}	
	for ( int i=0; i < M; ++i ){
		if ( res[i] == '-' ) res[i] = 'B';
		putchar( res[i] );
	}	
	puts("");

	return 0;
}

#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 20005;
const int LOG = 19;

vector<int> G[MAXN];
map<int, int> idx;
map<pii, int> W;

bool calc[MAXN]; // If the vertex values is known 
int V[MAXN]; // Value of the vertex
bool vis[MAXN];
int sum[MAXN];	// To uncover values
/* For LCA and other computations */
int P[MAXN][LOG];
int d[MAXN];
int dfsnum[MAXN]; // To discover back edges
int num;
int comp[MAXN]; // Component of the vertex
int ncomp;
int N = 0;

int res;

int get_id( const int &x ){
	return idx.count(x) == 0? (idx[x] = N++):idx[x];
}

int get_id2( const int &x ){
	return idx.count(x) == 0? -1:idx[x];
}

void uncover( int u ){
	vis[u] = true;
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( !vis[v] ){
			V[v] = W[ pii(u,v) ] - V[u];
			calc[v] = true;
			uncover(v);
		}
	}
}

void dfs( int u, int p ){
	/* Set initial values */
	dfsnum[u] = num++;
	comp[u] = ncomp;
	d[u] = ( p == -1 )? 0:(d[p] + 1);
	P[u][0] = p;
	
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( p == v ) continue;
		if ( dfsnum[v] == -1 ){
			/* dfs tree edge - calculate the sum and traverse */
			if ( d[u] & 1 ) sum[v] = sum[u] - W[pii(u,v)];
			else sum[v] = sum[v] = sum[u] + W[pii(u,v)];
			dfs( v , u );
		}
		else if ( dfsnum[v] < dfsnum[u] && !((d[u] - d[v]) & 1)  ){ // Back edge - odd cycle
			calc[v] = true;
			if ( d[v] & 1 ){
				V[v] = -( sum[u] - sum[v] - W[pii(u,v)] ) / 2;
			}
			else {
				V[v] = ( sum[u] - sum[v] + W[pii(u,v)] ) / 2;			
			}
		}
	}
}

int lca( int u, int v ){
	// u is deeper in the tree than v
	int log;
	for ( log = 1; (1 << log) <= d[u]; ++log );
	log--;
	for ( int i=log; i >= 0; --i )
		if ( (d[u] - d[v]) >= (1 << i) )
			u = P[u][i];

	if ( u == v ) return u;
	for ( int i=log; i >= 0; --i ){
		if ( P[u][i] != -1 && P[u][i] != P[v][i] )
			u = P[u][i], v = P[v][i];
	}
	return P[u][0];
}

bool test_bip( int u, int v ){
	if ( d[u] < d[v] ) swap( u , v );
	int x = lca( u , v );
	int len = d[u] + d[v];
	if ( (len & 1) == 0 ) return false;
	/* Calculate answer */
	if ( v == x ){
		if ( d[v] & 1 ) res = -( sum[u] - sum[v] );
		else res = sum[u] - sum[v];
	}
	else {
		if ( (d[v] - d[x]) & 1 ) swap(u, v); // u is the vertex with odd length path to lca
		if ( d[x] & 1 ) res = sum[v] - sum[u];
		else res = sum[u] - sum[v];
	}
	return true;
}

int main(){
	int M, Q;
	int x, y, w;
	int u, v;
	while ( scanf("%d %d", &M, &Q) && M ){
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &x, &y, &w);
			u = get_id( x );
			v = get_id( y );
			if ( u != v && W.count( pii(u,v) ) == 0 ){
				G[u].push_back( v );
				G[v].push_back( u );
				W[ pii(u,v) ] = W[ pii(v,u) ] = w;
			}
			else if ( u == v ){ // info from a generator
				calc[u] = true;
				V[u] = w;
			}
		}
		num = ncomp = 0;
		for ( int i=0; i < N; ++i ){
			dfsnum[i] = -1;
			for ( int j=1; (1<<j) < N; ++j )
				P[i][j] = -1;
		}
		/* From every component, we try to find an odd cycle */
		for ( int i=0; i < N; ++i ){
			if ( dfsnum[i] == -1 ){
				sum[i] = 0;
				dfs( i , -1 );
				ncomp++;
			}
		}

		fill( vis, vis + N, false );
		/* Now, discover all the values we can deduce */
		for ( int i=0; i < N; ++i ){
			if ( !vis[i] && calc[i] ) uncover(i);
		}
		/* Preprocess for LCA computation */
		for ( int j=1; (1 << j) < N; ++j ){
			for ( int i=0; i < N; ++i ){
				if ( P[i][j-1] != -1 )
					P[i][j] = P[ P[i][j-1] ][j-1];
			}
		}

		for ( int i=0; i < Q; ++i ){
			scanf("%d %d", &x, &y);		
			u = get_id2( x );
			v = get_id2( y );
			if ( u == -1 || v == -1 ) puts("*");
			else if ( calc[u] && calc[v] ) printf("%d\n", u == v? V[u]:(V[u] + V[v]) );
			else if ( u == v || comp[u] != comp[v] ) puts("*"); 
			else if ( test_bip(u, v) ) printf("%d\n", res); 
			else puts("*");
		}
		puts("-");
		// clear memory for next testcase
		for ( int i=0; i < N; ++i ){ 
			G[i].clear();
			calc[i] = false;
		}
		W.clear();
		idx.clear();
		N = 0;
	}
	return 0;
}


#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 10005;
const int LOG = 19; 
int N, M, Q;
vector<int> G[MAXN];

int dfsnum[MAXN];
int low[MAXN];
int comp[MAXN]; // Component
int d[MAXN];
int f[MAXN];
int P[LOG][MAXN];
int ord[MAXN];

int ncomp;
int num;

void dfs( int u, int p ){
	P[0][u] = p;
	d[u] = ( p == -1 )? 0:d[p] + 1;
	comp[u] = ncomp;
	ord[num] = u;
	dfsnum[u] = num++;

	low[u] = dfsnum[u];
	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ){
			dfs( v, u );
			low[u] = min( low[u], low[v] ); 
		}
		else {
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	// set edge as a bridge	
	f[u] = (p == -1 || low[u] < dfsnum[u])? 0:1;
}

int lca( int u, int v ){
	if ( d[u] < d[v] ) swap( u , v );

	int log;
	for ( log=1; (1 << log) <= d[u]; ++log );
	log--;

	for ( int i=log; i >= 0; i-- )
		if ( ( 1 << i ) <= d[u] - d[v] )
			u = P[i][u];

	if ( u == v ) return u;

	for ( int i=log; i >= 0; --i ){
		if ( P[i][u] != -1 && P[i][u] != P[i][v] )
			u = P[i][u], v = P[i][v];
	}
	return P[0][u];
}

int main(){
	int u, v, w;
	while ( scanf("%d %d %d", &N, &M, &Q) && N ){
		while ( M-- ){
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		/* Initialize */
		for ( int i=0; (1 << i) < N; ++i )
			fill( P[i] , P[i] + N, -1 );
		
		fill( dfsnum, dfsnum + N, -1 );
		num = ncomp = 0;

		for ( int i=0; i < N; ++i ){
			if ( dfsnum[i] == -1 ){
				ncomp++;
				dfs( i , -1 );
			}
		}
		// Process vertices in dfs order to calculate f
		for ( int i=0; i < N; ++i ){
			u = ord[i];
			if ( P[0][u] != -1 ){
				f[u] += f[ P[0][u] ]; 
			}
		}
		/* Precalc for LCA */
		for ( int i=1; (1 << i) < N; ++i ){
			for ( int j=0; j < N; ++j )
				if ( P[i-1][j] != -1 ) 
					P[i][j] = P[ i - 1 ][ P[i-1][j] ];
		}
		/* Process each query */
		while ( Q-- ){
			scanf("%d %d", &u, &v);
			u--, v--;
			if ( comp[u] != comp[v] ){
				puts("N");
				continue;
			}
			w = lca( u, v );
			if ( f[u] - f[w] == d[u] - d[w] && f[v] - f[w] == d[v] - d[w] )
				puts("Y");
			else 
				puts("N");
		}
		puts("-");
		// Clear memory
		for ( int i=0; i < N; ++i ) G[i].clear();

	}
	return 0;
}


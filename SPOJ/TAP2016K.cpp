#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

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

const int MAXN = 100005;
int C[MAXN];
vector<int> G[MAXN];
int N, M, P;
int pre[MAXN];
bool found;

int idx[MAXN];
int presum[MAXN];
int bestpath[MAXN];

int pathL[MAXN];
int pathR[MAXN];
int segL[4*MAXN];
int segR[4*MAXN];


void find_path( const int &u , const int &p ){
	int v;
	pre[u] = p;
	if ( u == P ) found = true;
	if ( found ) return;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( pre[v] == -1 ) find_path( v, u );
	}
}

int dfs( const int &u, const int &p ){
	int v;
	int best = 0;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v != p ) best = max( best, dfs(v, u) );
	}
	return C[u]	+ best;
}

void build( int node, int L, int R ){
	if ( L==R ){
		segL[node] = pathL[L];
		segR[node] = pathR[R];
		return;
	}
	int m = (L + R) >> 1;
	build( node<<1, L, m );
	build( (node<<1)|1, m+1, R );
	segL[node] = max( segL[node<<1], segL[(node<<1)|1] );
	segR[node] = max( segR[node<<1], segR[(node<<1)|1] );
}

int query( int *seg, const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R ) return seg[node];
	int m = ( L + R ) >> 1;
	if ( r <= m ) return query( seg, node<<1, L, m, l , r );
	if ( l > m ) return query( seg, (node<<1)|1, m+1, R, l, r );
	return max( query( seg, node<<1, L, m, l, m ),
				query( seg, (node<<1)|1, m+1, R, m+1, r ) );
}

void preprocess(){
	int u, v;
	int size = 0;
	u = P;
	// get the path from P to M
	while ( u != M ){
		idx[size++] = u; u = pre[u];
	}
	// preffix sum of the cost of the vertices along the path from P to M 
	presum[ 0 ] = C[ idx[0] ];
	for ( int i=1; i < size; ++i ) presum[i] = presum[ i-1 ] + C[ idx[i] ];
	// Get the longest path outside the path from P to M for each vertex
	for ( int i=0; i < size; ++i ){
		u = idx[i];
		bestpath[u] = 0;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			if ( (i == 0  || v != idx[i-1]) && ( i == (N-1) || v != idx[i+1] ) ){
				bestpath[u] = max( bestpath[u] , dfs( v , u ) );
			}
		}
	}
	// Calculate auxiliar info for main dp
	int sum = 0;
	pathL[0] = bestpath[0];
	for ( int i=1; i < size; ++i ){
		sum += C[ idx[i] ];
		pathL[i] = sum + bestpath[i];
	}
	sum = 0;
	pathR[size-1] = bestpath[size-1];
	for ( int i=size-2; i >= 0; --i ){
		sum += C[ idx[i] ];
		pathR[i] = sum + bestpath[i];
	}
	build( 1, 0, size-1 );
}

int main(){
	int u, v;

	while ( scanf("%d %d %d", &N, &M, &P) != EOF ){
		M--, P--;
		for ( int i=0; i < N; ++i ) scanf("%d", C+i);
		for ( int i=1; i < N; ++i ){ 
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		fill( pre, pre + N, -1 );
		found = false;

		find_path( M, -1 );
		preprocess();


		// Clean up the memory
		for ( int i=0; i < N; ++i ) G[i].clear();
	}

	return 0;
}


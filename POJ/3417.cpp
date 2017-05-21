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
int LOG;
const int MAXN = 100005;
vector<int> T[MAXN];
int N, M;
int h[MAXN];
int P[MAXN][17];
int dp[MAXN] = {0};
long long res;

int from[2*MAXN];
int to[2*MAXN];
int nxt[2*MAXN];
int head[MAXN] = {0};
int e = 1; 

void add_edge( int u, int v ){
	from[e] = u, to[e] = v, nxt[e] = head[u], head[u] = e; e++;
	from[e] = v, to[e] = u, nxt[e] = head[v], head[v] = e; e++;
}

void precalc( int u , int p ){
	if ( p == -1 ) h[u] = 0;
	else h[u] = h[p] + 1;

	// precalc
	int last = p;
	P[u][0] = last;
	for ( int i=1; i < LOG; ++i ){
		if ( last != -1 ){
			P[u][i] = P[ last ][i - 1];
			last = P[last][i - 1];
		}
		else { 
			break;
		}
	}

	for ( int f=head[u]; f > 0; f = nxt[f] ){
		if ( to[f] != p ) precalc( to[f] , u );
	}
}

int query( int u, int v ){
	if ( h[u] < h[v] ) return query( v , u );
	// h[u] >= h[v]
	int diff = h[u] - h[v];
	for ( int i=LOG; i >= 0; --i ){
		if ( (diff >> i) & 1 )
			u = P[u][i];
	}
	
	if ( u == v ) return u;
	
	for ( int i=LOG; i >= 0; --i ){
		if ( P[u][i] != -1 && P[u][i] != P[v][i] )
			u = P[u][i], v = P[v][i];
	}
	return P[u][0];
}

void dfs( int u, int p ){
	int v;
	for ( int f=head[u]; f > 0; f = nxt[f] ){
		v = to[f];
		if ( v != p ){
			dfs( v, u );
			dp[ u ] += dp[ v ];
		}
	}
	if ( p != -1 ){
		if ( dp[u] == 0 ) res += M;
		else if ( dp[u] == 1 ) res++;
	}
}

int main(){
	int u, v;
	int w;

	scanf("%d %d", &N, &M);
	
	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		add_edge( u , v );
	}

	for ( LOG = 0; (1<<LOG) < N; LOG++ );

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < LOG; ++j )
			P[i][j] = -1;
	
	precalc( 0, -1 );

	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		dp[u]++, dp[v]++;
		w = query( u , v );
		dp[w] -= 2;
	}

	res = 0;
	dfs(0, -1);

	printf("%lld\n", res);
	return 0;
}


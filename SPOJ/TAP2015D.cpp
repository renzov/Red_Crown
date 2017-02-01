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

const int MAXN = 1024;

int N;
bool G[MAXN][MAXN];
int deg[MAXN];
bool vis[MAXN];

pii dfs( int u ){
	vis[u] = true;
	pii temp;
	int size = 1, d = deg[u];
	for ( int v = 0; v < N; ++v )
		if ( G[u][v] && !vis[v] ){
			temp = dfs( v );
			size += temp.first;
			d += temp.second;
		}
	return pii( size, d );
}

int main(){
	int M, R, E;
	int u, v;

	while ( scanf("%d %d %d %d", &N, &M, &R, &E) != EOF ){
		// Clean memory
		for ( int i=0; i < N; ++i ){ 
			fill( G[i], G[i] + N, false );
			deg[i] = 0;
			vis[i] = false;
		}

		while ( M-- ){
			scanf("%d %d", &u, &v);
			u--, v--;
			if ( !G[u][v] ){
				G[u][v] = G[v][u] = true;
				deg[u]++, deg[v]++;
			}
		}
		pii comp;	//comp.first = num-vertex ; comp.second = deg-sum 
		int A, B;
		long long res = 0;
		for ( int i=0; i < N; ++i ){
			if ( !vis[i] ){
				comp = dfs( i );
				A = comp.first * E;
				M = (comp.first * (comp.first - 1)) >> 1;
				M -= (comp.second >> 1);
				B = M * R;
				if ( A <= B ) res += A;
				else res += B;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}


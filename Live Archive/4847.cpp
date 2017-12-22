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
const int MOD = 9999991;
const int MAXN = 32;
int N;
int T[MAXN][2];
int V[MAXN];
int comb[MAXN][MAXN];
int size[MAXN];
int root;

int C( const int &x, const int &y ){
	if ( x == 0 || y == 0 ) return 1;
	if ( comb[x][y] != -1 ) return comb[x][y];
	int &res = comb[x][y];
	res = ( C(x-1,y) + C(x,y-1) ) % MOD;
	return res;
}

void insert( int u, int v ){
	size[u]++;
	if ( V[v] < V[u] ){ // Go to the left
		if ( T[u][0] == -1 ){
			T[u][0] = v;
			size[v] = 1;
		}
		else {
			insert( T[u][0] , v );
		}
	}
	else {
		if ( T[u][1] == -1 ){
			T[u][1] = v;
			size[v] = 1;
		}
		else {
			insert( T[u][1] , v );
		}
	}
}

long long dfs( int u ){
	if ( T[u][0] == -1 && T[u][1] == -1 ) return 1;
	if ( T[u][0] == -1 ) return dfs( T[u][1] );
	if ( T[u][1] == -1 ) return dfs( T[u][0] );
	long long left = dfs( T[u][0] );
	long long right = dfs( T[u][1] );
	long long res = (left * right) % MOD;
	res = ( res * C( size[ T[u][0] ], size[ T[u][1] ] ) ) % MOD ;
	return res;
}

int main(){
	int runs;
	scanf("%d", &runs);
	for ( int i=0; i < 22; ++i ){
		fill( comb[i], comb[i] + 22, -1 );
	}
	while ( runs-- ){
		scanf("%d", &N);
		// Initialize
		for ( int i=0; i < N; ++i ){
			T[i][0] = T[i][1] = -1;
			size[i] = 0;
		}
		root = -1;
		for ( int i=0; i < N; ++i ){
			scanf("%d", V + i);
			if ( root != -1 ){
				insert( root, i );
			}
			else {
				root = i;
				size[root] = 1;
			}
		}
		printf("%lld\n", dfs( root ));
	}
	return 0;
}


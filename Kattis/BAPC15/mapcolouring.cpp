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

const int MAXN = 20;
int N, M;
int all;
bool G[MAXN][MAXN];
int color[MAXN];

inline bool belongs( const int &mask, const int &x ){
	return ((mask >> x)&1) != 0;
}

bool onecolor( int mask ){
	for ( int i=0; i < N; ++i ){
		if ( belongs(mask, i) ){
			for ( int j=i + 1; j < N; ++j ){
				if ( belongs(mask, j) && G[i][j] ){
					return false;
				}
			}
		} 
	}
	return true;
}

bool dfs( const int &u, const int &mask ){
	bool ok = true;
	for ( int v=0; v < N && ok; ++v ){
		if ( belongs( mask, v ) && G[u][v] ){
			if ( color[v] == -1 ){ 
				color[v] = 1 - color[u];
				ok &= dfs( v, mask );
			}
			else {
				ok &= ( color[u] != color[v] );
			}
		}
	}
	return ok;
}

bool bicolor( int mask ){
	fill( color, color + N, -1 );
	for ( int i=0; i < N; ++i ){
		if ( belongs( mask, i ) && color[i] == -1 ){
			color[i] = 0;
			if  ( !dfs( i, mask ) ) return false;
		}
	}
	return true;
}

bool tricolor(){
	for ( int mask=1; mask < (1 << N); ++mask ){
		if ( onecolor( mask ) && bicolor( all ^ mask ) ) return true;
	}
	return false;
}

bool fourcolor(){
	for ( int mask=1; mask < (1 << N); ++mask ){
		if ( bicolor(mask) && bicolor( all ^ mask ) ) return true;
	}
	return false;
}

int main(){
	int u, v;
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		memset( G, false, sizeof(G) );
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &u, &v);
			G[u][v] = G[v][u] = true;
		}
		all = (1 << N) - 1;
		if ( M == 0 ){
			puts("1");
		}
		else if ( bicolor( (1 << N) - 1 ) ){
			puts("2");
		}
		else if ( tricolor() ) {
			puts("3");
		}
		else if ( fourcolor() ){
			puts("4");
		}
		else {
			puts("many");
		}
	}
	return 0;
}


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

const int MAXN = 105;

int N, M, K, C;
int D[MAXN][MAXN];
bool vis[MAXN];
int match[2*MAXN];
int T;

bool alt_path( int u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	for ( int v=0; v < M; ++v ){
		if ( D[u][v] <= T ){
			if ( match[v] == -1 ){
				match[v] = u;
				return true;
			}
			else if ( alt_path(match[v]) ){
				match[v] = u;
				return true;
			} 
		}
		if ( D[u][v] <= (T - C) ){
			if ( match[v + M] == -1 ){
				match[v + M] = u;
				return true;
			}
			else if ( alt_path( match[v+M] ) ){
				match[v + M] = u;
				return true;
			}
		}
	}
	return false;
}

bool possible(){
	int f = 0;
	fill( match, match + 2*M, -1 );
	for ( int i=0; i < N && f < K; ++i ){
		fill( vis, vis + N, false );
		if ( alt_path(i) ) f++;
	}
	return f >= K;
}

int main(){
	int m;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		m = 0;
		scanf("%d %d %d %d", &N, &M, &K, &C);
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < M; ++j ){
				scanf("%d", &D[i][j]);
				if ( m < D[i][j] ) m = D[i][j];
			}

		int l = 0, r = m + C;
		while ( r - l > 1 ){
			m = ( l  + r ) >> 1;
			T = m;
			if ( possible() ) r = m;
			else l = m;
		}
		printf("%d\n", r);
	}
	return 0;
}


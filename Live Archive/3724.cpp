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

int G[MAXN][MAXN];
int deg[MAXN];
int cmp;
int p[MAXN];
bool ok;

inline void make_set( int x ){ p[x] = x; }
inline int find_set( int x ){ return ( p[x] == x )? x : ( p[x] = find_set(p[x]) ); }
void merge( int x, int y ){
	if (x != y){
		p[y] = x;
		cmp--;
	}
	else {
		ok = false;
	}
}

int main(){

	int N,M;
	int runs = 0;
	int u,v;

	while ( scanf("%d",&N) && N ){
		runs++;
		scanf("%d",&M);
		if ( M != (N - 1) ){
			ok = false;
		}

		cmp = N;
		fill( deg , deg + N, 0 );
		for ( int i=0; i < N; ++i ){
			make_set(i);
			for ( int j=0; j < N; ++j )
				G[i][j] = 0;
		}
	
		ok = true;

		for ( int i=0; i < M; ++i ){
			scanf("%d %d",&u,&v);
			u--,v--;
			if ( u==v ){ ok = false; }
			G[u][v]++;
			G[v][u]++;
			if ( G[u][v] > 1 ){ ok = false; } 
			deg[u]++;
			deg[v]++;
			merge( find_set(u) , find_set(v) );
		}
		
		if ( cmp != 1 ){ ok = false; }
		
		int cnt;

		if ( ok ){
		
			for ( u=0; u < N && ok ; ++u ){
				if ( deg[u] > 1 ){
					cnt = 0;
					for ( v = 0; v < N; ++v ){
						
						if ( v != u && G[u][v] ){
							
							if ( deg[v] > 1 ) cnt++;

						}
					
					}
					if ( cnt > 2 ){ ok = false; }
				}
			}
		}

		if ( !ok ) printf("Graph %d is not a caterpillar.\n",runs); 
		else printf("Graph %d is a caterpillar.\n",runs);	
	}


	return 0;
}


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
const int MAXQ = 10005;
int G[MAXN*MAXN] = {0};
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};
int res[MAXQ];
int N, M;
int X1[MAXQ];
int X2[MAXQ];
int Y1[MAXQ];
int Y2[MAXQ];
int ncomp;
int p[MAXN*MAXN];

inline int find_set( const int &x ){
	return ( p[x] == x )? x:( p[x] = find_set(p[x]) );
}

inline bool valid( const int &x, const int &y ){
	return x >= 0 && x < N && y >= 0 && y < M; 
}

void union_set( const int &x, const int &y ){
	if ( x != y ){
		p[y] = x;
		ncomp--;
	}
}

int main(){
	int x, y;
	int nx, ny;
	int Q;
	int used;
	scanf("%d %d %d", &N, &M, &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d %d %d", X1+i, Y1+i, X2+i, Y2+i);
		X1[i]--, X2[i]--, Y1[i]--, Y2[i]--;
		for ( x = X1[i]; x <= X2[i]; ++x )
			for ( y = Y1[i]; y <= Y2[i]; ++y )
				G[x*M + y]++;
	}
	// union find init
	for ( int i=0; i < N*M; ++i ) p[i] = i;
	ncomp = N * M;
	used = 0;
	// find final state of components
	for ( x=0; x < N; ++x )
		for ( y=0; y < M; ++y )
			if ( !G[x*M + y] ){
				for ( int k=0; k < 4; ++k ){
					nx = x + dx[k], ny = y + dy[k];
					if ( valid(nx, ny) && !G[nx*M + ny] )
						union_set( find_set( x*M + y ) , find_set( nx*M + ny ) );
				}
			}
			else {
				used++;
			}
	// undo each change backwards
	for ( int i=Q-1; i >= 0; --i ){
		res[i] = ncomp - used;
		if ( i > 0 ){
			x = X1[i], y = Y1[i];
			for ( x = X1[i]; x <= X2[i]; ++x )
				for ( y = Y1[i]; y <= Y2[i]; ++y ){
					G[x*M + y]--;
					if ( G[x*M + y] == 0 ){
						used--;
						for ( int k=0; k < 4; ++k ){
							nx = x + dx[k], ny = y + dy[k];
							if ( valid(nx, ny) && !G[nx*M + ny] )
								union_set( find_set( x*M + y ) , find_set( nx*M + ny ) );
						}
					}
				}
		}
	}
	for ( int i=0; i < Q; ++i ) printf("%d\n", res[i]);
	return 0;
}


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
#include <climits>

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
const int MAXE = 1000;
int R[30];
int H[30];
int d[30];
int res[30];
// Edges
int nxt[MAXE];
int to[MAXE];
int from[MAXE];
int head[30];
int w[MAXE];
int e;

bool bellman_ford(){
	fill( d, d + 25, 0 );
	int u, v;
	for ( int i=0; i < 23; ++i ){
		for ( int j=0; j < e; ++j ){
			u = from[j], v = to[j];
			if ( d[v] > (d[u] + w[j]) ) d[v] = d[u] + w[j];
		}
	}
	for ( int j=0; j < e; ++j ){
		u = from[j], v = to[j];
		if ( d[v] > (d[u] + w[j]) ) return false; //contains negative cycle
	}
	return true;
}
 
void add_edge( int u, int v, int c ){
	from[e] = u; to[e] = v; w[e] = c; nxt[e] = head[u]; head[u] = e++;
}

void build( int M ){
	fill( head, head + 25, -1 );
	e = 0;
	// S_i - S_{i-1} >= 0 => S_{i-1} - S_i <= 0
	for ( int i=1; i < 24; ++i ){
		add_edge( i, i-1, 0 );
	}
	add_edge( 0, 24, 0 );
	//  S_i - S_{i-1} <= H[i]
	for ( int i=1; i < 24; ++i ) add_edge( i-1, i, H[i] );
	add_edge( 24, 0, H[0] );
	// S_i - S_{i-8} >= R(i) => S_{i-8} - S_i <= -R(i)
	for ( int i=8; i < 24; ++i ) add_edge( i, i-8, -R[i] );
	// S_i - S_{16 + i} >= R(i) - M => S_{16+i} - S_i <= M - R(i)
	for ( int i=0; i <= 7; ++i ) add_edge( i , 16+i, -R[i] + M );
	add_edge( 23, 24, -M );
}

int main(){
	int t, runs, N;
	scanf("%d", &runs);
	while ( runs-- ){
		for ( int i=0; i < 24; ++i ){ 
			scanf("%d", R+i);
			H[i] = 0;
		}
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d", &t);
			H[t]++;
		}
		build( 0 );
		if ( bellman_ford() ){ 
			puts("0");
			continue;
		}
		build( N );
		if ( bellman_ford() ){
			int r = N; // r is solution to the problem
			int l = 0; // l is not solution to the problem
			int m;
			while ( r - l > 1 ){
				m = ( l + r ) >> 1; 
				build(m);
				if ( bellman_ford() ){
					r = m;
				}
				else {
					l = m;
				}
			}
			printf("%d\n", r);
		}
		else {
			puts("No Solution");
		}
	}
	return 0;
}


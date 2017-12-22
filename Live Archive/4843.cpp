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

const int MAXA = 5005;
int seg[MAXA*4];

void build( int node, int L, int R ){
	seg[node] = 0;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	build( node << 1, L , M );
	build( (node<<1)|1, M + 1, R );
}

void update( int node, int L, int R, int p ){
	seg[node]++;
	if ( L == R ) return;
	int M = (L + R) >> 1;
	if ( p <= M ) update( node<<1, L, M, p );
	else update( (node<<1)|1, M + 1, R, p );
}

int query( int node, int L, int R, int l, int r ){
	if ( L==l && R==r ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return query(node<<1, L, M, l, M) + query((node<<1)|1, M+1, R, M+1, r);
}

int main(){
	int x, N;
	int runs;
	int res;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		res = 0;
		build( 1, 1, 5000 );
		for ( int i=0; i < N; ++i ){
			scanf("%d", &x);
			if ( i ){
				res += query(1, 1, 5000, 1, x);
			}
			update( 1, 1, 5000, x );
		}
		printf("%d\n", res);
	}
	return 0;
}


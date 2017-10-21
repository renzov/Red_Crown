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

const int MAXL = 100010;

int B, P, L, N;
long long seg[4*MAXL];
long long pot[MAXL];

void build( int node, int l, int r ){
	seg[node] = 0;
	if ( l == r ) return;
	int m = ( l + r ) >> 1;
	build( node<<1, l, m );
	build( (node<<1)|1, m + 1, r );
}

void update( int node, int l, int r, int p, int v ){
	if ( l == r ){
		seg[node] = ( 1LL * v * pot[l] ) % P;
		return;
	}
	int m = ( l + r ) >> 1;
	if ( p > m ) update( (node << 1) | 1, m + 1, r , p,  v );
	else update( node << 1, l, m, p, v );
	// Update node value
	seg[node] = ( seg[node<<1] + seg[(node<<1)|1] ) % P;
}

long long query( int node, int l, int r, int a, int b ){
	if ( l == a && r == b ) return seg[node];
	int m = ( l + r ) >> 1;
	if ( b <= m ) return query( node << 1, l, m, a, b );
	if ( a > m ) return query( (node << 1) | 1, m + 1, r, a, b );

	return ( query( node << 1, l, m, a, m ) + 
	       query( (node << 1) | 1, m + 1, r, m + 1, b ) ) % P;
}

long long fpow( const long long &a, const long long &b ){
	if ( b == 0 ) return 1LL;
	if ( b == 1 ) return a;
	if ( b & 1 ) return ( a * fpow( a , b - 1 ) ) % P;
	long long t = fpow( a , b >> 1 );
	return (t * t) % P;
}

int main(){
	int l, r, val;
	int a, b;
	long long sum;

	while ( scanf("%d %d %d %d", &B, &P, &L, &N) && B ){
		// Initialize segment tree and array of powers
		build( 1 , 1, L );
		long long p = 1;
		for ( int i=L; i >= 1; --i ){
			pot[i] = p;
			p *= B;
			p %= P;
		}
		// Process the queries 
		char opt;
		for ( int i=0; i < N; ++i ){
			scanf(" %c", &opt);
			if ( opt == 'E' ){
				scanf("%d %d", &l, &val);
				update( 1 , 1, L, l, val );
			}
			else {
				scanf("%d %d", &a, &b);
				sum = query( 1, 1, L, a, b );
				sum *= fpow( pot[b], P  - 2 );
				sum %= P;
				printf("%lld\n", sum);
			}
		}
		puts("-");
	}
	return 0;
}


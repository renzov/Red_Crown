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

const int MAXN = 200005;
int N, Q;
long long A[MAXN];
long long seg[4*MAXN];

void build( int node, int L, int R ){
	if ( L==R ){
		seg[node] = A[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( node<<1, L, M );
	build( (node<<1)|1, M+1, R );
	seg[node] = min( seg[node<<1], seg[(node<<1)|1] );
}

int query( int node, int L, int R, int l, int r, long long v ){
	if ( seg[node] > v ) return -1;
	if ( L==R ) return L;
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r, v );
	if ( l > M ) return query( (node<<1)|1, M + 1, R, l, r, v );
	int r1 = query( node<<1, L, M, l, M, v );
	if ( r1 != -1 ) return r1;
	return query( (node<<1)|1, M+1, R, M+1, r, v );
}

int main(){
	int l, r, idx;
	long long v;
	scanf("%d %d", &N, &Q);
	for ( int i=0; i < N; ++i ) scanf("%I64d", A+i);

	build( 1, 0, N - 1 );

	for ( int i=0; i < Q; ++i ){
		scanf("%I64d %d %d", &v, &l, &r);
		l--, r--;
		do {
			idx = query( 1, 0, N-1, l, r, v );	
			if ( idx == -1 ) break;
			v %= A[idx];
			l = idx + 1;
		}
		while ( v > 0 && l <= r );
		printf("%I64d\n", v);
	}
	return 0;
}


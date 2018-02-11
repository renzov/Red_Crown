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

const int MAXN = 1000005;
int seg[4*MAXN] = {0};

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	seg[node] += v;
	if ( L==R ) return;
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( node<<1, L, M, p, v );
	else update((node<<1)|1, M+1, R, p, v);
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if (  l==L && r==R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return query(node<<1, L, M, l, M ) + 
			query( (node<<1)|1, M+1, R, M+1, r );
}

int main(){
	int N;
	int Q;
	int l, r, x;
	scanf("%d", &N);
	for ( int i=0; i < N; i++ ){
		scanf("%d", &x);
		update( 1, 0, N-1, i, x );
	}
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &l, &r);
		printf("%d\n", query(1, 0, N-1, l, r));
	}
	return 0;
}


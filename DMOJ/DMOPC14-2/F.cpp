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

const int MAXN = 100005;
long long seg[4*MAXN] = {0};
pii B[MAXN];
pii V[MAXN];
int H[MAXN];
int ord[MAXN];
long long res[MAXN];

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	seg[node] += v;
	if ( L==R ) return;
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( node<<1, L, M, p, v );
	else update((node<<1)|1, M+1, R, p, v);
}

long long query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if (  l==L && r==R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return query(node<<1, L, M, l, M ) + 
			query( (node<<1)|1, M+1, R, M+1, r );
}

bool cmp( const int &i, const int &j ){
	return H[i] < H[j];
}

int main(){
	int N;
	int Q;
	int l, r, x, q;
	scanf("%d", &N);
	for ( int i=0; i < N; i++ ){
		scanf("%d", &x);
		V[i] = pii( x, i );
		update( 1, 0, N-1, i, x );
	}
	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%d %d %d", &l , &r, &q);
		B[i] = pii(l, r);
		H[i] = q;
		ord[i] = i;
	}

	sort( ord, ord + Q, cmp );
	sort( V, V + N );

	int idx;
	int j = 0; 
	for ( int i=0; i < Q; ++i ){
		idx = ord[i];
		q = H[ idx ];
		while ( j < N && V[j].first < q ){
			update( 1, 0, N - 1, V[j].second, -V[j].first );
			j++;
		}
		res[ idx ] = query( 1, 0, N - 1, B[idx].first, B[idx].second );
	} 
	for ( int i=0; i < Q; ++i ) printf("%lld\n", res[i]);
	return 0;
}


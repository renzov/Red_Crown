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
int A[MAXN];
int S[MAXN] = {0};
int seg[4*MAXN];

void build( int node, int L, int R ){
	if ( L==R ){
		seg[node] = S[L];
		return;
	}
	int M = ( L + R ) >> 1;
	build( node<<1, L, M );
	build( (node<<1)|1, M + 1, R );
	seg[node] = max( seg[node<<1], seg[(node<<1)|1] );
}

int query( int node, int L, int R, int l, int r ){
	if ( L==l && R==r ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node<<1, L, M, l, r );
	if ( l > M ) return query( (node<<1)|1, M+1, R, l, r );
	return max( query(node<<1, L, M, l, M), query((node<<1)|1, M+1, R, M+1, r) );
}

int main(){
	int N, M;
	int k, len;
	int L, R;
	int res;
	int l, r, m;

	scanf("%d %d", &N, &M);
	for ( int i=1; i <= N; ++i ) scanf("%d", A+i);

	map<int,int> idx; // index of last ocurrence 
	// precompute for each i, the length of longest sequence starting in i
	for ( int i=N; i >= 1; --i ){
		k = idx[ A[i] ];
		len = (k == 0)? (N - i + 1):(k - i);
		S[ i ] = min( S[i + 1] + 1, len );
		idx[ A[i] ] = i;
	}

	build( 1, 1, N );

	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &L, &R);
		L++, R++;
		// in case sequence starting in L covers interval
		if ( S[L] >= (R - L + 1) ){
			printf("%d\n", R - L + 1);
		}
		else {
			l = L, r = R;
			while ( r - l > 1 ){
				m = ( l + r ) >> 1;
				if ( S[m] >= (R - m  + 1) ) r = m;
				else l = m;
			}
			res = max( query(1, 1, N, L, r - 1) , R - r + 1 );
			printf("%d\n", res);
		}
	}
	return 0;
}


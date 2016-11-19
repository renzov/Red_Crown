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

const int MAXN = 100005;
pair<int,pii> P[MAXN];
int seg[4*MAXN];

void build(int node, int l, int r){
	seg[node] = INT_MAX;
	if (l==r) return;
	int m = ( l + r ) >> 1;
	build( node<<1, l , m );
	build( (node<<1)|1, m+1, r );
}

void update( int node, int L, int R, int pos, int val ){
	seg[node] = min( seg[node], val );
	if ( L==R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M ) update( node << 1 , L, M, pos, val );
	else update( (node << 1)|1, M + 1, R, pos, val );
}

int query( int node, int L, int R, int l, int r ){
	if ( l==L && r==R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( node << 1, L, M, l, r );
	if ( l > M ) return query( (node << 1)|1, M+1, R, l, r );
	return min( query(node<<1, L, M, l, M), query((node<<1)|1, M+1, R, M+1, r) );
}

int main(){
	int n;
	int runs;
	int res;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &n);
		build( 1, 1 , n );
		for ( int i=0;  i < n; ++i )
			scanf("%d %d %d", &P[i].first, &P[i].second.first, &P[i].second.second);
		sort( P , P + n );
		res = 0;
		for ( int i=0; i < n; ++i ){
			if ( query( 1 , 1 , n , 1, P[i].second.first ) > P[i].second.second ){
				update( 1 , 1 , n, P[i].second.first, P[i].second.second );
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}


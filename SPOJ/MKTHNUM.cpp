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

int a[MAXN];
int b[MAXN];
int ord[MAXN];
int rev[MAXN];

struct node {
	int L, R, sum;
	node( int l, int r, int S ){
		L = l, R = r, sum = S;
	}
	node(){}
};

node MEM[ MAXN * 20 ];
int root[ MAXN ];
int cur_node;

bool cmp(const int &i, const int &j){
	return ord[i] < ord[j];
}

int insert( const int &vertex, int L , int R, int p ){
	if ( L <= p && p <= R  ){
		if ( L == R ){
			MEM[cur_node] = node(0,0,1);
			return cur_node++;
		}
		int res = cur_node++;
		int M = ( L + R ) >> 1;
		MEM[res].L = insert( MEM[vertex].L , L , M , p );
		MEM[res].R = insert( MEM[vertex].R , M + 1 , R , p );
		MEM[res].sum = MEM[vertex].sum + 1;
		return res;
	}
	return vertex;
}

int query( const int &v , const int &u, int L, int R, int k  ){

	if ( L==R ) return L;

	int M = (L+R) >> 1;
	int s = MEM[ MEM[v].L ].sum - MEM[ MEM[u].L ].sum;
	if ( k <= s )
		return query( MEM[v].L , MEM[u].L , L , M , k );
	else 
		return query( MEM[v].R , MEM[u].R , M + 1, R , k - s );
}

int main(){

	int N, M;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N ; i++ ) scanf("%d", a+i), ord[i] = i;
	sort( ord, ord, cmp );
	for ( int i=0; i < N ; ++i ) b[i] = a[ ord[i] ], rev[ord[i]] = i;
	// Set NULL NODE
	MEM[0].sum = MEM[0].L = MEM[0].R = 0;
	cur_node = 1;
	
	for ( int i=0; i < N ; ++i ){
		root[ i ] = insert( (i)? root[i-1]:0 , 0, N-1, rev[i] );	
	}

	int u, v, k;
	int res;

	while ( M-- ){
		scanf("%d %d %d", &u, &v, &k);
		u--,v--;
		res = query( root[v] , (u)? root[u-1]:0 , 0 , N-1 , k );
		printf("%d\n", b[res]);
	}

	return 0;
}


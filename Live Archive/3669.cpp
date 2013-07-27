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

const int MAX = 10005;

int c[1005];
char s[ MAX ];

int seg_tree[ 4 * MAX ];

void build_tree( int node , int L , int R ){
	if ( L==R ){
		seg_tree[ node ] = 1 << (s[L-1]-'a');
		return;
	}

	int M = ( L + R ) >> 1;

	build_tree( node << 1 , L , M );
	build_tree( (node << 1) | 1 , M + 1 , R );

	seg_tree[ node ] = seg_tree[ node << 1 ] | seg_tree[ (node << 1) | 1 ]; 
}

int query( int node , int L , int R , int l , int r ){
	if ( L == l && R == r ){
		return seg_tree[ node ];
	}

	int M = ( L + R ) >> 1;
	
	if ( r <= M )
		return query( node << 1 , L , M , l , r );
	if ( l > M )
		return query( (node << 1) | 1 , M + 1 , R , l , r );

	int left = query( node << 1 , L , M , l , M );
	int right = query( (node << 1) | 1 , M + 1 , R , M + 1 , r );

	return (left | right);
}

int main(){
	int runs;
	int K;
	int N;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d",&K);	
		for ( int i=0; i < K; ++i )
			scanf("%d",c+i);
		
		scanf("%s",s);
		
		N = strlen( s );
		
		build_tree( 1 , 1 , N );

		set< pii > I;
		set<pii>::iterator f;
		int l , r;
		int sl,sr;
		I.insert( make_pair( N , 1 ) );
	
		int res = 0;

		for ( int i=0; i < K; ++i ){
			f = I.lower_bound( make_pair( c[i] , c[i] ) );

			if ( f == I.end() || (c[i] == f->first) ){ continue; }

			r = f->first; l = f->second;
			
			I.erase(f);
			
			sl = query( 1 , 1 , N , l , c[i] );
			
			sr = query( 1,  1 , N , c[i] + 1 , r );
			
			res += __builtin_popcount( sl ^ sr );

			I.insert( make_pair( c[i] , l ) );
			I.insert( make_pair( r , c[i] + 1 ) );
		}

		printf("%d\n",res);
	}

	return 0;
}


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

const int MAXN = 10005;

int seg[ MAXN << 2 ];

void build( int node, int L, int R ){
	if ( L==R ){
		seg[node] = 1;
		//printf("[%d, %d] -> %d\n", L, R, seg[node]);
		return;
	}
	int M = ( L + R ) >> 1;
	build( node << 1 , L , M );
	build( (node << 1) + 1 , M + 1 , R );
	seg[ node ] = seg[ node << 1 ] + seg[ (node << 1) + 1 ];
	//printf("[%d, %d] -> %d\n", L, R, seg[node]);
}

int update( int node, int L, int R, int val ){
	//printf("[%d, %d] - sum = %d - val = %d\n", L,R, seg[node], val);
	if ( L == R ){ 
		seg[node] = 0;
		return L;
	}
	int M = ( L + R ) >> 1;
	int res;
	if ( seg[ node << 1 ] >= val ){
		res = update( node << 1 , L , M, val );
		seg[node] = seg[node << 1] + seg[ (node << 1) + 1 ];
		return res;
	}
	else {
		res = update( (node << 1) + 1 , M + 1, R, val - seg[ node << 1 ] );
		seg[node] = seg[node << 1] + seg[ (node << 1) + 1 ];
		return res;	
	}
}

int main(){
	int N,K,M;
	int C;
	int idx, last;
	while ( scanf("%d %d %d", &N, &K, &M) && N ){
		build( 1 , 0 , N - 1 );
		update( 1 , 0 , N - 1, M );
		C = N-1;
		last = M-1;
		while ( C > 1 ){
			last = (K + last)%C;
			if ( !last ) last = C;
			//printf("last = %d\n", last);
			update( 1, 0 , N-1, last );
			last--, C--;
		}
		printf("%d\n", update(1, 0, N-1, 1) + 1 );
	}
	return 0;
}


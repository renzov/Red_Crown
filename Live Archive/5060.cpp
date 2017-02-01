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

int a[ (1 << 15) + 5 ];
int S[ (1 << 17) + 5 ];
int R[ (1 << 17) + 5 ];
int N,K;

void process( int n , int l, int r ){
	
	if ( l == r ){
		S[ n ] = a[ l ];
		R[ n ] = l;
		return;
	}

	int M = ( l + r ) >> 1;
	
	process( n<<1 , l , M );
	process( (n<<1) | 1 , M + 1 , r );

	if ( S[ n << 1 ] >= S[ (n << 1) | 1 ] ){
		S[ n ] = min( S[ n << 1 ] - S[ (n << 1) | 1 ] + K , a[ R[ (n<<1) ] ] );
		R[ n ] = R[ n << 1 ];
	}
	else {
		S[ n ] = min( S[ (n<<1) | 1 ] - S[n<<1] + K , a[ R[ (n<<1) | 1 ] ] );
		R[ n ] = R[ (n<<1) | 1 ]; 
	}
}

int main(){

	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		
		scanf("%d %d",&N,&K);
		
		for ( int i=1; i <= (1<<N) ; ++i )
			scanf("%d",a+i);

		process( 1 , 1 , (1<<N) );
		stack<int> s;
		int n,l,r,m;
		n = 1;
		l = 1; r = (1<<N);
		while ( l != r ){
			m = ( l + r ) >> 1;
			if ( R[n<<1] != R[n] ){
				s.push( R[n<<1] );
				l = m + 1;
				n = (n << 1) | 1;
			}
			else {
				s.push( R[(n<<1)|1] );
				r = m;
				n = n << 1;
			}
		}
		
		printf("%d\n",R[1]);
		int cnt = 0;
		while ( !s.empty() ){
			if (cnt) putchar(' ');
			printf("%d",s.top());
			s.pop(); cnt++;
		}
		puts("");
	}
	return 0;
}


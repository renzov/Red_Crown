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

const int MAX = 1000005;

int a[MAX];
int b[MAX];

inline int Mx( int x, int y ){ return (x < y)? y:x; }

int main(){
	int n;
	int x;
	while ( scanf("%d",&n) != EOF ){
		scanf("%d",&a[0]);
		if ( n == 1 ){ printf("%d\n",a[0]); continue; }
		b[0] = 0;
		scanf("%d",&b[1]);
		a[ 1 ] = Mx( a[0] , b[1] );
		if ( n == 2 ){ printf("%d\n",a[1]); continue; }
		for ( int i=2; i < (n-1); ++i ){
			scanf("%d",&x);
			a[i] = Mx( a[i - 1] , a[i-2] + x );
			b[i] = Mx( b[ i - 1 ] , b[ i - 2 ] + x );
		}
		scanf("%d",&x);
		b[n-1] = Mx( b[n-2] , b[n-3] + x );
		printf("%d\n", Mx( b[n-1] , a[n-2] ));
	}
	return 0;
}


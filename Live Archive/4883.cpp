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

int f( int P , int L ){
	if ( L < P ) return 0;
	return (L / P) + 1;
}

int main(){
	int N;
	int P;
	int S;
	int r1,r2,r3;
	while ( scanf("%d",&N) && N ){
		r1 = r2 = r3 = INT_MAX;
		S = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%d",&P);
			S += P;
			r1 = min( r1 , f(P,50) );
			r2 = min( r2 , f(P,60) );
			r3 = min( r3 , f(P,70) );
		}
		if ( 2*S > 50 ) r1 = 0;
		if ( 2*S > 60 ) r2 = 0;
		if ( 2*S > 70 ) r3 = 0;
		printf("%d %d %d\n",r1,r2,r3);
	}
	return 0;
}

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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 50005;
point P[MAXN];
long long S[MAXN];

long long area2( const point &a, const point &b, const point &c ){
	return llabs( 1LL*(b.X-a.X)*(c.Y-a.Y) - 1LL*(c.X - a.X)*(b.Y - a.Y) );
}

int main(){
	int N, Q;
	bool first = true;
	while ( scanf("%d %d", &N, &Q) && N ){
		for ( int i=0; i < N; ++i )
			scanf("%d %d", &P[i].X, &P[i].Y);
		
		S[0] = 0;
		S[1] = 0;
		for ( int i=2; i < N; ++i ){
			S[i] = area2( P[0], P[i-1], P[i] );
			S[i] += S[i-1];
		}

		// Not mentioned in the description	
		if ( first ) first = false;
		else puts("");
		///

		int a, b;
		long long A, B;
		for ( int i=0; i < Q; ++i ){
			scanf("%d %d", &a, &b);
			A = S[a] + ( S[N-1] - S[b] ) + area2( P[0], P[a], P[b] );
			B = S[N-1] - A;
			A = min( A, B );
			if ( A & 1 ) printf("%lld.5\n", A >> 1);
			else printf("%lld.0\n", A >> 1 );
		}
	}
	return 0;
}


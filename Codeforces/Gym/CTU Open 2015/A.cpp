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
typedef pair< long , long > point;

const int MAXN = 100005;
int N;
int T[MAXN];
int V[MAXN];
point P[MAXN];
int L[MAXN];
int U[MAXN];

void convex_hull(){
	// Andrew "Monotone Chain" Alg
	sort( P, P + N );
	// Lower hull of P, corresponds to upper hull of lines
	U[ 0 ] = 0;
	U[ 1 ] = 1;
	int s1 = 2;
	for ( int i=2; i < N; ++i ){
		while ( s1 > 1 && cross( P[ U[s1-2] ], P[ U[s1-1] ] , P[i] ) <= 0 )
			s1--;
		U[s1++] = i;
	}
	// upper hull of P, corresponds to lower hull of lines
	L[ 0 ] = N - 1;
	L[ 1 ] = N - 2;
	for ( int i=N-3; i >= 0; --i ){
		while ( s2 > 1 && cross( P[ L[s2-2] ], P[ L[ s2-1 ] ], P[i] ) >= 0 )
			s2--;
		L[s2++] = i;
	}
}

int main(){
	int tmax = -1;
	while ( scanf("%d", &N) && N ){
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", T+i, V+i);
			if ( tmax < T[i] ) tmax = T[i];
		}
		for ( int i=0; i < N; ++i ) // line ax + b maps to point (a, -b)
			P[i] = point( V[i] , 1LL*V[i]*(T[i] - tmax) );
		convex_hull();
	}
	return 0;
}


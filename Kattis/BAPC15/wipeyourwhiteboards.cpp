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

long long extgcd( long long A, long long B, long long &X, long long &Y ){
	if (B == 0) { X = 1, Y = 0; return A; }
	long long g = extgcd(B, A%B, X, Y);
	swap(X, Y), Y -= (A/B)*X;
	return g;
}

long long roundup(const long long &X,const long long &Y){
	return (X < 0)? (X/Y):( X + Y - 1 )/Y;
}

int main(){
	int runs;
	scanf("%d", &runs);

	long long R, S, Q;
	long long A, B;
	long long G;
	while ( runs-- ){
		scanf("%lld %lld %lld", &R, &S, &Q);
		G = extgcd(R, -S, A, B); 
		B = -B;
		// We have that : A * R + B * S = G.
		A *= Q/G, B *= Q/G;
		// We have that : A * R + B * S = Q.
		// All the solutions have the form: (A + K*(-S/G), B + K*R/G)
		// if A + K*(-S/G) >= 1, then K >= (1-A)/(-S/G)
		// if B + K*(R/G) >= 1, then K >= (1-B)/(R/G)
		long long K = max(roundup(1-A,-S/G),roundup(1-B,R/G));
		printf("%lld %lld\n", A + K*(-S/G), B + K*R/G );
	}
	return 0;
}


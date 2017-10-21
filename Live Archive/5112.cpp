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

const long long MOD = 1000000007LL;
long long a[20];
long long S[20];
long long M[ 20 ][ 20 ];
long long C[ 20 ][ 20 ];
int R, K, N;
long long X[ 20 ];

void initialize(){
	for ( int i=0; i < R + K; ++i )
		fill( M[i], M[i] + R + K, 0 );
	/* first row */
	for ( int i=1; i <= R; ++i )
		M[0][i - 1] = a[i];
	/* Next R - 1 rows */
	for ( int i=1; i < R; ++i )
		M[i][ i - 1 ] = 1LL;
	/* the R + 1 row */
	M[ R ][ R - 1 ] = 1LL, M[R][R + K  - 1] = 1LL;
	for ( int i=1; i < K; ++i ){
		M[ R + i ][ R + i - 1 ] = 1LL;
	}
	// Initialize the base vector
	for ( int i=1; i <= R; ++i )
		X[i - 1] = S[R + K  - i];
	
	for ( int i=R; i < R + K; ++i ) 
		X[i] = 0;

}

void fast_pow( long long m[20][20], long long p, long long c[20][20] ){
	
	if ( p == 1 ){
		for ( int i=0; i < R+K; ++i )
			for ( int j=0; j < R+K; ++j )
				c[i][j] = m[i][j];
		return;
	}
	
	if ( p == 0 ){
		for ( int i=0; i < R+K; ++i )
			for ( int j=0; j < R+K; ++j )
				c[i][j] = ( i == j )? 1:0;
		return;
	}

	long long t[20][20];
	if ( p & 1 ){
		fast_pow( m, p - 1, t );
		for ( int i=0; i < R+K; ++i )
			for ( int j=0; j < R+K; ++j ){
				c[i][j] = 0;
				for ( int k=0; k < R+K; ++k ){
					c[i][j] += m[i][k] * t[k][j];
					c[i][j] %= MOD;	
				}
			}
	}
	else {
		fast_pow( m, p >> 1, t );
		for ( int i=0; i < R+K; ++i )
			for ( int j=0; j < R+K; ++j ){
				c[i][j] = 0;
				for ( int k=0; k < R+K; ++k ){
					c[i][j] += t[i][k] * t[k][j];
					c[i][j] %= MOD;
				}
			}
	}
}

int main(){

	int runs;
	scanf("%d", &runs);

	a[0] = S[0] = 0;
	while ( runs-- ){
		scanf("%d %d %d", &N, &R, &K);
		for ( int i=1; i <= R; ++i ) scanf("%lld", S + i);
		for ( int i=1; i <= R; ++i ) scanf("%lld", a + i);
		/* Calculate the values until S(R  + k - 1) */
		for ( int i=R+1; i < R + K; ++i ){
			S[ i ] = 0;
			for ( int j=1; j <= R; ++j ){
				S[i] += a[j] * S[ i  - j ];
				S[i] %= MOD;
			}
		}
		/* Create the transition matrix and vector */
		initialize();
		fast_pow( M , 1LL*(N - 1)*K + 1, C );
		long long res = 0;
		for ( int i=0; i < R+K; ++i ){
			res += X[i] * C[R][i];
			res %= MOD;
		}
		printf("%lld\n", res);
	}
	return 0;
}


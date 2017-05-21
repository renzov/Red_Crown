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

const int MOD = 10007;
int base[] = { 4, 1, 2, 1 };
int H[4][4] = { {2,2,2,2}, {1,0,0,0}, {0,0,2,2}, {0,0,1,0} };

// f( x ) = 2f(x-1) + 2f(x-2)
// g( x ) = 2g(x-1) + 2g(x-2) + f(x)
// res = g(N)

void fast_exp( int A[4][4], int n  ){
	if ( n == 1 ){
		for ( int i=0; i < 4; ++i ) for ( int j=0; j < 4; ++j ) 
			A[i][j] = H[i][j];
		return;
	}
	int T[4][4];
	if ( n & 1 ){
		fast_exp( T, n - 1 );
		for ( int i=0; i < 4; ++i )
			for ( int j=0; j < 4; ++j ){
				A[i][j] = 0;
				for ( int k=0; k < 4; ++k ){
					A[i][j] += T[i][k] * H[k][j];
					A[i][j] %= MOD;
				}
			}
	}
	else {
		fast_exp( T, n >> 1 );
		for ( int i=0; i < 4; ++i )
			for ( int j=0; j < 4; ++j ){
				A[i][j] = 0;
				for ( int k=0; k < 4; ++k ){
					A[i][j] += T[i][k] * T[k][j];
					A[i][j] %= MOD;
				}
			}
	}
}

int main(){
	int N, res;
	int A[4][4];

	while ( scanf("%d", &N) && N >= 0 ){
		if ( N==0 ) puts("1");
		else if ( N == 1 ) puts("4");
		else {
			fast_exp( A, N - 1 );
			res = 0;
			for ( int i=0; i < 4; ++i ){ 
				res += A[0][i] * base[i];
				res %= MOD;
			}
			printf("%d\n", res);
		}
	}
	return 0;
}


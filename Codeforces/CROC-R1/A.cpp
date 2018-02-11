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

char A[1000005];
char B[1000005];
int prefA[1000005];
int prefB[1000005];

int cmp( const char &a, const char &b ){
	if ( a == b ) return 0;
	if ( a == 'P' ) return ( b == 'R' )? 1:-1;
	if ( a == 'R' ) return ( b == 'S' )? 1:-1;
	return ( b == 'P' )?  1:-1;
}

int main(){
	int N, M, K, T;
	scanf("%d", &N);
	scanf("%s %s", A, B);
	M = strlen(A), K = strlen(B);

	T = M * K / __gcd( M, K );
	for ( int i=M; i < T; ++i )
		A[i] = A[i - M];
	for ( int i=K; i < T; ++i )
		B[i] = B[i - K];

	A[T] = B[T] = '\0';

	int val = cmp( A[0], B[0] );
	prefA[0] = 0;
	prefB[0] = 0;
	
	if ( val > 0 ) prefB[0]++;
	else if ( val < 0 ) prefA[0]++;

	for ( int i=1; i < T; ++i ){
		val = cmp( A[i], B[i] );
		prefA[i] = prefA[i-1];
		prefB[i] = prefB[i-1];
		if ( val > 0 ) prefB[i]++;
		else if ( val < 0 ) prefA[i]++;
	}

	int d = N / T;
	int resA = d * prefA[T-1];
	int resB = d * prefB[T-1];
	d = N % T;
	if ( d > 0 ){
		resA += prefA[d-1];
		resB += prefB[d-1];
	}
	printf("%d %d\n", resA, resB);
	return 0;
}


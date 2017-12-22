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

const int MAXN = 30005;
int A[MAXN];
int N;

int count_val( const int &T, const int &x ){
	bool first = T < (A[0] * x);
	bool last = T < (A[N-1] * x);
	if ( first == last ) return first? N:0;
	int l = 0; 
 	int r = N - 1;
	int m;
	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if ( first ){
			if ( A[m] * x > T ) l = m;
			else r = m;
		}
		else {
			if ( A[m] * x > T ) r = m;
			else l = m;
		}
	}
	return first? (l + 1):(N - r);
}

int main(){
	int T;
	int idx;
	int num, den;
	int cases = 0;
	while ( scanf("%d %d", &N, &T) && N ){
		for ( int i=0; i  < N; ++i ) scanf("%d", A + i);
		sort( A , A + N );
		num = 0;
		den = N * N;

		for ( int i=0; i < N; ++i )
			num += count_val( T, A[i] );
		
		int g = __gcd( num, den );
		num /= g, den /= g;
		printf("Case %d: %d/%d\n", ++cases, num, den);
	}
	return 0;
}


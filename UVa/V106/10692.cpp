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
#include <cassert>
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
const int LIMIT = 10001;
const int MAXN = 16;
int M, N;
int a[MAXN];
int ex[MAXN];

int fast_exp( int x, int y, int m ){
	int res;
	for ( res = 1; y > 0; y >>= 1 ){
		if ( y & 1 ) res = (res * x) % m;
		x = (x * x) % m;
	}
	return res;
}

void calc_pw(){
	ex[N-1] = a[N-1];
	int base, e;
	for ( int i=N-1; i > 0; --i ){
		if ( ex[i] == INT_MAX ){ 
			ex[i-1] = INT_MAX;
			continue;
		}
		base = 1;
		e = ex[i];
		while ( e-- && base < LIMIT ) base *= a[i-1];
		ex[i-1] = ( base < LIMIT )? base:INT_MAX;
	}
}

int solve( int pos, int mod ){
	if ( mod <= 1 ) return 0;
	if ( ex[pos] < INT_MAX ) return ex[pos] % mod;
	if ( ex[pos + 1] < INT_MAX ) return fast_exp( a[pos], ex[pos + 1], mod );
	// if not we find the cycle
	int base = a[pos];
	int p = fast_exp( base, 2*mod, mod );
	int len = 0;
	for( int q=p; ; ){
		len++;
		q = (q * base) % mod;
		if ( q == p ) break;
	}
	int e = 50000 - (50000 % len); // big multiple of len to ensure inside cycle
	return fast_exp( a[pos], e + solve( pos + 1, len ), mod );
}

int main(){
	char s[10];
	int cases = 0;
	while ( scanf("%s", s) && s[0] != '#' ){
		M = atoi(s);
		assert( M >= 2 && M <= 10000 );
		cases++;
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){ 
			scanf("%d", a+i);
			assert( a[i] >= 1 && a[i] <= 1000 );
		}
		calc_pw();
		printf("Case #%d: %d\n", cases, solve( 0 , M ) );
	}
	return 0;
}


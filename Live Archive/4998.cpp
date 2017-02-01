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

const long long MOD = 1000000000000LL;
const long long HLF_MOD = 1000000LL;
long long B;
long long A;

long long mul(long long a, long long b) {
	long long ah = a / HLF_MOD, al = a % HLF_MOD, bh = b / HLF_MOD, bl = b % HLF_MOD;
	return ((ah * bl + al * bh) * HLF_MOD + al * bl) % MOD;
}

long long fast_exp( long long a, long long b ){
	long long c = 1;
	while ( b > 0 ){
		if ( b&1 ){
			c = mul(a,c);
		}
		a = mul(a,a);
		b >>= 1;
	}
	return c;
}

bool test( long long b, long long m ){
	long long nxt = m * 10;
	if ( fast_exp(A,b % nxt ) % m != b % m ) return false;
	if ( m < MOD ){
		for ( int i=0; i < 10; ++i ){
			if ( test(b, nxt) ) return true;
			b += m;
		}
	}
	else if ( b >= (MOD / 10) ) {
		B = b;
		return true;
	}
	return false;
}


int main(){
	int cases = 0;
	while ( scanf("%lld", &A) && A ){
		cases++;
		for ( int i=0; i < 100; ++i ){
			if ( test( (long long)i , 10 ) ) break;
		}
		printf("Case %d: Public Key = %lld Private Key = %lld\n", cases, A, B);
	}
	return 0;
}


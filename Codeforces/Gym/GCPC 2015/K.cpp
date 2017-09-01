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

int dig[25];
long long N, M;
bool ok;

int T[10] = {0, 1, 2, -1, -1, 5, 9, -1, 8, 6};

long long decomp(){
	long long temp = N;
	int cnt = 0;
	M = 0;
	while ( temp ){
		dig[cnt++] = temp%10;
		temp /= 10;
	}
	ok = true;
	for ( int i=0; i < cnt && ok; ++i ){
		ok &= ( dig[i] != 3 );
		ok &= ( dig[i] != 4 );
		ok &= ( dig[i] != 7 );
		M *= 10;
		M += T[ dig[i] ];
	}
	return M;
}

bool isprime( const long long &X ){
	if ( X == 1 ) return false;
	if ( !(X&1) ) return X == 2;
	for ( long long i=3; i*i <= X; i += 2 ){
		if ( X % i == 0 ) return false;
	}
	return true;
}

int main(){
	scanf("%lld", &N);
	M = decomp();
	if ( ok ){
		if ( isprime( N ) && isprime( M ) ){
			puts("yes");
		}
		else {
			puts("no");
		}
	}
	else {
		puts("no");
	}
	return 0;
}


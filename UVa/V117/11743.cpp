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

int digits( int n ){
	int res = 0;
	while ( n ){
		res += (n%10);
		n /= 10;
	}
	return res;
}

int main(){
	char s[20];
	int runs;

	scanf("%d",&runs);

	while ( runs-- ){
	
		for ( int i=0; i < 4; ++i )
			scanf("%s", s + i*4 );
	
		int sum = 0;
		int val;

		for ( int i=0; i < 16; ++i ){
			val = s[i] - '0';
			if ( i&1 ) sum += val;
			else sum += digits( 2*val );
		}
		if ( sum % 10 ) puts("Invalid");
		else puts("Valid");
	}
	return 0;
}


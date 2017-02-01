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

int main(){


	long long N,L,U;
	long long M;
	while ( scanf("%lld %lld %lld",&N,&L,&U) != EOF ){
		M = 0;
		for ( int i=31; i >= 0; --i ){
			if ( ((M | (1LL<<i)) <= U) && !(N&(1LL<<i)) )
				M |= ( 1LL << i );
			else if ( M < L && ( L & (1LL << i) ) ){
				M |= ( 1LL << i );
			}
		}
		printf("%lld\n",M);	
	}

	return 0;
}


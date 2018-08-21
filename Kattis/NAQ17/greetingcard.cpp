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
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< long long , long long > pii;

// Precomputed values, the only solution to x^2 + y^2 == 2018^2 
int dx[] = {0, 1118, 1680, 2018};
int dy[] = {2018, 1680, 1118, 0};

set<pii> P;

int main(){
	int N;
	long long x, y;

	scanf("%d", &N);
	
	for ( int i=0; i < N; ++i ){
		scanf("%lld %lld", &x, &y);
		P.insert( pii(x,y) );
	}

	int res = 0;
	for ( set<pii>::iterator it=P.begin(); it != P.end() ; it++ ){
		x = it->first, y = it->second;
		for ( int i=0; i < 4; ++i ){
			if ( P.find( pii(x + dx[i], y + dy[i]) ) != P.end() ) res++;
			if ( P.find( pii(x + dx[i], y - dy[i]) ) != P.end() ) res++;
			if ( dx[i] && dy[i] && P.find( pii(x - dx[i], y + dy[i]) ) != P.end() ) res++;
			if ( dx[i] && dy[i] && P.find( pii(x - dx[i], y - dy[i]) ) != P.end() ) res++;
		}
	}
	printf("%d\n", res >> 1);
	return 0;
}


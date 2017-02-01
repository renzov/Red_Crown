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

long double N, p, s, v;
long double sq2 = sqrt( 2.0 );
long double E, L;
long double dem;

long double f( double c ){
	return ( pow( E, c*sq2 ) * dem ) + (1 + 1/c)*L;
}

int main(){

	while ( scanf("%Lf %Lf %Lf %Lf", &N, &p, &s, &v) != EOF ){
		E = log2(N);
		L = s / v;
		dem = N / (1000000000.0 * p);
		long double l = 0.0, r = 1.0;
		while (f(r) < f(r/2)) r *= 2;
		long double m1, m2;
		for ( int i=0; i < 1000; ++i ){
			m1 = (2*l + r ) / 3;
			m2 = ( l + 2*r ) / 3;
			if ( f(m1) > f(m2) ) l = m1;
			else r = m2;
		}
		printf("%Lf %Lf\n", f(l), l);
	}
	return 0;
}


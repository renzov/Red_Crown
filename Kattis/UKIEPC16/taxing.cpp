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

const int MAXB = 24;
const long double INF = 1000000.0L * 222222.0L;
int B;
long double S[MAXB];
long double P[MAXB];
long double tax_e;

long double f( const long double &x ){
	long double temp = x;
	long double tax = 0;
	long double b;

	for ( int i=0; i <= B; ++i ){
		b = min( temp, S[i] );
		tax += (b * P[i])/100.0;
		temp -= S[i];
		if ( temp < 0.0 ) break;
	}
	return tax;
}

long double get_val( const long double &E, const long double &M ){
	long double l = 0;
	long double r = INF;
	long double m;
	
	for ( int i=0; i < 200; ++i ){
		m = ( l + r ) / 2.0;
		if ( (m - f( E + m ) + tax_e ) < M )
			l = m;
		else 
			r = m;
	}
	return r;
}

int main(){
	
	scanf("%d", &B);
	for ( int i=0; i < B; ++i )
		scanf("%Lf %Lf", S+i, P+i);
	
	S[B] = INF;
	scanf("%Lf", P + B);

	int F;
	long double E, M;

	scanf("%d", &F);
	for ( int i=0; i < F; ++i ){
		scanf("%Lf %Lf", &E, &M);
		tax_e = f(E);
		printf("%Lf\n", get_val( E, M ) );
	}	
	return 0;
}


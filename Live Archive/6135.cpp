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

int W, A, D, K;
double P1[16];
double Q1[16];
double P2[16];
double Q2[16];

double f( const double &x, const double &m ){
	double num1 = 0;
	double num2 = 0;
	double den1 = 0;
	double den2 = 0;

	for ( int i=K; i >= 0; --i ){
		num1 = num1*x + P1[i];
		num2 = num2*x + P2[i];
		den1 = den1*x + Q1[i];
		den2 = den2*x + Q2[i];
	}

	double f1 = num1 / den1;
	double f2 = num2 / den2;

	if ( m > f1 ) return 0;
	if ( m > f2 ) return f1 - m;
	return f1 - f2;
}

int main(){

	while ( scanf("%d %d %d %d", &W, &D, &A, &K ) != EOF ){
	
		for ( int i=0; i <= K; ++i ) scanf("%lf", P1 + i);
		for ( int i=0; i <= K; ++i ) scanf("%lf", Q1 + i);
		for ( int i=0; i <= K; ++i ) scanf("%lf", P2 + i);
		for ( int i=0; i <= K; ++i ) scanf("%lf", Q2 + i);

		/* Binary search the answer */
		double l, r, m;
		double area;
		double delta = 1e-3;
		double a;
		l = -D;
		r = 0;

		for ( int i=0; i < 30; ++i ){
			m = ( l + r ) / 2;	
			area = 0;
			a = 0;
			/*  Apply Simpson's rule - using a delta of 0.001, 
				that is, we devide the interval in 1000xW parts  
			*/
			for ( int j=0; j < 1000*W; ++j ){
				area += ( f( a, m ) + 4*f( a + delta/2 , m ) + f( a + delta, m ) ) / 6.0;
				a += delta;
			}
			
			if ( area*delta < A ) 
				r = m;
			else 
				l = m;
		}
		
		printf("%0.5f\n", -l);
	}
	return 0;
}


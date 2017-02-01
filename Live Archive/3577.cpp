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

const int MAX = 5005;



int M[ MAX ];
int pred[ MAX ];

int S[ MAX ];
int ps[ MAX ];

void precalc_mul(){

	int k;

	for ( int i=1; i <= 5000 ; ++i ){
	
		M[ i ] = i;
		pred[ i ] = i;

		for ( int j=2; 2*j <= i ; ++j ){
		
			if ( ( i % j ) == 0 ){
				k = i / j;
				if ( (M[ k ] + M[j] + 2) < M[i] ){
					M[i] = M[k] + M[j] + 2;
					pred[i] = j;
				}
			}
		}
	
	}

}

void precalc_sum(){

	S[ 1 ] = 1; ps[ 1 ] = 1;
	S[ 2 ] = 2; ps[ 2 ] = 2;
	S[ 3 ] = 3;	ps[ 3 ] = 3;
	
	for ( int i=4; i <= 5000 ; ++i ){

		S[ i ] = M[i];
		ps[ i ] = i;
	
		for ( int j=1; j < i; ++j ){
			if ( (S[j] + M[i  - j] + 2) < S[i] ){
				S[i] = S[j] + M[i-j] + 2;
				ps[i] = j;
			}
			if ( (S[i - j] + M[j] + 2) < S[i] ){
				S[i] = S[i-j] + M[j] + 2;
				ps[i] = i - j;
			}
		}
	}
}

void printMul( int x ){
	if ( pred[x] == x ){
		for ( int i=0; i < x; ++i ) putchar('|');
		return;
	}
	int y = x / pred[x];
	printMul(pred[x]);
	putchar('x');
	printMul(y);
}

void printSum( int x ){
	if ( x <= 0 ) return;
	if ( ps[x] == x ){
		printMul(x);
	}
	else {
		int y = ps[x];
		printSum(y);
		putchar('+');
		printMul(x - y);
	}

}

int main(){
	int n;	
	precalc_mul();
	precalc_sum();
	
	while ( scanf("%d",&n) != EOF ){
		printf("%d toothpicks: ",S[n]);
		printSum( n );
		printf("=%d\n",n);
	}

	return 0;
}


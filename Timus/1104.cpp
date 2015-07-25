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

int res[50] = {0};

int main(){
	char c;
	int val;
	int maxval = 2;

	while ( isdigit( c=getchar() ) || isupper(c) ){
		
		if ( isdigit(c) ) val = c - '0';
		else val = 10 + (c-'A');
		
		if ( maxval <= val ) maxval = val + 1;

		for ( int i = maxval; i <= 36; ++i ){
			res[i] *= i;
			res[i] += val;
			res[i] %= (i-1);
		}

	}
	
	int b = -1;

	for ( int i=maxval; i <= 36 ; ++i ){
		if ( res[i] == 0){
			b = i; 
			break;
		}
	}

	if (b < 0) printf("No solution.\n");
	else printf("%d\n",b);
	
	return 0;
}


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

char A[1000005];
char B[1000005];

int main(){
	int runs;
	int toOne, toZero;
	int one, zero;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%s", A);
		scanf("%s", B);
		toOne = toZero = zero = one = 0;
		for ( int i=0; A[i]; ++i ){
			if ( A[i] != B[i] ){
				if ( A[i] == '0' ) toOne++;
				else toZero++;
			}
			else {
				if (A[i] == '0') zero++;
				else one++;
			}
		}
		if ( toOne && !(one + toZero) ) puts("Unlucky Chef");
		else if ( toZero && !(zero + toOne) ) puts("Unlucky Chef");
		else {
			puts("Lucky Chef");
			printf("%d\n", max(toZero, toOne));
		}
	}
	return 0;
}


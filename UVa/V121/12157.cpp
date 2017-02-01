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
	int runs;
	int N, M, d;
	int A,B;
	scanf("%d", &runs);
	for ( int cases = 1;  cases <= runs; ++cases ){
		scanf("%d", &N);
		A = B = 0;
		while ( N-- ){
			scanf("%d", &d);
			A += ((d / 30) + 1) * 10;
			B += ((d / 60) + 1) * 15;
		}
		printf("Case %d:", cases);
		M = ( A < B )? A:B;
		if ( M == A ) printf(" Mile");
		if ( M == B ) printf(" Juice");
		printf(" %d\n", M);
	}
	return 0;
}


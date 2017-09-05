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
	int cases = 0;
	int X1, X2, Y1, Y2;	
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
		printf("Case %d: %d %d %d %d\n", ++cases, Y1, X2, Y2, X1);
	}
	return 0;
}


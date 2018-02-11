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

	int D;
	int T, w;
	int sum;
	scanf("%d", &D);
	for ( int i=1; i <= D; ++i ){
		scanf("%d", &T);
		sum = 0;
		while ( T-- ){
			scanf("%d", &w);
			sum += w;
		}
		if ( sum ) printf("Day %d: %d\n", i, sum);
		else puts("Weekend");
	}
	return 0;
}


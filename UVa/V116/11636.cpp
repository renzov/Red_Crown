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

int res[10005] = {0};

int main(){

	int n;
	
	for (int i=2, j = 1 ; i <= 10000 ; i <<= 1, j++ ){
		res[i] = j;
	}
	
	for ( int i=3,j = 2; i <= 10000 ; ++i ){
		if ( i != (j << 1) ) 
			res[i] = res[j] + 1;
		else
			j <<= 1;
	}
	int runs = 0;
	while ( scanf("%d",&n) && n > 0 ){
		runs++;
		printf("Case %d: %d\n",runs,res[n]);
	}

	return 0;
}


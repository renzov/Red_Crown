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
	int K, R;
	
	scanf("%d %d", &K, &R);
	
	double res = 0.0;
	double val;
	for ( int i=1; i <= K; ++i ){
		val = 1.0;
		for ( int j=1; j < (1<<i); ++j ){
			val *= (double)( (1<<K) - R - j + 1 ) / ( (1<<K) - j );
		}
		res += val;
	}
	printf("%.5f\n", res);
	return 0;
}


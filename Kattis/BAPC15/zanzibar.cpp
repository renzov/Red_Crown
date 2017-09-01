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
	int N;
	long long res;
	scanf("%d", &runs);
	while ( runs-- ){
		res = 0;
		int last = 1;
		while ( scanf("%d", &N) && N ) {
			res += max( 0, N - 2*last );
			last = N;
		}
		printf("%lld\n", res);
	}
	return 0;
}


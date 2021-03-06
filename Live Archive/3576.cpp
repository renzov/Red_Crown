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
	int N , w , d , W;
	int M;
	while ( scanf("%d %d %d %d",&N,&w,&d,&W) == 4 ){
		M = ((( N  - 1 )*N) >> 1)*w;
		if ( M == W ) printf("%d\n",N);
		else printf("%d\n",(M - W)/d);
	}
	return 0;
}


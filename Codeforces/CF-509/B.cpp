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
	long long a, b, x , y;
	cin >> a >> b >> x >> y;
	long long g = __gcd( x, y );
	x /= g, y /= g;
	if ( x > a || y > b ){
		cout << 0 << endl;
	}
	else {
		cout << min( a / x, b / y ) << endl;
	}
	return 0;
}


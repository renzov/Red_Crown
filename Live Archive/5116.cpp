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
	long long t[ 75 ] = {0};

	t[1] = 1;
	for ( int i=2; i <= 70 ; ++i ){
		t[i] = i;
		for ( int j=1; j < i ; ++j )
			t[i] = max( t[i] , t[ i - j ] * j );
	}

	for ( int i=1; i <= 70; ++i )
		cout << t[i] << endl;

	cout << *max_element( t , t + 75 )  << endl;
	return 0;
}


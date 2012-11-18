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

	int n,a,b;
	while ( scanf("%d",&n) && n){
		a = b = 0;
		int cnt = 0;
		for ( int i=0; i < 32; ++i ){
			if ( (n>>i) & 1 ){
				cnt++;
				if ( cnt & 1 ){
					a |= ( 1 << i );
				}
				else {
					b |= ( 1 << i );
				}
			}
		}
		printf("%d %d\n",a,b);
	}

	return 0;
}


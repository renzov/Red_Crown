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
int k;
int m;
int n;
long long memo[ 40 ][ 30 ][ 30 ][ 30 ];

long long solve( int x , int y , int ya , int r ){
	if ( x == m ){
		return ( y == 0 ) && (r == 0);
	}
	if ( memo[x][y][ya][r] != -1 ) return memo[x][y][ya][r];
	
	long long &ret = memo[x][y][ya][r];
	ret = 0LL;
	//Go up
	if ( y < n ){
		ret += solve( x + 1 , y + 1 , y , r );
	}
	//Go down
	if ( y > 0 ){
		if ( y <= ya ){
			ret += solve( x + 1 , y - 1 , y , r );
		}
		else { //Create a peak
			if ( y != k ){
				ret += solve( x + 1 , y - 1 , y , r );
			}
			else if ( r ){
				ret += solve( x + 1 , y - 1 , y , r - 1 );
			}
		}
	}
	return ret;
}

int main(){

	int r;	

	while ( scanf("%d %d %d",&n,&r,&k) != EOF ){
		m = 2*n;
		memset( memo , -1 , sizeof(memo) );
		printf("%lld\n",solve( 0 , 0, 0 , r ));
	}
	return 0;
}


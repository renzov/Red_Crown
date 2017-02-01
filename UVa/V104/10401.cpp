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

long long memo[ 20 ][ 20 ];
int pos[ 20 ];
int n;

long long solve( int last , int col ){
	if ( col == n ) return 1LL;
	if ( memo[last][col] != -1 )
		return memo[last][col];
	long long &ret = memo[ last ][ col ];
	ret = 0;
	if ( pos[col] >= 0 ){
		ret = ( abs(last - pos[col]) > 1 )? solve(pos[col],col + 1):0LL;
	}
	else {
		for ( int i=0; i < n; ++i ){
			if ( abs(last - i)  > 1 ){
				ret += solve( i , col + 1 );
			}
		}
	}
	return ret;
}

int main(){

	char s[ 20 ];

	while ( scanf("%s",s) != EOF ){
		n = strlen(s);
		memset(memo,-1,sizeof(memo));			
		
		for ( int i=0; i < n; ++i ){
			if ( s[i] == '?' ) pos[i] = -1;
			else if ( isdigit(s[i]) ) pos[i] = s[i] - '0' - 1;
			else pos[i] = s[i] - 'A' + 9; 
		}

		long long res = 0LL;
		if ( pos[0] >= 0 ){
			res = solve( pos[0] , 1 );
		}
		else {
			for ( int i=0; i < n; ++i )
				res += solve( i , 1 );
		}
		printf("%lld\n",res);
	}
	return 0;
}


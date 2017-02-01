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

int n;
int r[20];

int64 dp[20][35][3];
int64 dp2[20][35];

int64 f( int pos, int s, int lt ){
	if ( pos >= n ){
		if (lt == 2) return s > 0;
		return 1;
	}

	if ( dp[pos][s][lt] != -1 ) return dp[pos][s][lt];
	
	int64 &ret = dp[pos][s][lt];
	ret = 0;
	
	for ( int val=0; val <= s; ++val ){
		if (val < r[pos]) ret += f( pos + 1, s - val, (lt == 0)? 1:lt );
		else if (val == r[pos] ) ret += f( pos + 1, s - val, lt );
		else ret += f( pos + 1 , s - val, (lt == 0)? 2:lt );
	}
	return ret;
}

int64 g( int pos, int s ){
	if (pos >= n) return 1;

	if (dp2[pos][s] != -1 ) return dp2[pos][s];
	int64 &ret = dp2[pos][s];
	ret = 0;
	for ( int val = 0 ; val < s; ++val ){
		ret += g( pos + 1, s - val );
	}
	return ret;
}

int main(){
	int sum;
	
	while ( scanf("%d",&n) && n ){
		sum = 0;
		for ( int i=0; i<n; ++i ) scanf("%d",r+i), sum += r[i];
		//memset( dp2, -1, sizeof(dp2) );	
		memset( dp, -1 , sizeof(dp) );
		printf("%lld\n",f(0, sum, 0) );
	}
	return 0;
}


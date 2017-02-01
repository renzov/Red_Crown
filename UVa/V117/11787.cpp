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

int val( char c ){
	switch ( c ){
		case 'B' : return 1;
		case 'U' : return 10;
		case 'S' : return 100;
		case 'P' : return 1000;
		case 'F' : return 10000;
		case 'T' : return 100000;
		case 'M' : return 1000000;
	}
}

int main(){

	int runs;
	int n;
	char s[600];
	int last;
	int v;
	int cnt;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%s",s);
		n = strlen(s);

		if ( val( s[0] ) > val( s[n-1] ) ) reverse( s , s + n );

		bool ok = true;
		int res = 0;
		last = -1;
		for ( int i=0; s[i]  && ok; ++i ){
			v = val( s[i] );
			if ( v < last ) ok = false;
			else if ( v == last ){ cnt++; ok = (cnt <= 9); }
			else { last = v; cnt = 1; }
			res += v;
		}
		if ( ok ) printf("%d\n",res);
		else puts("error");
	}

	return 0;
}


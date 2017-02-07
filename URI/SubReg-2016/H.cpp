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

char s[60];
char v[60];

inline bool vowel( char c ){
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(){
	char last = '/';
	int m = 0;
	scanf("%s", s);
	for ( int i=0; s[i]; ++i ){
		if ( vowel(s[i]) ){
			last = s[i];
			v[m++] = last;
		}
	}
	bool ok = true;
	for ( int i=0, j=m-1; ok && i < j; i++,--j ){
		ok = v[i] == v[j];
	}
	puts((ok)? "S":"N");
	return 0;
}

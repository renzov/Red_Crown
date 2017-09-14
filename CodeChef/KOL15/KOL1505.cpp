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


void shrink( char *s ){
	int cnt = 0;
	char last = 0;
	for ( int i=0; s[i]; ++i ){
		if ( s[i] != last ){
			s[cnt++] = s[i];
			last = s[i];
		}
	}
	s[cnt] = '\0';
}

int main(){
	int runs;		
	char s[100];
	char t[100];

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%s %s", s, t);
		shrink(s);
		shrink(t);
		if ( strcmp(s,t) == 0 ) puts("Yes");
		else puts("No");
	}
	return 0;
}


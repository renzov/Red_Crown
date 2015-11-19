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

const int MAXN = 1000005;

int s[ MAXN ];
char type[ MAXN ];

int main(){
	int size = 0;
	int N;
	char c;
	int t = 0, g = 0;

	scanf("%d", &N);
	while ( getchar() != '\n' );

	for ( int i=0; i < 2*N; ++i ){
		c = getchar();
		if ( !size || c == type[size-1] ){
			type[ size ] = c;
			if ( c == 't' ) s[size++] = ++t;
			else s[size++] = ++g;
		}
		else {
			if (c == 't'){
				t++;
				printf("%d %d\n", s[--size], t);
			}
			else {
				g++;
				printf("%d %d\n", g, s[--size]);
			}
		}
	}
	return 0;
}


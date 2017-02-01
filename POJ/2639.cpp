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

char s[205];
int d[205];

void print( int x , int y ){
	printf("(");
	for ( int i=x; i <= y ; ++i ) putchar(s[i]);
	printf(")");
}

int cmp ( char *w , int idx  , int size ){
	char c;
	for ( int i=0; i < size; ++i ){
		c = w[(i + idx)%size]; 
		if ( w[i] != c )
			return w[i] < c? -1:1;
	}
	return 0;
}

bool isNeck( char *w , int size ){
	
	int zeros = 0;
	int ones = 0;
	int prefix = 0;	

	for ( int i=0; i < size && w[i]=='0' ; ++i ) prefix++;

	for ( int i=0; w[i] ; ++i )
		( w[i] == '0' )? zeros++:ones++;

	if ( !zeros || !ones ) return true;
	
	int M = -1;

	for ( int i=size-1; i >= 0 ; --i ){
	
		if ( w[i] == '0' ) d[i] = prefix + 1;
		else d[i] = 0;

		prefix = d[i];

		if ( d[i] > M ) M = d[i];
	
	}

	if ( d[0] < M ) return false;

	for ( int i=1; i < size; ++i ){
		if ( d[i] == M && (cmp( w , i , size ) > 0 ) ){ return false; }
	}

	return true;
}

int main(){

	int runs;
	int n;
	int i;
	int j;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%s",s);
		
		n = strlen( s );
		j = 0;

		while ( j < n ){
		
			for ( i=n; !isNeck( s + j , i - j ) ; --i );
			
			print( j , i - 1 );

			j = i;
		
		}
		puts("");

	}
	return 0;
}


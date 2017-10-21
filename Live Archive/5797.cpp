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

int T[][3] = { {2, 3, 0}, {1, 0, 0}, {1, 1, 0}, {3, 0, 0}, {3, 2, 0},  
			   {1, 2, 0}, {3, 1, 0}, {3, 3, 0}, {1, 3, 0}, {2, 1, 0} };

char s[105];
int S[105][3];

void print( int n, int r ){
	for ( int i=0; i < 2; ++i ){
		if ( (T[n][r] >> i) & 1 ) putchar('*');
		else putchar('.');
	}
}

bool eq( int a[], int b[] ){
	for ( int i=0; i < 3; ++i )
		if ( a[i] != b[i] ) return false;
	return true;
}

int main(){

	int D;
	char c;

	while ( scanf("%d", &D) && D ){
		scanf(" %c", &c);
		if ( c == 'S' ){
			scanf("%s", s);
			for ( int i=0; i < 3; ++i ){
				for ( int j=0; j < D; ++j ){
					if (j) putchar(' ');
					print( s[j] - '0' , i );
				}
				puts("");
			}
		}
		else {
			for ( int i=0; i < 3; ++i ) {
				for ( int j=0; j < D; ++j ){
					S[j][i] = 0;
					for ( int k=0; k < 2;  ++k ){
						scanf(" %c", &c);
						if ( c == '*' ) S[j][i] |= (1 << k);
					}
				}
			}
			for ( int i=0; i < D; ++i ){
				for ( int j=0; j < 10; ++j ){
					if ( eq( S[i], T[j] ) ){
						printf("%d", j);
						break;
					}
				}
			}
			puts("");
		}
	}
	return 0;
}


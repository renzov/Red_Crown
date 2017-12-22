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

bool A[6][30];
bool B[6][30];
int size[10];
int suff[10];
void read_matrix( bool M[6][30] ){
	char c;
	for ( int i=0; i < 6; ++i )
		for ( int j=0; j < 5; ++j ){
			scanf(" %c", &c);
			M[j][ c - 'A' ] = true;
		}
}

int main(){
	int K;
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		memset(A, false, sizeof(A));
		memset(B, false, sizeof(B));

		scanf("%d", &K);
		read_matrix( A );
		read_matrix( B );
		int total = 1;
		for ( int i=0; i < 5; ++i ){
			size[i] = 0;
			for ( int j=0; j < 26; ++j ){
				if ( A[i][j] && B[i][j] )
					size[ i ]++;
			}
		}
		suff[ 5 ] = 1;
		for ( int i=4; i >= 0; --i ) suff[i] = size[i] * suff[i + 1];

		if ( K > suff[0] ){
			puts("NO");
		}
		else {
			for ( int i=0; i < 5; ++i ){
				for ( int j=0; j < 26; ++j ){
					if ( A[i][j] && B[i][j] ){
						if ( suff[i+1] >= K ){
							printf("%c", (char)(j + 'A'));
							break;
						}
						else {
							K -= suff[i+1];
						}
					}
				}
			}
			puts("");
		}
	}
	return 0;
}


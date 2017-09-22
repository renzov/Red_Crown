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
const int MAXK = 20;

int K;
int size[MAXK];
int s[MAXK];

bool test( const int &mask, const int &L ){
	int temp;
	int m;
	for ( int i=0, k; i < K; ++i ){
		// Test i-th string
		m = mask, temp = s[i];
		k = 0;
		for ( int j=0; j < L && k < size[i]; ++j ){
			if ( (m & 1) == (temp & 1) ){
				temp >>= 1;
				k++;
			}
			m >>= 1;
		}
		if ( k < size[i] ) return false;
	}
	return true;
}

int main(){
	char neck[10];
	int runs;
	int maxsize;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &K);
		maxsize = 0;
		// Reading the input
		for ( int i=0; i < K; ++i ){
			scanf("%s", neck);
			s[i] = 0;
			size[i] = 0;
			for ( int j=0; neck[j]; ++j ){
				size[i]++;
				if ( neck[j] == 'B' )
					s[i] |= ( 1 << j );
			}
			maxsize = max( maxsize, size[i] );
		}
		bool ok = false;
		for ( int L = maxsize; ; ++L ){
			for ( int mask = 0; mask < ( 1 << L ); ++mask ){
				// Test this mask
				if ( test( mask, L ) ){
					ok = true;
					// print answer
					for ( int i=0; i < L; ++i )
						if ( (mask >> i) & 1 ) putchar('B');
						else putchar('G');
					puts("");
					break;
				}
			}
			if ( ok ) break;
		}
	}
	return 0;
}


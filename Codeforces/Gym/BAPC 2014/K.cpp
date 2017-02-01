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

const int MAXN = 15;
int n, m;
int BITS;
int V[MAXN];
int res[MAXN];

void brute(){
	int R = 0;
	int last;
	bool ok = true;
	for ( int i=0; i < n && ok; ++i ){
		if ( res[i] == 0 && V[i] == 0 ){
			ok = false;
		}
		else if ( res[i] == 1 && V[i] == 1 ){
			ok = false;
		}
	}
	if (ok) R++, last = 0;
	ok = true;
	for ( int i=0; i < n && ok; ++i ){
		if ( res[i] == 1 && V[i] == 0 ){
			ok = false;
		}
		else if ( res[i] == 0 && V[i] == 1 ){
			ok = false;
		}
	}
	if (ok) R++, last = 1;
	if ( R == 1 ){
		printf("%d\n", last);
	}
	else {
		printf("%d solutions\n", R);
	}
}

int main(){
	int runs;
	char s[50];
	int first, second;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &n, &m);
		for ( int i=0; i < n; ++i ){
			scanf("%s %d", s, V+i);
			res[i] = 0;
			for ( int j=0; j < m; ++j ){
				if ( s[j] == '1' ) res[i] |= ( 1 << j );
			}
		}

		if ( m == 1 ){
			brute();
			continue;
		}

		int M = m >> 1;  // M = floor(m / 2)
		int val;
		long long frec;
		bool ok;
		long long base = m + 1;
		map< long long, int > count;
		map< long long, int > witness;
		
		// Only consider the first M bits
		BITS = ( 1 << M ) - 1;

		for ( int mask=0; mask < (1 << M); ++mask ){
			frec = 0;
			ok = true;
			for ( int j=0; j < n && ok; ++j ){
				val = M - __builtin_popcount( (res[j] ^ mask) & BITS ); // val <= M
				ok = val <= V[j];
				frec *= base;
				frec += val;
			}
			if ( ok ) count[ frec ]++, witness[ frec ] = mask;
		}
	
		for ( int i=0; i < n; ++i ) res[i] >>= M;

		M = m - M;
		BITS = (1<<M) - 1;
		int R = 0;

		for ( int mask=0; mask < (1 << M); ++mask ){
			frec = 0;
			ok = true;
			for ( int j=0; j < n && ok; ++j ){
				val = M - __builtin_popcount( (res[j] ^ mask) & BITS );
				ok = val <= V[j];
				val = V[j] - val;
				frec *= base;
				frec += val;
			}
			if ( ok ){ 
				if ( count[ frec ] ){ 
					R += count[ frec ], second = mask, first = witness[ frec ];
				}
			}
		}
		if ( R == 1 ){
			second = (second << (m-M)) | first;
			for ( int i=0; i < m; ++i ){
				if ( second & 1 ) putchar('1');
				else putchar('0');
				second >>= 1;
			}
			puts("");
		}
		else { 
			printf("%d solutions\n", R);
		}
	}
	return 0;
}


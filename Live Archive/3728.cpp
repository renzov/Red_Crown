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

const int MAXN = 105;

int size[MAXN];
int M[MAXN][MAXN];
int C[MAXN];

int N,W,H;

void put( int pos , int beg ){
	for ( int i=0; i < size[pos]; ++i ){
		C[beg] |= M[pos][i];
		beg--;
	}
}

bool test( int pos , int beg ){
	bool ok = true;
	for ( int i=0; i < size[pos] && ok; ++i, beg-- ){
		ok = (C[ beg ] ^ M[pos][i]) == (C[beg] | M[pos][i]);
	}
	return ok;
}

int read(){
	char s[20];
	scanf("%s",s);
	int res = 0;
	for ( int i=0; i < W; ++i )
		if ( s[i] == 'X' )
			res |= ( 1 << i );
	return res;
}

int main(){

	int h;

	while ( scanf("%d %d %d",&N,&W,&H) && N && W && H ){
	
		for ( int i=0; i < N; ++i ){
			scanf("%d",size + i);
			for ( int j=0; j < size[i]; ++j ){
				M[i][j] = read();	
			}		
		}
	
		int idx = 0;
		int last;
		bool first = true;
		while ( idx < N ){
			fill( C , C + H , 0 );
			put( idx , size[idx] - 1 );
			h = size[idx] - 1;
			idx++;
			while ( idx < N ){
				last = -1;
				for ( int k = H - 1; k >= (size[idx] - 1); --k ){
					if ( !test( idx , k ) ) break;
					last = k;
				}
				if ( last < 0 ){
					if ( !first ) putchar(' ');
					printf("%d", h + 1 );
					first = false;
					break;
				}
				else {
					put( idx , last );
					h = last;
					idx++;
				}
			}
		}
		if (!first) putchar(' ');
		printf("%d\n",h+1);

	}
	return 0;
}


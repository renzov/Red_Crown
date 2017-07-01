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

const int MAXN = 5005;
int K[MAXN];

int main(){
	int col;
	int N, L, C;

	while ( scanf("%d %d %d", &N, &L, &C) != EOF ){
		col = N / L;
		if ( col*L < N ) col++;
		
		for ( int i=0; i < N; ++i ) scanf("%d", K+i);
		sort( K, K + N );
		reverse( K, K + N );

		bool ok = true;
		for ( int i=0; ok && i < N; i += L ){
			if ( K[i] > C ) ok = false;
			C -= K[i];
		}
		if ( ok ) puts("S");
		else puts("N");
	}
	return 0;
}


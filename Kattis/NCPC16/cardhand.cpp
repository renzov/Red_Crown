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
typedef pair< int , int > card;

const int MAXN = 60;
card C[MAXN];
card T[MAXN];
int suitorder[5];
int mul[5];
int N;

int dp[60][60];

int lcs(){
	for ( int i=0; i <= N; ++i ) dp[i][0] = dp[0][i] = 0;

	for ( int i=1; i <= N; ++i )
		for ( int j=1; j <= N; ++j ){
			if ( C[i-1] == T[j-1] ){
				dp[i][j] = 1 + dp[i-1][j-1];
			}
			else { 
				dp[i][j] = max( dp[i][j-1] , dp[i-1][j] );
			}
		}
	return dp[N][N];
}

int cmp( const card &A, const card &B ){
	if ( A.first != B.first ) return suitorder[ A.first ] < suitorder[ B.first ];
	return A.second*mul[ A.first ] < B.second*mul[ B.first ];
}

int get_suit( const char &c ){
	switch ( c ){
		case 's' : return 0; break;
		case 'h' : return 1; break;
		case 'd' : return 2; break;
		case 'c' : return 3; break;
	}
	return -1;
}

int get_rank( const char &c ){
	if ( isdigit(c) ) return c - '0';
	switch ( c ){
		case 'T' : return 10; break;
		case 'J' : return 11; break;
		case 'Q' : return 12; break;
		case 'K' : return 13; break;
		case 'A' : return 14; break;
	}
	return -1;
}

int main(){
	char s[5];
	scanf("%d", &N);
	
	for ( int i=0; i < N; ++i ){
		scanf("%s", s);
		C[i] = card( get_suit( s[1] ) , get_rank( s[0] ) );
		T[i] = C[i];
	}

	for ( int i=0; i < 4; ++i ) suitorder[ i ] = i;
	// Test all suit permutations
	int res = N;
	do {
		// Test for each suit a order
		for ( int i=0; i < 16; ++i ){ // one bit for each suit
			for ( int j=0; j < 4; ++j ) mul[j] = ( ( i >> j )&1 )? -1:1;
			sort( T, T + N, cmp );
			res = min( res , N - lcs() );
		}
	}
	while ( next_permutation( suitorder, suitorder + 4 ) );
	printf("%d\n", res);
	return 0;
}


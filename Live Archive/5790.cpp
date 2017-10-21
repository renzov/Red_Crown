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

const int MAXN = 1024;

int N;

int tim = 0;
int B[MAXN][MAXN];
int sum[MAXN][MAXN] = {0};
int T[MAXN][MAXN] = {0};
long long dp[MAXN][MAXN];

long long solve( const int &r, const int &c ){
	if ( r >= N ) return 0;
	if ( T[r][c] >= tim ) return dp[r][c];
	
	T[r][c] = tim;
	long long &res = dp[r][c];
	res = 0; // For not taking anything and when c == 0 and leave
	if ( c > 0 ){ // Leave the element
		res = max( res , solve( r, c - 1 ) );
	}
	// If we take the element
	res = max( res , sum[r][c+1] + solve( r + 1 , min( c, N - 2 - r ) ) );
	return res;
}

int main(){
	
	while ( scanf("%d", &N) && N ){
		// Reading the input
		// We consider the matrix by diagonals 
		for ( int i=0; i < N; ++i )
			for ( int j=0; j <= i; ++j )
				scanf("%d", &B[j][i-j]);
	
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < (N - i); ++j )
				sum[i][j+1] = sum[i][j] + B[i][j];

		tim++;	
		
		printf("%lld\n", solve(0, N-1));
	}
	return 0;
}


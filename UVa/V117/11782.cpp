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
int dp[(1 << 20) + 10][21];
int W[ (1 << 20) + 10];
int H;
int K;
int N;

void read( int u ){
	scanf("%d",W+u);
	if ( ((u<<1) + 1) < N ){
		read( (u << 1) + 1 );
		read( (u << 1) + 2 );
	}
}

int main(){
	int l,r;
	while ( scanf("%d",&H) && ( H >= 0 ) ){
		scanf("%d",&K);
		H++;
		N = ( 1 << H ) - 1;
		read( 0 );

		for ( int i=0; i < N; ++i ){
			dp[i][1] = W[i];
		}

		for ( int k=2; k <= K; ++k ){
			for ( int i=0; i < N; ++i ){
				dp[ i ][ k ] = dp[ i ][ k - 1 ]; 
				if ( ((i << 1) + 1) >= N ) continue;
				l = ( i << 1 ) + 1;
				r = ( i << 1 ) + 2;
				for ( int j=1; j < k; ++j ){
					dp[i][k] = max( dp[i][k] , dp[l][j] + dp[r][k-j] );
				}
			}
		}
		printf("%d\n",dp[0][K]);
	}

	return 0;
}


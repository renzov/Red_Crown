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
const int MAX = 20005;
const int INF = 1 << 30;
int L[ MAX ];
int R[ MAX ];
int D[ MAX ];

int dp[ MAX ][ 2 ];
int pos[ MAX ][ 2 ];
int main(){
	int n;
	int tmp;
	while ( scanf("%d",&n) && n ){
		for (int i=1; i <= n; ++i){
			dp[i][1] = dp[i][0] = INF;
			scanf("%d %d",L+i,R+i);
			D[ i ] = R[i] - L[i];
		}
		pos[0][0] = pos[0][1] = 1;
		dp[0][0] = dp[0][1] = 0;
		
		for ( int i=1; i <= n; ++i ){
			
			for ( int j=0; j < 2; ++j ){
				//LEFT = 0
				tmp = dp[ i - 1 ][ j ] + abs( R[i] - pos[i-1][j] ) + D[i];
				if ( tmp < dp[i][0] ){
					dp[i][0] = tmp;
					pos[i][0] = L[i];
				}
				//RIGHT = 1
				tmp = dp[ i - 1 ][ j ] + abs( L[i] - pos[i-1][j] ) + D[i];
				if ( tmp < dp[i][1] ){
					dp[i][1] = tmp;
					pos[i][1] = R[i];
				}
			}

		}
		printf("%d\n", dp[n][1] + (n - 1) + abs(n - pos[n][1]) );
	}
	return 0;
}


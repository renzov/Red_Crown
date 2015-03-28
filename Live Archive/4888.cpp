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

const int MAXN = 1005;

bool dp[MAXN][MAXN];
int A[MAXN];
int B[MAXN];
int C[2*MAXN];

int main(){
	int N,M;

	while ( scanf("%d %d",&N,&M) && M && N ){
		for ( int i=1; i <= N; ++i ) scanf("%d",A + i);
		for ( int i=1; i <= M; ++i ) scanf("%d",B + i);
		for ( int i=1; i <= (N + M); ++i ) scanf("%d",C + i);
		dp[0][0] = true;
		for ( int i=1; i <= max(N,M); ++i ){
			if (i <= N) dp[i][0] = ( A[i] == C[i] ) && dp[i-1][0];
			if (i <= M) dp[0][i] = ( B[i] == C[i] ) && dp[0][i-1];
		}
		for ( int i=1; i <= N; ++i )
			for ( int j=1; j <= M; ++j ){
				dp[i][j] = false;
				if ( ( A[i] == C[i+j] && dp[i-1][j] ) ||
				     ( B[j] == C[i+j] && dp[i][j-1] ) )
					dp[i][j] = true;
			}
		if ( dp[N][M] ) puts("possible");
		else puts("not possible");
	}
	return 0;
}


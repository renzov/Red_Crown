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

int C[MAXN];
int dp[MAXN][MAXN] = {0};

int main(){

	int runs;
	int N,j;
	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d",&N);
		for ( int i=0; i < N; ++i ) scanf("%d",C+i);

		for ( int i=0; i < (N-1) ; ++i ){
			dp[i][i+1] = (C[i] == C[i+1])? 1:0;
		}
		

		for (int L=4; L <= N ; L+=2 ){

			for ( int i=0; (i + L) <= N ; i++ ){
				j = i + L - 1;
				dp[i][j] = max( dp[i+1][j-1] + (C[i] == C[j]) , dp[i+2][j] + (C[i] == C[i+1]) );	
				
				for ( int k = i + 3 ; k < j ; k += 2 ){
					dp[i][j] = max( dp[i][j] , dp[i+1][k-1] + dp[k+1][j] + (C[i] == C[k]) );
				}

			}
		
		}
		printf("%d\n",dp[0][N-1]);
	}
	return 0;
}


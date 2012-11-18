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
#include<climits>

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
const int MAX = 17;
int dp[1<<MAX];
int n;
int p[MAX];
int adj[MAX];
int sum[1<<MAX];
int uncover[1<<MAX];

int main(){
	int m,u,v;
	while ( scanf("%d",&n) && n ){
		for ( int i=0;  i<n; ++i ){ scanf("%d",p+i); adj[i] = 0; }
		scanf("%d",&m);
		while ( m-- ){
			scanf("%d %d",&u,&v); u--,v--;
			adj[u] |= ( 1 << v );
			adj[v] |= ( 1 << u );
		}
		//Clear dp
		sum[0] = dp[0] = uncover[0] = 0;
		for ( int i=1; i < (1<<n); ++i ){
			dp[i] = -INT_MAX;
			sum[ i ] = 0;
			uncover[ i ] = 0;
			for ( int j=0; j < n; ++j )
				if ( (i>>j) & 1 ) 
					sum[i] += p[j];
				else
					uncover[ i ] |= adj[j];
		}


		for ( int i=1; i < (1<<n); ++i ){
			for ( int j=0; j < n; ++j ){
				if ( i == ((1<<n) - 1)){
					dp[i] = max( dp[i] , sum[i^(1<<j)] - dp[i^(1<<j)] + p[j] );
				}
				else if ( ((i>>j)&1) && ((uncover[i]>>j)&1)){
					dp[i] = max( dp[i] , sum[i^(1<<j)] - dp[i^(1<<j)] + p[j] );
				}
			
			}
		}
		int best = dp[(1<<n) - 1];
		int opponent = sum[ (1<<n) - 1 ] - best;
		if ( best > opponent ){
			printf("First player wins! %d to %d.\n",best,opponent);
		}
		else if ( best < opponent ){
			printf("Second player wins! %d to %d.\n",opponent,best);
		}
		else {
			printf("Tie game! %d all.\n",best);
		}
	}
	return 0;
}


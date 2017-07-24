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

const int MAXN = 1000005;
long long dp[7][2] = {0};
int W[MAXN];
int N;

int main(){
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ) scanf("%d", W+i);
	for ( int i=0; i < 7; ++i ) dp[i][0] = dp[i][1] = -1;
	dp[0][0] = 0;
	int nx;	
	int last = 0;
	
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < 7; ++j ){
			if ( dp[j][last] != -1 ){
				nx = ( j + W[i] ) % 7;
				dp[nx][1-last] = max ( dp[j][last] + W[i], dp[nx][last] );
			}
		}
		for ( int j=0; j < 7; ++j ) dp[j][1-last] = max( dp[j][1-last], dp[j][last] );
		last = 1 - last;
	}
	printf("%lld\n", dp[0][last]);
	return 0;
}


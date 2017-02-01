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
#include <cassert>

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

int dp[10005];
int pre[10005];
int w[256];

int main(){
	for ( int i=1; i <= 140; ++i ){
		w[i] = (i * (i+1)) / 2;
	}
	dp[0] = 0;
	dp[1] = 1;
	pre[1] = 1;
	for ( int i=2; i <= 10000; ++i ){
		dp[i] = i;
		pre[i] = 1;
		for ( int j=1; j <= 140 && w[j] <= i; ++j ){
			if ( dp[i] > (1 + dp[i - w[j]]) ){
				dp[i] = 1 + dp[i-w[j]];
				pre[i] = j;
			}
		}
	}
	int runs, N, l;
	char c;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		c = 'a';
		while ( N > 0 ){
			l = pre[ N ];
			for ( int i=0; i < l; ++i ) putchar(c);
			N -= w[l];
			c++;
		}
		putchar('\n');
	}
	return 0;
}


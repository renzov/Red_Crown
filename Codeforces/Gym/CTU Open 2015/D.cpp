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

const int MAXN = 10005;
const int MOD = 12345647;
char N[MAXN];
char L[MAXN];
int n, l;
int ti;

int dp[MAXN][8][3]; // dp( pos, mask is greater, carry )
int T[MAXN][8][3] = {0};

inline int gt( int m, int p ){ return (m >> p) & 1; }

int solve( int pos, int mask, int car ){
	if ( pos >= n ) return ( car == 0 )? 1:0;
	if ( T[pos][mask][car] >= ti ) return dp[pos][mask][car];
	T[pos][mask][car] = ti;
	int &res = dp[pos][mask][car];
	res = 0;
	int mask2;
	int car2;
	for ( int d1 = gt(mask,0)? 0:L[pos]; d1 <= 9; d1++ ){
		if ( d1 != 3 ){
			for ( int d2 = gt(mask,1)? 0:L[pos]; d2 <= 9; d2++ ){		
				if ( d2 != 3 ){
					for ( int d3 = gt(mask,2)? 0:L[pos]; d3 <= 9; d3++ ){
						if ( d3 != 3 ){
							mask2 = mask;
							if ( d1 > L[pos] ) mask2 |= 1;
							if ( d2 > L[pos] ) mask2 |= 2;
							if ( d3 > L[pos] ) mask2 |= 4;
							car2 = 10*car + N[pos] - d1 - d2 - d3;
							if ( car2 >= 0 && car2 <= 2 ){
								res += solve( pos + 1, mask2, car2 );
								res %= MOD;
							}
						}
					}
				}
			}
		}
	}
	return res;
}

int main(){
	int d;
	ti = 0;
	while ( scanf("%s %s", N, L) && N[0] != '0' ){
		ti++;
		n = strlen(N);
		l = strlen(L);
		d = n - l;
		for ( int i=0; i<n; ++i ) N[i] -= '0';
		for ( int i=l-1; i >= 0; i-- ) L[i + d] = L[i] - '0';
		for ( int i=0; i < d; ++i ) L[i] = 0;
		printf("%d\n", solve( 0,  0, 0 ));
	}
	return 0;
}

